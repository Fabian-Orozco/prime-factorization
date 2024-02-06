/**
 * Copyright [2021] <fabian.orozcochaves@ucr.ac.cr>
 */
#include <math.h>

#include "entrada.h"
#include "matematico.h"


/**
 * @brief Verifica si un numero es compuesto o no.
 * @details Utiliza el operador módulo para ver si se puede dividir en al menos un número distinto a él mismo; de ser así, se confirma que es compuesto.
 * @code
 * if ( es_compuesto(valor) ) {
    return COMPUESTO;
 * @endcode
 * @param valor Es el entero que se quiere verificar.
 * @return 1 en caso de que el número sea compuesto, en caso contrario 0.
 */
int64_t es_compuesto(int64_t valor) {
  // Si se puede dividir en un numero distinto a él (excepto el 2)
  int64_t factor = 2;
  if (valor == 2) return 0;
  while ( factor < valor && factor != valor ) {
    if ((valor % factor) == 0) {
      // Devuelva Verdadero (1).
      return 1;
    } else {
      ++factor;
    }
  }
  // Sino devuelva Falso (0)
  return 0;
}  // end procedure

/**
 * @brief Asigna una banderilla que categoriza al entero.
 * @details Se utiliza para clasificar el entero en una categoría.
 * @code 
 * int64_t categoria = asignar_categoria(valor);
 * @endcode
 * @param valor Es el entero que se quiere categorizar.
 * @return La categoría(banderilla) a la que pertenece: 
 * -2 (NEGATIVO) si el entero es menor que 0.
 * -3 (ESPECIAL) si el entero es 1 o 0.
 * -4 (PRIMO) si el entero es primo.
 * -5 (COMPUESTO) si el entero es compuesto.
 */
int64_t asignar_categoria(int64_t valor) {
  // Devuelve -2 si el valor es 1 o 0
  if (valor == 1 || valor == 0) {
    return ESPECIAL;
    // Devuelve -3 si el valor es negativo
  } else if (valor < 0) {
    return NEGATIVO;
    // Devuelve -5 si el valor es compuesto
  } else if (es_compuesto(valor)) {
    return COMPUESTO;
    // Devuelve -4 si el valor es primo
  } else {
    return PRIMO;
  }
}  // end procedure

/**
 * @brief Calcula la raíz cuadrada de un valor pasado por parámetro.
 * @details Basado en: <http://rosettacode.org/wiki/Isqrt_(integer_square_root)_of_X#C.2B.2B>
 * @code 
 * for (int64_t factor = 3; factor <= isqrt(valor); factor += 2) {codeBlock}
 * @endcode
 * @param valor Es el valor del que se quiere calcular la raíz cuadrada.
 */
int64_t isqrt(int64_t valor) {
  if (valor >= 9223372036854775807) return valor;
  int64_t q = 1;
  while (q <= valor)
    q <<= 2;
  int64_t r = 0;
  while (q > 1) {
    q >>= 2;
    int64_t t = valor - r - q;
    r >>= 1;
    if (t >= 0) {
      valor = t;
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
 * if (entradas->elements[actual].categoria == COMPUESTO)
      factorizar_compuesto(&entradas->elements[actual]);
  }
 * @endcode
 * @param compuesto es la entrada que se quiere factorizar y almacenar en su arreglo de factores, dichos factores.
 */
void factorizar_compuesto(entrada_t* compuesto) {
  int64_t valor = compuesto->valor;
  while (valor % 2 == 0) {
    entrada_append_factor(compuesto, 2);
    valor /= 2;
  }
  for (int64_t factor = 3; factor <= isqrt(valor); factor += 2) {
    while ( (valor % factor) == 0 ) {
      entrada_append_factor(compuesto, factor);
      valor /= factor;
    }
  }
  if (valor > 2) {  // Se llegó a un factor primo.
    entrada_append_factor(compuesto, valor);
  }
}

/**
 * @brief Verifica la categoría del número y si es debido, invoca a factorizar.
 * @details Se utiliza para realizar la factorización a los números debidos.
 * @code 
 * verificar_factorizacion(&entradas);
 * @endcode
 * @param entradas Es el arreglo que contiene todos las entradas.
 */
void verificar_factorizacion(array_entrada_t * entradas) {
  for (size_t actual = 0; actual < entradas->count; ++actual) {
    if (entradas->elements[actual].categoria == COMPUESTO)
      factorizar_compuesto(&entradas->elements[actual]);
  }
}  // end procedure


/**
 * @brief Cuenta y retorna la cantidad de veces que se repite el factor
 * @details Se utiliza para la impresión de los factores de un entero
 * @code 
 * 
 * @endcode
 * @param factor Es el factor del que se quiere saber la frecuencia 
 * @param factores Es el arreglo que contiene los factores de todos los enteros.
 * @param actual Representa la posición del arreglo de factores por la que se quiere iterar.
 * @return La cantidad de veces que se repite el factor
 */
int64_t contar_frecuencia(int64_t factor, array_int_t* factores
, size_t* actual) {
  int64_t frecuencia = 0;
  // Mientras factores[posicion] sea igual a factor: aumente la frecuencia
  while (*actual < factores->count
  && factores->elements[*actual] == factor) {
    ++frecuencia;
    ++(*actual);
  }
  // Retorne la frecuencia
  return frecuencia;
}  // end procedure
