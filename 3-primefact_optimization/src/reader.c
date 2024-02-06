/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "reader.h"
#include "calculator.h"


/**
 * @brief Almacena la entrada según su categoría.
 * @details Crea e inicializa el struct entrada y lo almacena en el arreglo de entradas.
 * @code 
 * almacenar_entrada(entradas, valor, categoria);
 * @endcode
 * @param entradas Es el arreglo que contiene cada entrada con sus atributos.
 * @param value Es el valor de la entrada.
 * @param category Es la categoria de la entrada.
 */
int64_t almacenar_entrada(array_entrada_t* entradas, int64_t value
, int64_t category) {
  // verifique categoria, cree e inicialice struct entrada
  // crea una entrada
  entrada_t nueva;
  if (category == INVALID)
    // inicializa la entrada según su categoría
    entrada_nan_init(&nueva, INVALID);
  else
    // inicializa la entrada según su categoría
    entrada_init(&nueva, value, category);
  // añade la entrada al arreglo de entradas.
  array_input_append(entradas, &nueva);
  return 1;
}

int64_t validar_entrada(FILE* input, array_entrada_t* entradas) {
  assert(input);
  int64_t value = 0;
  // Mientras no sea el final del archivo
  while ((feof(input) == 0)) {
    // Verificar cada línea del archivo
    //  Si es entero de 64 bits con signo y su rango es válido
    if (fscanf(input, "%" SCNd64, &value) == 1) {
      if (errno == 0) {  // dentro del rango
        // Categoriza e invoca a almacenar entrada
        // negativo, primo o compuesto
        int64_t category = assign_category(value);
        almacenar_entrada(entradas, value, category);
      } else {  // fuera de rango
        // // si es fuera de rango invoca almacenar entrada y resetea errno
        almacenar_entrada(entradas, INVALID, INVALID);
        errno = 0;
      }
    } else {  // texto
      // si es texto invoca a almacenar entrada y flushea la entrada
      almacenar_entrada(entradas, INVALID, INVALID);
      fscanf(input, "%*s");
    }
  }
  // entrada vacía retorna error
  if (entradas->count == 1) {
    return 1;
  }
  return 0;
}  // end procedure

// procedure validar_argumentos(argc, argv[])
uint64_t validar_argumentos(uint64_t argc, char* argv[]) {
  // declare pthreads_count := default_cpu_max
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  // if argc == 2
  if (argc == 2) {
    // pthreads_count := argv[1]
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 0 || thread_count < 1) {
      fprintf(stderr, "Error: invalid thread count\n");
      thread_count = 0;
    }
  }
  // return pthreads_count
  return thread_count;
}  // end procedure
