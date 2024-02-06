/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#include "control_pthreads.h"
#include "entrada.h"
#include "calculator.h"

int64_t is_compound(int64_t value) {
  // Si se puede dividir en un numero distinto a él (excepto el 2)
  int64_t factor = 2;
  if (value == 2) return 0;
  while ( factor < value && factor != value ) {
    if ((value % factor) == 0) {
      // Devuelva Verdadero (1).
      return 1;
    } else {
      ++factor;
    }
  }
  // Sino devuelva Falso (0)
  return 0;
}  // end procedure

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

/**
 * @brief Calcula la raíz cuadrada de un valor pasado por parámetro.
 * @details Basado en: <http://rosettacode.org/wiki/Isqrt_(integer_square_root)_of_X#C.2B.2B>
 * @code 
 * for (int64_t factor = 3; factor <= isqrt(valor); factor += 2) {codeBlock}
 * @endcode
 * @param value Es el valor del que se quiere calcular la raíz cuadrada.
 */
int64_t isqrt(int64_t value) {
  if (value >= 9223372036854775807) return value;
  int64_t q = 1;
  while (q <= value)
    q <<= 2;
  int64_t r = 0;
  while (q > 1) {
    q >>= 2;
    int64_t t = value - r - q;
    r >>= 1;
    if (t >= 0) {
      value = t;
      r += q;
    }
  }
  return r;
}

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
  for (int64_t factor = 3; factor <= isqrt(value); factor += 2) {
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

void* verificar_factorizacion(void* data) {
  //   private_data := (cast) data
  private_data_t* private_data = (private_data_t*) data;

  // shared_data := private_data->shared_data
  shared_data_t* shared_data = private_data->shared_data;

  // entradas := shared_data->entradas
  array_entrada_t* entradas = shared_data->entradas;

  uint64_t beginning = private_data->beginning;
  uint64_t end = private_data->end;

  // for private_data->beginning to private_data->fin do
  for ( ; beginning < end; ++beginning) {
    // if entradas[beginning] == COMPUESTO
     if (entradas->elements[beginning].category == COMPOUND)
     // factorizar_compuesto(entrada)
       factorizar_compuesto(&entradas->elements[beginning]);
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
