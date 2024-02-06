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

void print_structure(array_entrada_t* entradas) {
  printf("printS\n");
  for (size_t actual = 0; actual < entradas->count; ++actual) {
    printf("cat: %li y val: %li\n", (entradas->elements)[actual].category
      , (entradas->elements)[actual].value);
  }
}

void print_factorizations(array_entrada_t* entradas) {
  for ( size_t actual = 0; actual < entradas->count; ++actual ) {
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

void imprimaArreglo(array_int_t* entradas) {
  for (uint64_t i = 0; i < entradas->count-2; i += 2) {
    fprintf(stderr, "%"PRId64 ":%"PRId64 "\n", entradas->elements[i]
      , entradas->elements[i+1]);
  }
}

void imprimaArreglo2(int64_t* elements, uint64_t count) {
  for (uint64_t i = 0; i < count; i += 2) {
    fprintf(stderr, "%"PRId64 ":%"PRId64 "\n", elements[i]
      , elements[i+1]);
  }
}
