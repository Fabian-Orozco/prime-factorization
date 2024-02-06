/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef CONTROL_THREAD_H
#define CONTROL_THREAD_H

#include <inttypes.h>
#include <stdbool.h>
#include <omp.h>
#include "array_entrada.h"
#include "typographer.h"

/**
 * @brief realiza la función de consumir del buffer (arreglo indizado)
 * @details a traves de la tecnologia openMP
 * @param process_number numero de proceso que ejecuta la funcion
 * @param start variable de cada proceso (inicio del mapeo)
 * @param finish variable de cada proceso (final del mapeo)
 * @param elements arreglo con todas las entradas
 * @param thread_count entero que indica la cantidad de hilos a crear
 * @return entero | codigo error: 0 si fue exitoso
 */
array_entrada_t* consume(int process_number, uint64_t start, uint64_t finish
  , int64_t* elements, uint64_t thread_count);

#endif  // CONTROL_THREAD_H
