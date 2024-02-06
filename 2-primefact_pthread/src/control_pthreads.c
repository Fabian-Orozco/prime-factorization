/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "reader.h"
#include "control_pthreads.h"
#include "calculator.h"

shared_data_t* init_shared_data(uint64_t argc, char* argv[]) {
  // declare and initialize shared_data
  shared_data_t* shared_data = (shared_data_t*)
  calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    // shared_data->thread_count := validar_argumentos(argc, argv)
    shared_data->thread_count = validar_argumentos(argc, argv);
    // return shared data
    return shared_data;
  }
  return NULL;
}  // end procedure

void distribute_work(private_data_t* private_data) {
  shared_data_t* shared_data = private_data->shared_data;

  // declare thread_count := shared_data->thread_count
  uint64_t thread_count = shared_data->thread_count;

  // declare arr_size := entradas.count-1
  uint64_t inputs_size = shared_data->entradas->count - 1;
  // -1 para ignorar la entrada de ctrl+d / eof

  // cantidad minima de trabajo para cada hilo
  // trabajo_por_hilo := arr_size / thread_count
  uint64_t work_per_thread = inputs_size / thread_count;

  // cantidad de hilos que harán un trabajo más que los demás
  // threads_work_max := arr_size % thread_count
  uint64_t threads_work_max = inputs_size % thread_count;

  // cantidad de hilos que hacen la cantidad minima de trabajo
  // threads_work_min := thread_count - threads_work_max
  uint64_t threads_work_min = thread_count - threads_work_max;

  // indice que asigna el beginning y final de cada hilo
  // declare marcador := 0
  uint64_t marker = 0;

  // lleva la cuenta del hilo actual
  // declare thread_number := 0
  uint64_t thread_number = 0;

  // recorre arreglo
  // while thread_number < thread_count do
    while (thread_number < thread_count) {
      // ya recorrió los que trabajan el mínimo
      if (thread_number == threads_work_min) {
        // ++trabajo_por_hilo
        ++work_per_thread;
        // threads_work_min := 0
        // para que nunca más vuelva a entrar al if
        threads_work_min = 0;
      }
    // private_data_array[thread_number].beginning := marcador;
    private_data[thread_number].beginning = marker;

    // marcador += trabajo_por_hilo aumenta contador según qty de trabajo
    marker += work_per_thread;

    // private_data_array[thread_number]->end = marcador;
    private_data[thread_number].end = marker;
    // ++thread_number
    ++thread_number;
    }
}  // end procedure

uint64_t create_pthreads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;

  // si hay menos entradas que hilos => se crea un hilo por entrada
  if (shared_data->entradas->count-1 < shared_data->thread_count) {
    shared_data->thread_count = shared_data->entradas->count-1;
  }

  // arreglo de hilos
  // threads[thread_count]
  pthread_t* threads = (pthread_t*)
  malloc(shared_data->thread_count * sizeof(pthread_t));

  // arreglo de datos privados (corresponden a cada hilo respectivamente)
  // private_data[thread_count]
  private_data_t* private_data = (private_data_t*)
  calloc(shared_data->thread_count, sizeof(private_data_t));


  // if (threads && private_data)
  if (threads && private_data) {
    // inicializa punteros a shared data
    uint64_t counter = 0;
    // inicializa el shared data de cada elemento en el arreglo private_data
    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      private_data[counter].shared_data = shared_data;
    }
    // distribute_work(private_data, thread_count, entradas[])
    distribute_work(private_data);

    // verificar_factorización
    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      error =
      pthread_create(&threads[counter], /*args*/ NULL, verificar_factorizacion
      , &private_data[counter]);
    }

    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      error = pthread_join(threads[counter], /*value_ptr*/ NULL);
    }

  } else {
    error = 1;
  }
  free(private_data);
  free(threads);
  return error;
}
