/**
 * Copyright [2021] <jeisson.hidalgo@ucr.ac.cr>
 * Basado en: <https://git.ucr.ac.cr/JEISSON.HIDALGO/concurrente21a-jeisson_hidalgo/-/blob/master/taller/stats/src/array_double.h>
 * 
 */

#ifndef ARRAY_INT_H
#define ARRAY_INT_H
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Registro que representa un arreglo dinámico que contiene elementos dinámico tipo int64_t.
 * 
 */
typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_int_t;

/**
 * @brief Inicializa los campos del struct
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea inicializar.
 * @return Código de error:
 * 0 si se realizó la inicialización
 * 1 si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t array_int_init(array_int_t* array);

/**
 * @brief Libera la memoria y "resetea" los campos del struct
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea destruir.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si se realizó la inicialización
 * 1 (EXIT_FAILURE) si no se realizó la inicialización
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
void array_int_destroy(array_int_t* array);

/**
 * @brief Agrega un nuevo elemento de tipo int64_t al final del arreglo
 * @param array Es la dirección de memoria donde se encuentra el arreglo que se desea agregar.
 * @param element Es el valor tipo int65_t que se desea agregar.
 * @return Código de error:
 * 0 (EXIT_SUCCESS) si agregó exitosamente el valor
 * 1 (EXIT_FAILURE) si no pudo agregar el valor por falta de memoria
 * @remark Realiza una comprobación con assert para saber si le pasaron una entrada válida.
 */
int64_t array_int_append(array_int_t* array, int64_t element);

#endif  //  ARRAY_INT_H
