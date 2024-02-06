/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array_entrada.h"
#include "array_int.h"
#include "control_pthreads.h"
#include "entrada.h"
#include "reader.h"
#include "calculator.h"
#include "typographer.h"

#define ERROR_MAIN_INIT_ARRAY 11
#define ERROR_MAIN_IN 12
#define ERROR_CREATE_THREADS 13
#define ERROR_CREATE_SHARE_DATA 14

/**
 * @brief main del programa
 * @details Crea y destruye el arreglo de struct, invoca la validación de entrada(lector.h) para almacenar los datos en cada struct e invoca a control de threads para crear threads, repartir trabajo y factorizar. Por ultimo invoca a imprimir para que muestre los datos del struct(tipografo.h).
 */
// procedure main(void)
int main(int argc, char* argv[]) {
  uint64_t error = 0;

  // declare and initialize shared_data
  shared_data_t* shared_data = init_shared_data(argc, argv);

  if (shared_data == 0) {
    fprintf(stderr, "error. No se pudo inicializar el thread count");
    return ERROR_CREATE_SHARE_DATA;
  }

  // declare and initialize array_entradas
  array_entrada_t* entradas = (array_entrada_t*)
  calloc(1, sizeof(array_entrada_t));
  error = array_input_init(entradas);
  if (!error) {
    // validar_entrada
    error = validar_entrada(stdin, entradas);
    if (!error) {
      shared_data->entradas = entradas;
      // create pthreads (reparte trabajo y factoriza).
      struct timespec start_time, finish_time;
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      error = create_pthreads(shared_data);

      clock_gettime(CLOCK_MONOTONIC, &finish_time);
      double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

      fprintf(stderr, "Execution time: %.9lfs\n", elapsed_time);
      // imprimir
      print_factorizations(entradas);
    } else {
      fprintf(stderr, "%i" " No se pudo validar la entrada\n", ERROR_MAIN_IN);
    }
  } else {
    fprintf(stderr, "%i" " No se pudo inicializar el array\n"
    , ERROR_MAIN_INIT_ARRAY);
  }
  array_input_destroy(entradas);
  free(entradas);
  free(shared_data);
  return EXIT_SUCCESS;
}  // end procedure
