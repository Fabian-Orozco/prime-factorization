/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include "entrada.h"
#include <stdio.h>

int64_t entrada_init(entrada_t* entrada, int64_t value, int64_t category) {
  assert(entrada);
  entrada->value = value;
  entrada->category = category;
  int64_t error = 0;
  if (entrada->category == COMPOUND)
    error = array_int_init(&entrada->factors);
  return error;
}

void entrada_nan_init(entrada_t* entrada, int64_t category) {
  assert(entrada);
  entrada->value = category;
  entrada->category = category;
}

void entrada_destroy(entrada_t* entrada) {
  assert(entrada);
  if (entrada->category == COMPOUND)
    array_int_destroy(&entrada->factors);
  entrada->value = 0;
  entrada->category = 0;
}

int64_t entrada_append_factor(entrada_t* entrada, int64_t factor) {
  int64_t error = array_int_append(&entrada->factors, factor);
  return error;
}
