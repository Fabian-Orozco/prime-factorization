/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef ARRAY_ENTRADA_H
#define ARRAY_ENTRADA_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "entrada.h"

/**
 * @brief Registro que representa un arreglo dinámico que contiene elementos dinámico tipo entrada_t.
 * 
 */
typedef struct {
  size_t capacity;
  size_t count;
  entrada_t* elements;
} array_entrada_t;

/**
 * @brief Inicializa los campos del struct
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea inicializar.
 * @return Código de error:
 * 0 si se realizó la inicialización
 * 1 si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t array_input_init(array_entrada_t* array);

/**
 * @brief Libera la memoria y "resetea" los campos de cada struct y del array.
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea inicializar.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si se realizó la inicialización
 * 1 (EXIT_FAILURE) si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
void array_input_destroy(array_entrada_t* array);

/**
 * @brief Agrega un nuevo elemento de tipo entrada_t al final del arreglo
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea inicializar.
 * @param element Es el valor tipo entrada_t que se desea agregar.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si agregó exitosamente el valor
 * 1 (EXIT_FAILURE) si no pudo agregar el valor por falta de memoria
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t array_input_append(array_entrada_t* array, entrada_t* element);

#endif  // ARRAY_ENTRADA_H
