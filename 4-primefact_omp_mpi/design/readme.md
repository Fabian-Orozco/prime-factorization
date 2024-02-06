
# Diseño de la solución

## **Descripción**

Tomando en cuenta que **las funciones de lectura, calculo e impresión deben estar separadas e invocarse en secuencia en ese orden** y que además **la factorización prima se calcula de manera concurrente**, tuve la disposición de hacerlo de la siguiente forma: con **un arreglo de elementos que se reparten por bloques para después ser repartidos de forma dinámica y aleatoria a cada proceso con la cantidad de hilos adecuada y/o suministrada por el usuario** manteniendo una concurrencia y orden de impresión en los resultados de las entradas mediante la tecnología declarativa de openMP y una mejora en rendimiento mediante una distribución con la tecnología MPI.

Para comprender el patrón que buscan llevar el programa puede ver el diagrama o consultar el código en pseudocódigo:

- [Controlador del programa](./main.pseudo)
- [Lector de la entrada en datos](./reader.pseudo)
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
