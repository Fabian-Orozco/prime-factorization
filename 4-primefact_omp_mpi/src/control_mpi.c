/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <time.h>
#include "control_mpi.h"

uint64_t start_mpi(int argc, char* argv[]) {
  double start_time = 0;
  double elapsed = 0;

  uint64_t error = 0;
  int provided;
  if (MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided)
      == MPI_SUCCESS) {
    int process_number = -1;
    error = MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    error = MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    error = MPI_Get_processor_name(process_hostname, &hostname_length);

    // mide el tiempo de pared del proceso 1
    if (process_number == 0) {
      start_time = MPI_Wtime();
    }

    // declare and initialize thread_count
    uint64_t thread_count = validar_argumentos(argc, argv);

    error = start_process(process_count, process_number, thread_count);

    if (process_number == 0) {
      elapsed = MPI_Wtime() - start_time;
      fprintf(stderr, " /_ proc.numb: %i  |  general_time_elapsed: %lf_\\ \n"
        , process_number, elapsed);
    }
    MPI_Finalize();
  }
  return error;
}

uint64_t* distribute_work(int process_count, uint64_t inputs_count
  , uint64_t* all_range, uint64_t* all_range_count) {
  uint64_t temp = process_count;
  int temp2 = inputs_count;  // NOWARNING

  // verifica si tiene el tamanio adecuado de entradas
  if (process_count > (temp2 >> 1)) {
    process_count = (temp2 >> 1);
  }

  *all_range_count = (process_count << 1);
  all_range = (uint64_t*) calloc(temp << 1, sizeof(uint64_t));

  // itera sobre all_range de 2 en 2 en cada ciclo
  int counter = 0;
  for (int i = 0; i < process_count; ++i) {
    // calculator
    all_range[counter++] = calculate_start(i, inputs_count, process_count, 0);
    all_range[counter++] = calculate_finish(i, inputs_count, process_count, 0);
  }
  return all_range;
}

uint64_t start_process(int process_count, int process_number
  , uint64_t thread_count) {
  uint64_t error = 0;
  array_int_t* entradas = (array_int_t*) calloc(1, sizeof(array_int_t));
  array_int_t* factores = (array_int_t*) calloc(1, sizeof(array_int_t));
  error = array_int_init(entradas); error = array_int_init(factores);

  // buffer a enviar
  int64_t* elements = 0;
  uint64_t inputs_count = -1;
  uint64_t inputs_capacity = -1;

  // cantidad de elementos en all_range
  uint64_t all_range_count = -1;

  // rango de cada bloque
  uint64_t start = -1;
  uint64_t finish = -1;

  // array que sirve para distribuir aleatoriamente los bloques
  uint64_t* process_array = 0;
  bool can_print = false;
  bool can_continue = false;

  if (!error) {
    if (process_number == 0) {
      // array que sirve para distribuir el trabajo por bloque (inicialmente)
      uint64_t* all_range = 0;

      process_array = randomize_process_array(process_array, process_count);

      // printf("proceso cero\n");
      error = validar_entrada(stdin, entradas);

      elements = entradas->elements;
      inputs_capacity = entradas->capacity;

      // quita el ctrl+d y su categoria
      inputs_count = entradas->count-2;

      // envia el arreglo de entradas | MPI_Send
      send_elements(elements, inputs_capacity, process_count, inputs_count);

      // distribuye el trabajo por bloques
      all_range = distribute_work(process_count, inputs_count, all_range
        , &all_range_count);

      distribute_work_random(process_count, process_array, &start, &finish
      , all_range);

      // libera memoria
      free(all_range);
// end process0---------------------------------------------------------
    }
// process != 0---------------------------------------------------------
    if (process_number != 0) {
      if (MPI_Recv(&inputs_capacity, /*capacity*/ 1, MPI_INT64_T
        , /*source*/ 0 , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)
          != MPI_SUCCESS) {
          fprintf(stderr, "error: no se pudo recibir input_capacity\n");
      }

      if (MPI_Recv(&inputs_count, /*capacity*/ 1, MPI_INT64_T
        , /*source*/ 0 , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)
          != MPI_SUCCESS) {
          fprintf(stderr, "error: no se pudo recibir input_counts\n");
      }

      // receive_my_data(elements, &start, &finish, &inputs_capacity);
      elements = (int64_t *) calloc(inputs_capacity, sizeof(int64_t));

      // recibe elements del proceso 0
      if (MPI_Recv(elements, /*capacity*/ inputs_capacity, MPI_INT64_T
        , /*source*/ 0 , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)
          != MPI_SUCCESS) {
          fprintf(stderr, "error: no se pudo recibir elements\n");
      }

      // recibe start del proceso 0
      if (MPI_Recv(&start, /*capacity*/ 1, MPI_UINT64_T, /*source*/ 0
        , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
          fprintf(stderr, "error: no se pudo recibir start\n");
      }

      // recibe finish del proceso 0
      if (MPI_Recv(&finish, /*capacity*/ 1, MPI_UINT64_T, /*source*/ 0
        , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS)  {
          fprintf(stderr, "error: no se pudo recibir finish\n");
      }

// end process != 0-----------------------------------------------------------
    }

// all process---------------------------------------------------------
    // factoriza por rango
    array_entrada_t* my_inputs;
    if (start != 0 || finish != 0) {
      my_inputs = consume(process_number, start, finish, elements
        , thread_count);
    }

// process0---------------------------------------------------------
    if (process_number == 0) {
      for (int index = 0; index < process_count; ++index) {
        if (process_array[index] != 0) {
          uint64_t target = process_array[index];
          // printf("target: %li\n", target);
          MPI_Send(&can_print, 1, MPI_C_BOOL, target, 0, MPI_COMM_WORLD);
          MPI_Recv(&can_continue, 1, MPI_C_BOOL, MPI_ANY_SOURCE, 0
            , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
          print_factorizations(my_inputs);
        }
      }
    } else {
// end process != 0----------------------------------------------------------
      MPI_Recv(&can_print, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD
        , MPI_STATUS_IGNORE);
      print_factorizations(my_inputs);
      MPI_Send(&can_continue, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD);
    }
// process0-----------------------------------------------------------------
    if (process_number == 0) {
      free_structures(factores, entradas, my_inputs);
// end process0-------------------------------------------------------------
    }
    error = EXIT_SUCCESS;
  } else {
    fprintf(stderr, "error: could not init arrays\n");
    error = EXIT_FAILURE;
  }
  return error;
}

uint64_t send_elements(int64_t* elements, uint64_t inputs_capacity
  , int process_count, uint64_t inputs_count) {
  for (int target = 1; target < process_count; ++target) {
    if (MPI_Send(&inputs_capacity, 1,
      MPI_UINT64_T, target, 0, MPI_COMM_WORLD) != MPI_SUCCESS ) {
      fprintf(stderr, "error: no se pudo enviar el arreglo de entradas\n");
    }
    if (MPI_Send(&inputs_count, 1,
      MPI_UINT64_T, target, 0, MPI_COMM_WORLD) != MPI_SUCCESS ) {
      fprintf(stderr, "error: no se pudo enviar el arreglo de entradas\n");
    }
    if (MPI_Send(elements, inputs_capacity,
      MPI_UINT64_T, target, 0, MPI_COMM_WORLD) != MPI_SUCCESS ) {
      fprintf(stderr, "error: no se pudo enviar el arreglo de entradas\n");
    }
  }
  return EXIT_SUCCESS;
}

uint64_t distribute_work_random(int process_count, uint64_t* process_array
  , uint64_t* start, uint64_t* finish, uint64_t* all_range) {
  // distribuye el trabajo aleatoriamente
  uint64_t contador = 0;
  for (int index = 0; index < process_count; ++index) {
    uint64_t target = process_array[index];
    if (target != 0) {
      uint64_t temp = all_range[contador++];
      // envia el start a cada proceso de forma aleatoria
      if (MPI_Send(&temp, 1, MPI_UINT64_T, target, 0, MPI_COMM_WORLD) \
        != MPI_SUCCESS ) {
          fprintf(stderr, "error: no se pudo enviar start\n");
      }
      temp = all_range[contador++];
      // envia el finish a cada proceso de forma aleatoria
      if (MPI_Send(&temp, 1, MPI_UINT64_T, target, 0, MPI_COMM_WORLD) \
        != MPI_SUCCESS ) {
          fprintf(stderr, "ERROR: no se pudo enviar finish\n");
      }
    } else {
      *start = all_range[contador++];
      *finish = all_range[contador++];
    }
  }
  return EXIT_SUCCESS;
}

uint64_t free_structures(array_int_t *factores, array_int_t *entradas
  , array_entrada_t* inputs) {
  array_int_destroy(factores);
  array_int_destroy(entradas);
  array_input_destroy(inputs);
  free(factores);
  free(entradas);
  free(inputs);
  return EXIT_SUCCESS;
}
