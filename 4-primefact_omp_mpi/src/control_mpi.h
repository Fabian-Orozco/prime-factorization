/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "array_int.h"
#include "reader.h"
#include "calculator.h"
#include "typographer.h"

/**
 * @brief inicia la inicializacion de la tecnología MPI
 * @details a partir de este metodo el programa es ejecutado
 * @param argc cantidad de argumentos pasados por linea de comandos
 * @param argv vector que contiene los argumentos
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t start_mpi(int argc, char* argv[]);

/**
 * @brief inicia la inicializacion de la tecnología MPI
 * @details a partir de este metodo el programa es ejecutado
 * @param process_count cantidad de procesos en el world
 * @param process_number numero de proceso que ejecuta el metodo
 * @param thread_count cantidad de hilos deseados por el usuario
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t start_process(int process_count, int process_number
  , uint64_t thread_count);

/**
 * @brief envia un arreglo con todas las entradas | MPI_Send
 * @param elements arreglo con todas las entradas
 * @param inputs_capacity capacidad de almacenaje del arreglo
 * @param process_count cantidad de procesos en el world
 * @param inputs_count cantidad de elementos contenidos por el arreglo
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t send_elements(int64_t* elements, uint64_t inputs_capacity
  , int process_count, uint64_t inputs_count);

/**
 * @brief distribuye el trabajo con mapeo por bloque
 * @param process_count cantidad de procesos en el world
 * @param process_array arreglo que sera llenado
 * @param start variable de cada proceso (inicio del mapeo)
 * @param finish variable de cada proceso (final del mapeo)
 * @param all_range arreglo que posee todos los bloques en pares ordenados
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t distribute_work_random(int process_count, uint64_t* process_array
  , uint64_t* start, uint64_t* finish, uint64_t* all_range);

/**
 * @brief libera la memoria de las estructuras pasadas por parametro
 * @param factores arreglo dinamico que se quiere liberar
 * @param entradas arreglo dinamico que se quiere liberar
 * @param inputs arreglo dinamico que se quiere liberar
 * @return entero | codigo error: 0 si fue exitoso
 */
uint64_t free_structures(array_int_t *factores, array_int_t *entradas
  , array_entrada_t* inputs);
