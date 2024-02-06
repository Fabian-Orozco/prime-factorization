/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#ifndef READER_H
#define READER_H

#include "array_entrada.h"
// #include "array_int.h"

/**
 * @brief Valida la entrada para clasificar lo que entra por ella.
 * @details Se utiliza para ignorar entradas inválidas o no contempladas como enteros. En caso de que la entrada sea válida, la clasifica y agrega a la estructura de datos correspondiente. 
 * @code 
 * error = validar_entrada(stdin, entradas);
 * @endcode
 * @param input Es la entrada de la que se quieren leer los archivos
 * @param entradas Es el arreglo que contiene cada entrada con sus atributos
 * @remark Se verifica que el input exista, de no ser así sería un fallo de programador, por lo que el programa se aborta.
 Además se verifica la variable global errno para verificar que no se escriban cosas indebidas en ella, de ser así indicaría que el valor ingresado por la entrada está fuera de rango y lo clasifica en categorías y valores como NO_VALIDO.
 */
int64_t validar_entrada(FILE* input, array_int_t* entradas);

/**
 * @brief Valida los argumentos para saber la cantidad de threads requeridos
 * @details Se utiliza para designar el tamaño disponilbe de cpus disponibles para trabajar con la misma cantidad de threads por defecto. Si la entrada es un valor válido designa esa cantidad de threads.
 * @code 
 * if (shared_data) {
    shared_data->thread_count = validar_argumentos(argc, argv);
    return shared_data;
  }
 * @endcode
 * @param argc es la cantidad de argumentos enviados
 * @param argv[] Es el arreglo que contiene cada argumento
 * @remark el número por defecto de hilos será la cantidad de cpus disponibles
 */
uint64_t validar_argumentos(uint64_t argc, char* argv[]);

#endif  // READER_H
