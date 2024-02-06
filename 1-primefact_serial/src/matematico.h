/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#ifndef MATEMATICO_H
#define MATEMATICO_H

#include <inttypes.h>
#include <stddef.h>
#include "array_int.h"
#include "array_entrada.h"

int64_t es_compuesto(int64_t valor);

int64_t asignar_categoria(int64_t valor);

void verificar_factorizacion(array_entrada_t* entradas);

int64_t contar_frecuencia(int64_t factor, array_int_t* factores
, size_t* actual);


#endif  //  LECTOR_H
