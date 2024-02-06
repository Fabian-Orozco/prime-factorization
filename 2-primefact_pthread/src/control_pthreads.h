/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef CONTROL_PTHREAD_H
#define CONTROL_PTHREAD_H

#include <inttypes.h>
#include "array_entrada.h"

/**
 * @brief Registro que representa a los datos compartidos entre hilos.
 */
typedef struct shared_data {
  uint64_t thread_count;
  array_entrada_t* entradas;
} shared_data_t;

/**
 * @brief Registro que representa a los datos privados de cada hilo.
 */
typedef struct private_data {
  shared_data_t* shared_data;
  uint64_t beginning;
  uint64_t end;
} private_data_t;

/**
 * @brief Inicializa (pide memoria) para los datos compartidos
 * @param argc es la cantidad de argumentos enviados
 * @param argv[] Es el arreglo que contiene cada argumento
 * @return puntero a datos compartidos o nulo de no poder inicializar.
 */
shared_data_t* init_shared_data(uint64_t argc, char* argv[]);

/**
 * @brief Reparte el trabajo para cada hilo según la cantidad de entradas e hilos deseados
 * @details Utiliza el operador modulo para para saber la cantidad de hilos que harán un trabajo más que los demás; divide el trabajo según la cantidad de entradas y designa un inicio y un fin (indice del arreglo de entradas) por la cual trabajará cada hilo.
 * @param private_data es un puntero a los datos privados
 */
void distribute_work(private_data_t* private_data);

/**
 * @brief Crea arreglo de hilos, reparte el trabajo y verifica la factorización de las entradas
 * @details designa la cantida de hilos a crear en caso de que sean más que las entradas ingresadas, crea el arreglo de hilos y el de datos privados. Reparte el trabajo de hilo e invoca la verificación para factorizar las entradas según el trabajo por hilo creado.
 * @param shared_data es un puntero a los datos compartidos.
 * @return entero que indica si hay o no error al crear los hilos.
 */
uint64_t create_pthreads(shared_data_t* shared_data);

#endif  // CONTROL_PTHREAD_H
