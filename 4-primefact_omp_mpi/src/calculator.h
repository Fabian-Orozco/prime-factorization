/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#ifndef MATEMATICO_H
#define MATEMATICO_H

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "array_int.h"
#include "array_entrada.h"
#include "control_threads.h"

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
 * verificar_factorizacion(shared_data, my_unit);
 * @endcode
 * @param entradas Es el arreglo que contiene cada entrada con sus atributos.
 * @param unit unidad a la cual le toca factorizar el hilo.
 */
void verificar_factorizacion(array_entrada_t* entradas, uint64_t unit);

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

/**
 * @brief calcula el inicio de un bloque (mapeo por bloque)
 * @param process_number numero de proceso que ejecuta el metodo
 * @param end limite final del arreglo a repartir
 * @param process_count cantidad de procesos en el world
 * @param begin limite inicial del arreglo a repartir
 * @return entero | codigo error: 0 si fue exitoso
 */
int calculate_start(int process_number, int end, int process_count, int begin);

/**
 * @brief calcula el final de un bloque (mapeo por bloque)
 * @param process_number numero de proceso que ejecuta el metodo
 * @param end limite final del arreglo a repartir
 * @param process_count cantidad de procesos en el world
 * @param begin limite inicial del arreglo a repartir
 * @return entero | codigo error: 0 si fue exitoso
 */
int calculate_finish(int process_number, int end, int process_count, int begin);

/**
 * @brief calcula el minimo entre dos numeros
 * @param x numero que sera comparado
 * @param y numero que sera comparado
 * @return int el minimo entre los numeros pasados por parametro
 */
int minimo(int x, int y);

/**
 * @brief llena un arreglo con cero hasta la cantidad de procesos
 * @param process_array arreglo que sera llenado
 * @param process_count cantidad de procesos en el world
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t* fill_process_array(uint64_t* process_array, int process_count);

/**
 * @brief randomiza los elementos de un arreglo
 * @details Basado en https://stackoverflow.com/a/6127606
 * @param process_array arreglo que sera llenado
 * @param process_count cantidad de procesos en el world
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t* randomize_process_array(uint64_t* process_array, int process_count);

#endif  //  LECTOR_H
