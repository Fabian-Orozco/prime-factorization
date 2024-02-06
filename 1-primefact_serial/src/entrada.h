/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef ENTRADA_H
#define ENTRADA_H

#include <inttypes.h>
#include <assert.h>
#include "array_int.h"

// comp, prime, neg, 0 1, rang / text
enum{COMPUESTO = -5, PRIMO, NEGATIVO, ESPECIAL, NO_VALIDO};

/**
 * @brief Registro que representa a un valor y su categoria, de ser compuesto almacena también sus factores.
 * 
 */
typedef struct entrada {
  int64_t valor;
  int64_t categoria;
  array_int_t factores;
} entrada_t;

/**
 * @brief Inicializa los campos del struct
 * @param entrada Es la dirección de memoria donde se encuentra el registro que se desea inicializar.
 * @param valor Es el valor que tendrá la entrada.
 * @param categoria Es la categoria de la entrada (primo, negativo o compuesto).
 * @return Código de error:
 * 0 si se realizó la inicialización
 * 1 si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t entrada_init(entrada_t* entrada, int64_t valor, int64_t categoria);

/**
 * @brief Inicializa los campos del struct
 * @param entrada Es la dirección de memoria donde se encuentra el registro que se desea inicializar.
 * @param categoria Es la categoria de la entrada (texto o fuera de rango).
 * @return Código de error:
 * 0 si se realizó la inicialización
 * 1 si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida. El valor coincide con la categoria.
 */
void entrada_nan_init(entrada_t* entrada, int64_t categoria);

/**
 * @brief Libera la memoria y "resetea" los campos del struct
 * @param entrada Es la dirección de memoria donde se encuentra el registro que se desea destruir.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si se realizó la inicialización
 * 1 (EXIT_FAILURE) si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
void entrada_destroy(entrada_t* entrada);

/**
 * @brief Agrega un nuevo elemento de tipo int64_t al final del arreglo de factores del struct.
 * @param entrada Es la dirección de memoria donde se encuentra el struct que se desea agregar.
 * @param factor Es el valor tipo int64_t que se desea agregar.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si agregó exitosamente el valor
 * 1 (EXIT_FAILURE) si no pudo agregar el valor por falta de memoria
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t entrada_append_factor(entrada_t* entrada, int64_t factor);

#endif  // ENTRADA_H
