/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <unistd.h>
#include <stdlib.h>

#include "reader.h"
#include "calculator.h"
#include "control_threads.h"
#include "mpi.h"

array_entrada_t* consume(int process_number, uint64_t start, uint64_t finish
  , int64_t* elements, uint64_t thread_count) {
  if (start == 0 && finish == 0) {
    // proceso no debe consumir
    return NULL;  // flag para saber que ya no tiene que hacer nada mas.
  }
  uint64_t range = finish - start;

  if (thread_count > range) {
    thread_count = range;
  }

  array_entrada_t* entradas = (array_entrada_t*)
  calloc(1, sizeof(array_entrada_t));

  array_input_init(entradas);

  for (uint64_t index = start; index < finish; index += 2) {
    entrada_t nueva;
    entrada_init(&nueva, elements[start++], elements[start++]);
    array_input_append(entradas, &nueva);
  }

  double consume_start_time = MPI_Wtime();
  #pragma omp parallel for num_threads(thread_count) schedule(dynamic) \
    default(none) shared(entradas, elements)
  for (uint64_t index = 0; index < entradas->count; ++index) {
    verificar_factorizacion(entradas, index);
  }

  double consume_elapsed_time = MPI_Wtime() - consume_start_time;
  fprintf(stderr, " |  proc.numb: %i  |  consume time_elapsed: %lf  |\n"
    , process_number, consume_elapsed_time);
  return entradas;
}

