//
// Created by nacho on 26/3/2026.
//
#include <iostream>
#include <cstring>
#include "PagedArray.h"
#include "SorterManager.h"
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 11)
    {
        cout << "Error argumentos invalidos" << endl;
        return 1;
    }

    //Obtenmos direccion del archivo generado anteriormente
    string archivoO;
    // Obtenemos la ruta donde sera creado el archivo ordenado
    string archivoS;
    // Obtenemos el algoritmo a usar
    string algoritmo;
    //Obtenemos tamano de pagina
    int pageSize;
    //Obtenemos numero de paginas
    int pageCount;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-input") == 0)
        {
            archivoO = argv[i+1];
        }
        else if (strcmp(argv[i], "-output") == 0)
        {
            archivoS = argv[i+1];
        } else if (strcmp(argv[i], "-alg") == 0)
        {
            algoritmo = argv[i+1];
        } else if (strcmp(argv[i], "-pageSize") == 0) {
            pageSize = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "-pageCount") == 0) {
            pageCount = atoi(argv[i+1]);
        }
    }
    if (archivoO.empty() || archivoS.empty() || algoritmo.empty() || pageSize == 0 || pageCount == 0) {
        cout << "Error: argumentos invalidos" << endl;
        return 1;
    }

    FILE* archivoLec = fopen(archivoO.c_str(), "rb");
    FILE* archivoEsc = fopen(archivoS.c_str(), "wb");
    if (archivoLec == nullptr)
    {
        cout << "Error al abrir archivo " << archivoO << endl;
        return 1;
    }
    if (archivoEsc == nullptr)
    {
        cout << "Error al abrir archivo " << archivoS << endl;
        return 1;
    }

    //Buffer para pasar los datos
    int* buffer = new int[4096];

    size_t leidos = 0;
    while ((leidos = fread(buffer, sizeof(int), 4096, archivoLec)) > 0){
        fwrite(buffer, sizeof(int), leidos, archivoEsc);
    }
    cout << "Archivo copiado exitosamente" << endl;
    //Liberar memoria
    fclose(archivoLec);
    fclose(archivoEsc);
    delete [] buffer;

    FILE* archivo = fopen(archivoS.c_str(), "rb");
    fseek(archivo, 0, SEEK_END);
    long long tamanoArchivo = ftell(archivo);
    long long CantidadEnteros = tamanoArchivo / sizeof(int);
    fclose(archivo);

    //Creo el paged array
    PagedArray NewPagedArray(archivoS.c_str(), pageSize, pageCount, CantidadEnteros);

    auto inicio = chrono::steady_clock::now();
    SortManager(NewPagedArray, CantidadEnteros, algoritmo.c_str());
    cout << "Archivo ordenado exitosamente" << endl;
    auto fin = chrono::steady_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    string archivoTexto = archivoS + ".txt";

    FILE* ordenado = fopen(archivoS.c_str(), "rb");
    FILE* archivotxt = fopen(archivoTexto.c_str(), "w");

    if (ordenado == nullptr )
    {
        cout << "Error al abrir archivo " << archivoS << endl;
        return 1;
    }
    if ( archivotxt == nullptr)
    {
        cout << "Error al generar archivo legible" << endl;
        return 1;
    }
    // Numero a escribir en el archivo txt
    int numEsc;
    long long contador = 1;
    //4096 enteros * 11 disitos mas signo que pueden tener
    char* bufferTexto = new char[4096*12];
    int* bufferInts = new int[4096];
    int offset = 0;

    fread(&numEsc, sizeof(int), 1, ordenado);
    //Escribo el primer numero //Formato entero
    fprintf(archivotxt, "%d", numEsc);

    // Resto en bloques
    while (contador < CantidadEnteros) {
        int IntLeidos = fread(bufferInts, sizeof(int), 4096, ordenado);
        for (int i = 0; i < IntLeidos; i++) {
            offset += sprintf(bufferTexto + offset, ",%d", bufferInts[i]);
            // Escribir cuando el buffer esté casi lleno
            if (offset > 4096 * 11) {
                fwrite(bufferTexto, 1, offset, archivotxt);
                offset = 0;
            }
        }
        contador += IntLeidos;
    }
    // Escribir lo que queda en el buffer
    if (offset > 0) {
        fwrite(bufferTexto, 1, offset, archivotxt);
    }

    delete[] bufferInts;
    delete[] bufferTexto;
    fclose (archivotxt);
    fclose (ordenado);

    //Resumen
    cout << "Tiempo de ordenamiento: " << duracion << " ms" << endl;
    NewPagedArray.estadisicas(duracion, algoritmo, tamanoArchivo);
}