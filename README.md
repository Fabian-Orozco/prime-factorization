# **Prime Factorization**

## **Problem Description**

This project has as its main problem the **factorization of positive integers**, since this is a repetitive and tedious task for both humans and traditional computers.

Considering **three categories of numbers**: one, prime and composite, we are looking for a way to factor them into prime components for small and large quantities of numbers at the same time, having as a priority the **use of openMP technology to parallelize the factorization together with MPI to perform it in a distributed way**.

### **Program Features:**

- **Programming language used:** C.
- **Communication with the user:** by standard output and input.
- **Valid values:** Positive numbers less than 2^63 (9223372036854775808).
- **Special values:** 0 and 1.
- **Responds to invalid values:** yes.
- **Form of factoring:** serial, concurrent (openMP) and distributed (MPI).

### **Objectives:**

- **Receive a list of integers** from standard input, this input can be redirected from a text file containing numbers.
- **Validate the arguments** the first argument will be the name of the program and the second will be the number of threads desired.
- **Validate each line of the list** as it may contain values that are not valid.
- **Distribute the tasks equally** so that the threads can work in parallel.
- **Calculate prime factorization** to composite numbers because the factors for prime numbers are only themselves.
- **Display by standard output a list with the numbers and their prime factors** using conditionally safe. Consider the case of being composite, otherwise it may include an error message for invalid or special values in the order they were entered.

---

## **User's manual**

### **Compilation:**

Use the following command: `make`.  
Example:

```bash
[fabian:primefact_omp_mpi]
$ make
mkdir -p build/
mpicc -c -Wall -Wextra -fopenmp -g -std=gnu11 -Isrc -MMD src/array_entrada.c -o build/array_entrada.o
mpicc -c -Wall -Wextra -fopenmp -g -std=gnu11 -Isrc -MMD src/entrada.c -o build/entrada.o
.
.
.

mpicc -Wall -Wextra -fopenmp -g -Isrc build/array_entrada.o build/array_int.o build/calculator.o build/control_mpi.o build/control_threads.o build/entrada.o build/main.o build/reader.o build/typographer.o -o bin/primefact_omp_mpi -lm
[fabian:primefact_omp_mpi]
$
```

### **Interactive execution:**

Use `mpiexec -np` next to the desired number of processes followed by the path and name of the executable with the desired threads for example: `mpiexec -np 3 bin/primefact_omp_mpi 5`, eventually, press `Enter` and the program will now be running waiting for data input.

Note: In case you do not enter a number, the program will take the available number of CPUs as the default number of threads and processes to perform the factorization.

#### **Data Entry**

Now enter each value (positive integer with range: less than 2^63) followed by a `Space` or `Enter` to perform its proper prime factorization.  
Finally press `Ctrl+D` to indicate the end of the entry. For example:

```bash
[fabian:primefact_omp_mpi]
$ mpiexec bin/primefact_omp_mpi 5
40 53 568 999 388

Execution time: 0.002330456s
40: 2^3 5
53: 53
568: 2^3 71
999: 3^3 37
388: 2^2 97
[fabian:primefact_omp_mpi]
$
```

### **Batch Execute:**

Use `mpiexec -np` next to the desired number of processes followed by the path and name of the executable with the desired threads e.g.: `mpiexec -np 3 bin/primefact_omp_mpi 5 <path/file.extension` replacing the path, name and extension of the text file to redirect to the standard input the desired file. This will take the numbers of the file as object to factor. For example:

```bash
[fabian:primefact_omp_mpi]
$ mpiexec -np 3 bin/primefact_omp_mpi 5 < tests/input000.txt

0: NA
2: 2
9: 3^2
10: 2 5
52: 2^2 13
81: 3^4
1000: 2^3 5^3
1024: 2^10
100: 2^2 5^2
113: 113
180: 2^2 3^2 5
```

donde _input000.txt_ contiene:

```txt
0
2
9
10
52
81
100
113
180
1000
1024
```

---

## **Credits**

**Author:** Fabián orozco chaves
**Contact:** <fabian.orozcochaves@ucr.ac.cr>

Adapted code file: **Dynamic array**.  
Modified the array to contain 64-bit signed integers instead of double values.

- **Author:** Jeisson Hidalgo
- **Contact:** <jeisson.hidalgo@ucr.ac.cr>
