/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#include <stdio.h>

#include "typographer.h"
#include "calculator.h"

/**
 * @brief Se encarga de la impresión de números compuestos.
 * @details Se invoca a la hora de imprimir un número compuesto, verifica que tenga factores e imprime la frecuencia de cada uno.
 * @code 
    if (entradas->elements[actual].categoria == COMPUESTO) {
      // Invoca a imprimir_compuesto(arg,arg2)
      imprimir_compuesto(&entradas->elements[actual]);
    }
 * @endcode
 * @param compuesto
 */
void imprimir_compuesto(entrada_t* compuesto) {
  // print(numero)
  printf("%" PRId64 ":", compuesto->value);
  size_t actual = 0;
  // imprime el factor, cuenta su frecuencia y la imprime si es mayorque 1.

  while (actual < compuesto->factors.count) {
    int64_t factor = compuesto->factors.elements[actual];
    printf(" %" PRId64, factor);
    int64_t frecuencia
    = contar_frecuencia(factor, &compuesto->factors, &actual);
    if (frecuencia > 1) {
      printf("^%" PRId64 , frecuencia);
    }
  }
  printf("\n");
}  // end procedure

/**
 * @brief Se encarga de la impresión de números que no son compuestos.
 * @details Se invoca a la hora de imprimir un número no compuesto, imprime según la categoría del valor ingresado.
 * @code 
  } else {
    // Sino ==> invoca a imprimir_invalido
    imprimir_invalido(&entradas->elements[actual]);
  }
 * @endcode
 * @param entrada es la entrada que se quiere imprimir (puede ser fuera de rango, texto, primo, negativo o especial)-
 */
void imprimir_invalido(entrada_t* entrada) {
  // Si está fuera de rango
  if (entrada->category == INVALID) {
    // print("invalid number")
    printf("invalid number\n");
  } else {  // Sino está fuera del rango
      // print(numero)
      printf("%" PRId64 ":", entrada->value);
      // Caso primo: print(factor)
      if (entrada->category == PRIME) {
          printf(" %" PRId64 "\n" , entrada->value);
        // Caso negativo: print("Num: invalid number")
      } else if (entrada->category == NEGATIVE) {
          printf(" invalid number\n");
          // Caso especial: print("NA")
      } else if (entrada->category == SPECIAL) {
          printf(" NA\n");
      }
    }
}

/**
 * @brief Se encarga de la impresión de resultados según la entrada de datos.
 * @details Imprime:
 * | Número: factor^frecuencia | si es compuesto con al menos un factor y frecuencia > 1
 * | Número : Número | si es primo
 * | Número: NA | si es 0 o 1
 * | invalid number | si se ingresó texto o un número fuera de rango (-2^63, ..., 2^63-1)
 * @code 
    imprimir(&entradas);
 * @endcode
 * @param entradas es el arreglo que contiene todas las entradas.
 */
void print_factorizations(array_entrada_t* entradas) {
  for ( size_t actual = 0; actual < entradas->count-1; ++actual ) {
    // Si es compuesto
    if (entradas->elements[actual].category == COMPOUND) {
      // Invoca a imprimir_compuesto(arg,arg2)
      imprimir_compuesto(&entradas->elements[actual]);
    } else {
      // Sino ==> invoca a imprimir_invalido
      imprimir_invalido(&entradas->elements[actual]);
    }
  }
}  // end procedure
