/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#include "control_pthreads.h"
#include "entrada.h"
#include "calculator.h"

#include "math.h"


int64_t assign_category(int64_t value) {
  // Devuelve -2 si el valor es 1 o 0
  if (value == 1 || value == 0) {
    return SPECIAL;
    // Devuelve -3 si el valor es negativo
  } else if (value < 0) {
    return NEGATIVE;
    // Devuelve -5 si el valor es compuesto
  } else if (is_compound(value)) {
    return COMPOUND;
    // Devuelve -4 si el valor es primo
  } else {
    return PRIME;
  }
}  // end procedure

int64_t is_compound(int64_t value) {
  // Si se puede dividir en un numero distinto a él (excepto el 2)
  int64_t factor = 2;
  if (value == 2) return 0;
  if (value % 2 == 1) return 1;
  while ( factor <  sqrt((double)value) && factor != value ) {
    if ((value % factor) == 0) {
      // Devuelva Verdadero (1).
      return 1;
    } else {
      factor += 2;
    }
  }
  // Sino devuelva Falso (0)
  return 0;
}  // end procedure

/**
 * @brief Realiza la factorización prima de números compuestos.
 * @details Basado en: <https://stackoverflow.com/a/43556849>
 * Se llama cuando se desean calcular los factores de los enteros compuestos.
 * Descompone cada valor siguiendo un algoritmo tomado de la web el cuál se basa en la Criba de Eratóstenes.
 * @code
 * if (entradas->elements[actual].categoria == COMPOUND)
      factorizar_compuesto(&entradas->elements[actual]);
  }
 * @endcode
 * @param compuesto es la entrada que se quiere factorizar y almacenar en su arreglo de factores, dichos factores.
 */
void factorizar_compuesto(entrada_t* compuesto) {
  int64_t value = compuesto->value;
  // Divide entre 2 al máximo y agrega los factores al arreglo de factores.
  while (value % 2 == 0) {
    entrada_append_factor(compuesto, 2);
    value /= 2;
  }
  // Itera en incrementos de 2 desde 3 hasta la raiz del número (inclusive).
  for (int64_t factor = 3; factor <= sqrt((double) value); factor += 2) {
    // Mientras sea divisible entre el factor actual
    while ( (value % factor) == 0 ) {
      // Agrega el factor al arreglo de factores.
      entrada_append_factor(compuesto, factor);
      value /= factor;
    }
  }
  // Si el valor es mayor a dos quiere decir que se llegó a un valor primo
  if (value > 2) {
    entrada_append_factor(compuesto, value);
  }
}  // end procedure

void* verificar_factorizacion(shared_data_t* shared_data, uint64_t unit) {
  if (shared_data->entradas->elements[unit].category == COMPOUND) {
     // factorizar_compuesto(entrada)
       factorizar_compuesto(&shared_data->entradas->elements[unit]);
  }
  return NULL;
}  // end procedure

int64_t contar_frecuencia(int64_t factor, array_int_t* factors
, size_t* actual) {
  int64_t frecuencia = 0;
  // Mientras factores[posicion] sea igual a factor: aumente la frecuencia
  while (*actual < factors->count
  && factors->elements[*actual] == factor) {
    ++frecuencia;
    ++(*actual);
  }
  // Retorne la frecuencia
  return frecuencia;
}  // end procedure
