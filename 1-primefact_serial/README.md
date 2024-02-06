# **Prime Factorization**

## **Problem Description**

This project's main problem is **factoring positive integers** since this is a repetitive and tedious task for both humans and traditional computers.

Considering **three categories of numbers**: one, prime and composite, we look for a way to factorize them into prime components for small and large quantities of numbers at the same time, taking as priority the **correctness of the algorithm** used. so that it works effectively.

### **Program Features:**

- **Programming language used:** C.
- **Communication with the user:** through standard output and input.
- **Valid values:** positive numbers less than 2^63 (9223372036854775808).
- **Special values:** 0 and 1.
- **Responds to invalid values:** yes.
- **Form of factoring:** serial.

### **Goals:**

- **Receive a list of integers** from standard input, this input may be redirected from a text file containing numbers.
- **Validate each line in the list** as it may contain values that are not valid.
- **Calculate the prime factorization** to the composite numbers because the factors for the prime numbers are only themselves.
- **Show through standard output a list with the numbers and their prime factors** if it is composite, in other cases it may include an error message for invalid or special values in the order in which they were entered.

---

## **User manual**

### **Compilation:**

Use the following command: `make`
Example:

```bash
[fabian:primefact_serial]$ make
mkdir -p build/
cc -c -Wall -Wextra -g -std=gnu11 -Isrc -MMD src/array_int.c -o build/array_int.o
cc -c -Wall -Wextra -g -std=gnu11 -Isrc -MMD src/lector.c -o build/lector.o
cc -c -Wall -Wextra -g -std=gnu11 -Isrc -MMD src/main.c -o build/main.o
cc -c -Wall -Wextra -g -std=gnu11 -Isrc -MMD src/matematico.c -o build/matematico.o
cc -c -Wall -Wextra -g -std=gnu11 -Isrc -MMD src/tipografo.c -o build/tipografo.o
mkdir -p bin/
cc -Wall -Wextra -g -Isrc build/array_int.o build/lector.o build/main.o build/matematico.o build/tipografo.o -o bin/primefact_serial -lm
[fabian:primefact_serial]$
```

### **Interactive execution:**

Use the following command: `bin/primefact_serial`, then press `Enter` and the program will now be running waiting for data input.

#### **Data entry**

Now enter each value (positive integer with range: less than 2^63) followed by a `Space` or `Enter` to perform its proper prime factorization.
Finally press `Ctrl+D` to indicate the end of the entry. For example:

```bash
[fabian:primefact_serial]$ bin/primefact_serial
40 53 578 999 388

40: 2^3 5
53:53
578: 2 17^2
999: 3^3 37
388: 2^2 97
[fabian:primefact_serial]$
```

### **Batch execution:**

Use the command: `bin/primefact_serial < path/file.extension` replacing the path, name and extension of the text file to redirect the desired file to standard input. In this way, the numbers in the file will be taken as an object to factor. For example:

```bash
[fabian:primefact_serial]$ bin/primefact_serial < test/testF/inputF1.txt
100: 2^2 5^2
2:2
-1: invalid number
2:2
invalid number
3:3
invalid number
2:2
18: 2 3^2
[fabian:primefact_serial]$
```

where _inputF1.tx_ contains:

```txt
100
2
-1
2
.
3
qeroij
2
18
```

![input/output](./design/inputOutput.png)

---

## **Credits**

**Author:** Fabián orozco chaves
**Contact:** <fabian.orozcochaves@ucr.ac.cr>

Adapted code file: **Dynamic fix**
The array was modified to contain signed 64-bit integers instead of double values.

- **Author:** Jeisson Hidalgo
- **Contact:** <jeisson.hidalgo@ucr.ac.cr>
- **Files:** [array_int.h](./src/array_int.h) | [array_int.c](./src/array_int.c)
- [Repository](https://git.ucr.ac.cr/JEISSON.HIDALGO/concurrente21a-jeisson_hidalgo/-/tree/master/taller/stats/src)

---

Other routes:
[Solution Design](./design/readme.md)
