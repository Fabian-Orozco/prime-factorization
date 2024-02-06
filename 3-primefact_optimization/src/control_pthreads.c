/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

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
    shared_data->next_unit = 0;
    if (!pthread_mutex_init(&shared_data->can_access_next_unit, NULL)) {
      // return shared data
      return shared_data;
    }
  }
  return NULL;
}  // end procedure

void* consume(void* data) {
  shared_data_t* shared_data = (shared_data_t*) data;
  uint64_t my_unit = 0;
  while (true) {
    pthread_mutex_lock(&shared_data->can_access_next_unit);
    if (shared_data->next_unit < shared_data->entradas->count) {
      my_unit = shared_data->next_unit++;
    } else {
      pthread_mutex_unlock(&shared_data->can_access_next_unit);
      break;
    }
    pthread_mutex_unlock(&shared_data->can_access_next_unit);
    verificar_factorizacion(shared_data, my_unit);
  }
  return NULL;
}

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

  // if (threads)
  if (threads) {
    // inicializa punteros a shared data
    uint64_t counter = 0;
    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      error
      = pthread_create(&threads[counter], /*args*/ NULL, consume, shared_data);
    }
    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      error = pthread_join(threads[counter], /*value_ptr*/ NULL);
    }
  } else {
    error = 1;
  }
  free(threads);
  return error;
}
