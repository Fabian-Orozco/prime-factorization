/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#ifndef TYPOGRAPHER_H
#define TYPOGRAPHER_H

#include <inttypes.h>
#include "array_entrada.h"

/**
 * @brief Se encarga de la impresión de resultados según la entrada de datos.
 * @details Imprime:
 * | Número: factor^frecuencia | si es compuesto con al menos un factor y frecuencia > 1
 * | Número : Número | si es primo
 * | Número: NA | si es 0 o 1
 * | invalid number | si se ingresó texto o un número fuera de rango (-2^63, ..., 2^63-1)
 * @code 
    imprimir(&entradas);
 * @endcode
 * @param entradas es el arreglo que contiene todas las entradas.
 */
void print_factorizations(array_entrada_t* entradas);

/**
 * @brief imprime el contenido de un arreglo dinamico
 * @param entradas es el arreglo que contiene todas las entradas.
 */
void imprimaArreglo(array_int_t* entradas);

/**
 * @brief imprime el contenido de un arreglo dinamico
 * @param elements arreglo con todas las entradas
 * @param count cantidad de elementos contenidos por el arreglo
 */
void imprimaArreglo2(int64_t* elements, uint64_t count);

void print_structure(array_entrada_t* entradas);

#endif  //  TYPOGRAPHER_H
