# PagedArraySorter-Datos-2
Proyecto de ordenamiento de archivos binarios grandes usando arreglos paginados en C++.

### Descripcion del sistema de desarrollo:
**Sistema operativo de desarrollo** Windows 11  
**Compilador** MinGW-GCC (mingw64 (por defecto de CLion))  
**CMake** 3.20 o superior  
**IDE recomendado usado durante el desarrollo** CLion

### Como ejecutar:
- mkdir cmake-build-debug
- cd cmake-build-debug
- cmake ..
- cmake --build .

### Generador de Archivos
Este se encarga de generar una lista de numeros desordenados entre 0 y INT max

#### Ejecusion
generador.exe -size TAMAÑO -output RUTA

##### Tamaños disponibles:
**TINY** **1000 enteros** ~4 KB  
**SMALL** **33 554 432 enteros** ~128 MB  
**MEDIUM** **67 108 864 enteros** ~256 MB
**LARGE** **134 217 728 enteros** ~512 MB
- Nota:  
-size corresponde al tamaño de archivo deseado  
-output la ruta donde desea que se genere el archivo


### Ordenador de Archivos
Este se encarga de tomar el archivo generado anteriormente y ordenarlo mediante un algoritmo  
indicado por el usuario en la ejecucion, ademas, este devuelve un archivo legible con los numeros  
ordnados y genera un CSV con estaditicas de ejecusion.

#### Ejecusion 
sorter.exe -input RUTA_ENTRADA -output RUTA_SALIDA -alg ALGORITMO 
-pageSize TAMAÑO_PÁGINA -pageCount CANTIDAD_PÁGINAS

- Nota:  
-**input** corresponde a la direccion del archivo construido en el generador  
 -**output** corresponde donde desea encontrar el archivo ordenado y legible  
-**alg** corresponde al proceso que desea emplear para ordenar el archivo generado  
-**pageSize** corresponde al la cantidad de enteros que caben por pagina  
-**pageCount** corresponde a la cantidad de paginas en memoria simultaneamente

#### Algoritmos disponibles
-**MergeSort** Funciona para todo tamaño de archivo  
-**RadixSort** Funciona para todo tamaño de archivo  
-**QuickSort** Funciona para tod tamaño de archivo  
-**ShellSort** Solo usar en archivos TYNI y SMALL  
-**CombSort** Solo usar en archivos TYNI y SMALL

#### Al finalizar su ejecusion

- Consola  
En consola se imprimiran detalles de ejecusion, durante el proceso apareceran
2 mensajes uno notificando que el archivo se pudo copiar, otro notificando que se pudo ordenar
y un tercero que imprimira estadisticas de la ejecusion.
Cual quier otro mensaje producido por un error indicara explicitamente cual a sido este.

- Archivos generados  
En la ruta -output se generaran 2 archicos uno con los numeros aleatorios generados durante la   
ejecusion del generador y otro con el mismo nombre asignado por la ruta establecida por el usuario  
pero .txt.
Ademas se creara un .csv en el disco local C con el nombre "RegistrosCSV.csv" donde se  
guardaran datos de ejecusion de cada uso del sorter (una linea nueva por ejecusion).

### Estructura del proyecto
PagedArraySorter-Datos-2/  
├── .gitignore  
├── CMakeLists.txt    
├── src/  
│   ├── generador.cpp        # Programa generador de archivos binarios  
│   ├── sorter.cpp           # Programa principal de ordenamiento  
│   ├── PagedArray.h         # Declaración de la clase PagedArray  
│   ├── PagedArray.cpp       # Implementación de PagedArray y lógica de paginación  
│   ├── SorterManager.h      # Gestión de algoritmos y métricas  
│   ├── MERGESORT.h          # Implementación de Merge Sort  
│   ├── QUICKSORT.h          # Implementación de Quick Sort  
│   ├── RADIXSORT.h          # Implementación de Radix Sort  
│   ├── SHELLSORT.h          # Implementación de Shell Sort  
│   ├── COMBSORT.h           # Implementación de Comb Sort  
│   ├── BUBBLESORT.h         # Implementación de Bubble Sort (descartado)  
│   ├── HEAPSORT.h           # Implementación de Heap Sort (descartado)  
│   ├── CYCLESORT.h          # Implementación de Cycle Sort (descartado)  
│   └── README.md  
└──  
- nota  
BubbleSort, HeapSort, CycleSort fueron descartados por ser inviables con archivos de prueba de menor tamaño 
que los implementados en e proyecto.

### Recomendacion
- Para iniciar prueba que todos los algoritmos esten funcionando corresctamente con un archivo TINY 
antes de pasar a un SMALL, MEDIUM o LARGE.
