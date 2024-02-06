/**
 * Copyright [2021] <jeisson.hidalgo@ucr.ac.cr>
 * Basado en: <https://git.ucr.ac.cr/JEISSON.HIDALGO/concurrente21a-jeisson_hidalgo/-/blob/master/taller/stats/src/array_double.c>
 * 
 */

#include <assert.h>
#include <stdlib.h>

#include "array_entrada.h"

/**
 * @brief Incrementa la capacidad del arreglo (aumenta la cantidad de memoria reservada para el arreglo)
 * @param array Es la dirección de memoria donde se encuentra el arreglo al que se desea aumentar la capacidad
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si se realizó el incremento
 * 1 (EXIT_FAILURE) si no se realizó el incremento por falta de memoria
 */
int64_t array_input_increase_capacity(array_entrada_t* array);

int64_t array_input_init(array_entrada_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_input_destroy(array_entrada_t* array) {
  assert(array);
  for (size_t i = 0 ; i < array->count; ++i) {
    entrada_destroy(&array->elements[i]);
  }
  free(array->elements);
  array->capacity = 0;
  array->count = 0;
}

int64_t array_input_append(array_entrada_t* array, entrada_t* element) {
  assert(array);
  if (array->count == array->capacity) {
    if (array_input_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = *element;
  return EXIT_SUCCESS;
}

int64_t array_input_increase_capacity(array_entrada_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  entrada_t* new_elements = (entrada_t*)
    realloc(array->elements, new_capacity * sizeof(entrada_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
