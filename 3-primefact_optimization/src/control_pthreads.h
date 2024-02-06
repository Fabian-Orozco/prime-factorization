/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef CONTROL_PTHREAD_H
#define CONTROL_PTHREAD_H

#include <inttypes.h>
#include <stdbool.h>
#include <pthread.h>
#include "array_entrada.h"

/**
 * @brief Registro que representa a los datos compartidos entre hilos.
 */
typedef struct shared_data {
  uint64_t thread_count;
  array_entrada_t* entradas;
  uint64_t next_unit;
  pthread_mutex_t can_access_next_unit;
} shared_data_t;

/**
 * @brief Inicializa (pide memoria) para los datos compartidos
 * @details inicializa el mutex y la variable next_unit
 * @param argc es la cantidad de argumentos enviados
 * @param argv[] Es el arreglo que contiene cada argumento
 * @return puntero a datos compartidos o nulo de no poder inicializar.
 */
shared_data_t* init_shared_data(uint64_t argc, char* argv[]);


/**
 * @brief realiza la función de consumir del buffer (arreglo indizado)
 * @details mediante una variable contadora protegida por mutex realiza la asignación de la unidad para cada hilo, esto indefinidamente hasta consumir todo el buffer.
 * @code 
 * uint64_t counter = 0;
    for (counter = 0; counter < shared_data->thread_count; ++counter) {
      error
      = pthread_create(&threads[counter], NULL, consume, shared_data);
    }
 * @endcode
 * @param data argumento del hilo. en este caso envían los datos compartidos.
 */
void* consume(void* data);

/**
 * @brief Crea arreglo de hilos, reparte el trabajo y verifica la factorización de las entradas
 * @details designa la cantida de hilos a crear en caso de que sean más que las entradas ingresadas, crea el arreglo de hilos y el de datos privados. Reparte el trabajo de hilo e invoca la verificación para factorizar las entradas según el trabajo por hilo creado.
 * @param shared_data es un puntero a los datos compartidos.
 * @return entero que indica si hay o no error al crear los hilos.
 */
uint64_t create_pthreads(shared_data_t* shared_data);

#endif  // CONTROL_PTHREAD_H
