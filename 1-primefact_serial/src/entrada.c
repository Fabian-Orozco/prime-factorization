/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include "entrada.h"
#include <stdio.h>

int64_t entrada_init(entrada_t* entrada, int64_t valor, int64_t categoria) {
  assert(entrada);
  entrada->valor = valor;
  entrada->categoria = categoria;
  int64_t error = 0;
  if (entrada->categoria == COMPUESTO)
    error = array_int_init(&entrada->factores);
  return error;
}

void entrada_nan_init(entrada_t* entrada, int64_t categoria) {
  assert(entrada);
  entrada->valor = categoria;
  entrada->categoria = categoria;
}

void entrada_destroy(entrada_t* entrada) {
  assert(entrada);
  if (entrada->categoria == COMPUESTO)
    array_int_destroy(&entrada->factores);
  entrada->valor = 0;
  entrada->categoria = 0;
}

int64_t entrada_append_factor(entrada_t* entrada, int64_t factor) {
  int64_t error = array_int_append(&entrada->factores, factor);
  return error;
}
