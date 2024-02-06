/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#ifndef MATEMATICO_H
#define MATEMATICO_H

#include <inttypes.h>
#include <stddef.h>
#include "array_int.h"
#include "array_entrada.h"

/**
 * @brief Verifica si un numero es compuesto o no.
 * @details Utiliza el operador módulo para ver si se puede dividir en al menos un número distinto a él mismo; de ser así, se confirma que es compuesto.
 * @code
 * if ( es_compuesto(valor) ) {
    return COMPUESTO;
 * @endcode
 * @param value Es el entero que se quiere verificar.
 * @return 1 en caso de que el número sea compuesto, en caso contrario 0.
 */
int64_t is_compound(int64_t value);

/**
 * @brief Asigna una banderilla que categoriza al entero.
 * @details Se utiliza para clasificar el entero en una categoría.
 * @code 
 * int64_t categoria = assign_category(valor);
 * @endcode
 * @param value Es el entero que se quiere categorizar.
 * @return La categoría(banderilla) a la que pertenece: 
 * -2 (NEGATIVO) si el entero es menor que 0.
 * -3 (ESPECIAL) si el entero es 1 o 0.
 * -4 (PRIMO) si el entero es primo.
 * -5 (COMPUESTO) si el entero es compuesto.
 */
int64_t assign_category(int64_t value);

/**
 * @brief Verifica la categoría del número y si es debido, invoca a factorizar.
 * @details Se utiliza para realizar la factorización a los números debidos.
 * @code 
 * for (contador = 0; contador < shared_data->thread_count; ++contador) {
      pthread_create(&threads[contador], NULL, verificar_factorizacion
      , &private_data[contador]);
    }
 * @endcode
 * @param data argumento del hilo. en este caso envían los datos privados del hilo.
 */
void* verificar_factorizacion(void* data);

/**
 * @brief Cuenta y retorna la cantidad de veces que se repite el factor
 * @details Se utiliza para la impresión de los factores de un entero
 * @code 
 * int64_t frecuencia = contar_frecuencia(factor, &compuesto->factores, &actual);
 * @endcode
 * @param factor Es el factor del que se quiere saber la frecuencia 
 * @param factors Es el arreglo que contiene los factores de todos los enteros.
 * @param actual Representa la posición del arreglo de factores por la que se quiere iterar.
 * @return La cantidad de veces que se repite el factor
 */
int64_t contar_frecuencia(int64_t factor, array_int_t* factors
, size_t* actual);


#endif  //  LECTOR_H
