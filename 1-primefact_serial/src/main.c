/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array_entrada.h"
#include "array_int.h"
#include "entrada.h"
#include "lector.h"
#include "matematico.h"
#include "tipografo.h"

#define ERROR_MAIN_INIT_ARRAY 11
#define ERROR_MAIN_IN 21

/**
 * @brief main del programa
 * @details Crea y destruye el arreglo de struct, invoca la validación de entrada(lector.h) para almacenar los datos en cada struct e invoca su verificación para factorizarlos(matematico.h). Por ultimo invoca a imprimir para que muestre los datos del struct(tipografo.h).
 */
// procedure main(void)
int main(void) {
  int64_t error = 0;
  array_entrada_t entradas;
  error = array_entrada_init(&entradas);
  if (!error) {
    error = validar_entrada(stdin, &entradas);
    if (!error) {
      struct timespec start_time, finish_time;
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      verificar_factorizacion(&entradas);

      clock_gettime(CLOCK_MONOTONIC, &finish_time);
      double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
      fprintf(stderr,"Execution time: %.9lfs\n", elapsed_time);
      
    } else {
      fprintf(stderr, "%i" "no se pudo validar la entrada", ERROR_MAIN_IN);
    }
    imprimir(&entradas);
    array_entrada_destroy(&entradas);
  } else {
    fprintf(stderr, "%i" "no se pudo inicializar el array"
    , ERROR_MAIN_INIT_ARRAY);
  }
  return EXIT_SUCCESS;
}  // end procedure
