
# Diseño de la solución

## **Descripción**

Tomando en cuenta que **las funciones de lectura, calculo e impresión deben estar separadas e invocarse en secuencia en ese orden** y que además **la factorización prima se calcula de manera concurrente**, tuve la disposición de hacerlo de la siguiente forma: con **un struct que almacena el valor, su categoria y un arreglo de factores para los enteros compuestos el cual se encargará de llenar cada hilo correspondiente utilizando una técnica de seguridad condicional (conditionally safe); por lo que el programa no utiliza herramientas de control de concurrencia como semáforos o mutex lo que hace que no haya exclusión mutua pero que mantenga una concurrencia y orden de impresión en los resultados de las entradas.**

Para comprender el patrón que buscan llevar el programa puede ver el diagrama o consultar el código en pseudocódigo:

- [Controlador del programa](./main.pseudo)
- [Lector de la entrada en datos](./reader.pseudo)
- [Controlador de los hilos](pthreads.pseudo)
- [Cálculos matemáticos](./calculator.pseudo)
- [Impresión de resultados](./typographer.pseudo)

Además puede visualizar una simulación de la estructura de datos utilizada más adelante.

---

## Estructura de datos

La estructura de datos utilizada es un arreglo dinámico de enteros de 64 bits de tamaño creado por el profesor Jeisson Hidalgo ([+info.](../README.md)) y adaptado con los ajustes necesarios para manejar los tipos de datos ya mencionados.

![Estructura del arreglo](./img/data_structure.png)

![UML](./img/arrayUML.png)

### **Ejemplo de entrada, proceso y salida:**

Archivo con tres líneas de datos (compuesto, primo e inválido):

~~~txt
100 
53
-150
-texto-
45
~~~

Diagrama con el siguiente llamado: `make; bin/primefact_pthread 2`

![Diagrama de memoria](./img/diagram.png)

---

Otras rutas:  
[README del proyecto](../README.md)
