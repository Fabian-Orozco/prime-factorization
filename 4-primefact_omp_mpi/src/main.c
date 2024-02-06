/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "array_entrada.h"
#include "array_int.h"
#include "control_threads.h"
#include "entrada.h"
#include "reader.h"
#include "calculator.h"
#include "typographer.h"
#include "control_mpi.h"

/**
 * @brief main del programa
 * @details invoca al controlador de mpi para que realice el flujo del programa
 */
// procedure main(void)
int main(int argc, char* argv[]) {
  uint64_t error = 0;
  error = start_mpi(argc, argv);
  return error;
}  // end procedure
