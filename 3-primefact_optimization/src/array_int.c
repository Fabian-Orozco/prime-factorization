/**
 * Copyright [2021] <jeisson.hidalgo@ucr.ac.cr>
 * Basado en: <https://git.ucr.ac.cr/JEISSON.HIDALGO/concurrente21a-jeisson_hidalgo/-/blob/master/taller/stats/src/array_double.c>
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "array_int.h"

/**
 * @brief Incrementa la capacidad del arreglo (aumenta la cantidad de memoria reservada para el arreglo)
 * @param array Es la dirección de memoria donde se encuentra el arreglo al que se desea aumentar la capacidad
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si se realizó el incremento
 * 1 (EXIT_FAILURE) si no se realizó el incremento por falta de memoria
 */
int64_t array_int_increase_capacity(array_int_t* array);

int64_t array_int_init(array_int_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_int_destroy(array_int_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int64_t array_int_append(array_int_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (array_int_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int64_t array_int_increase_capacity(array_int_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)
    realloc(array->elements, new_capacity * sizeof(int64_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
