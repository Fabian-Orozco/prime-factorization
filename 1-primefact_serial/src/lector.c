/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lector.h"
#include "matematico.h"


/**
 * @brief Almacena la entrada según su categoría.
 * @details Crea e inicializa el struct entrada y lo almacena en el arreglo de entradas.
 * @code 
 * almacenar_entrada(entradas, valor, categoria);
 * @endcode
 * @param entradas Es el arreglo que contiene cada entrada con sus atributos.
 * @param valor Es el valor de entrada.
 * @param categoria Es la categoria de la entrada.
 */
int64_t almacenar_entrada(array_entrada_t* entradas, int64_t valor
, int64_t categoria) {
  entrada_t nueva;
  if (categoria == NO_VALIDO)
    entrada_nan_init(&nueva, NO_VALIDO);
  else
    entrada_init(&nueva, valor, categoria);
  array_entrada_append(entradas, &nueva);
  return 1;
}

/**
 * @brief Valida la entrada para clasificar lo que entra por ella.
 * @details Se utiliza para ignorar entradas inválidas o no contempladas como enteros. En caso de que la entrada sea válida, la clasifica y agrega a la estructura de datos correspondiente. 
 * @code 
 * validar_entrada();
 * @endcode
 * @param input Es la entrada de la que se quieren leer los archivos
 * @param entradas Es el arreglo que contiene cada entrada con sus atributos
 * @remark Se verifica que el input exista, de no ser así sería un fallo de programador, por lo que el programa se aborta.
 Además se verifica la variable global errno para verificar que no se escriban cosas indebidas en ella, de ser así indicaría que el valor ingresado por la entrada está fuera de rango y lo clasifica en categorías y valores como NO_VALIDO.
 */
int64_t validar_entrada(FILE* input, array_entrada_t* entradas) {
  assert(input);

  int64_t valor = 0;
  while ((feof(input) == 0)) {
    if (fscanf(input, "%" SCNd64, &valor) == 1) {  // entero
      if (errno == 0) {  // dentro del rango
        // verifique categoria, cree e inicialice struct entrada
        // puede ser: negativo, primo o compuesto
        int64_t categoria = asignar_categoria(valor);
        almacenar_entrada(entradas, valor, categoria);
      } else {  // fuera de rango
        almacenar_entrada(entradas, NO_VALIDO, NO_VALIDO);
        errno = 0;
      }
    } else {  // texto
      almacenar_entrada(entradas, NO_VALIDO, NO_VALIDO);
      fscanf(input, "%*s");
    }
  }
  return 0;
}  // end procedure

