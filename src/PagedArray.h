//
// Created by nacho on 7/3/2026.
//

#ifndef PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H
#define PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H

#include <cstdio>
#include <iostream>
using namespace std;

class PagedArray
{
    //Variables de la clase
private:
    int PageSize;       //Cantidad de enteros por pagina
    int NumPages;       //Frames disponibles
    bool* DirtyBite;    //Saber si hay que registrar cambios
    int** frames;       //Matriz de frames
    int* FramePages;    //Registro de paginas en frames
    FILE* file;         //Puntero al archivo en disco
    int PageFaults;     //Contador de Faultds
    int PageHits;       //Contador de hits
    int NumArray;       //Total de enteros en el array
    int* ultimo;        //Registro de ultimo uso
    int contador;       //Contador de accesos

    //Metodos declarados
    void Cargador(int pageNum, int frameIndex);
    //Metodo para escoger la pagina que se va a guardar en disco
    int LRU();

public:
    //Constructor
    PagedArray(const char* filePath, int pageSize, int numPages, int numArray)
    {
        //asignacion de variables
        PageSize = pageSize;
        NumPages = numPages;
        NumArray = numArray;
        PageFaults = 0;
        PageHits = 0;
        file = fopen(filePath, "r+b");
        frames = new int*[NumPages];
        contador = 0;
        for(int i = 0; i < NumPages; i++) {
            frames[i] = new int[PageSize];
        }
        DirtyBite = new bool[NumPages];
        for(int i = 0; i < NumPages; i++)
        {
            DirtyBite[i] = false;
        }
        FramePages = new int[NumPages];
        for (int i = 0; i < NumPages; i++)
        {
            FramePages[i] = -1;
        }
        ultimo = new int[NumPages];
        for (int i = 0; i < NumPages; i++)
        {
            ultimo[i] = 0;
        }
    };
    // Destructor
    ~PagedArray()
    {
        //Limpia la memoria del heap
        delete[] FramePages;
        delete[] DirtyBite;
        for (int i = 0; i < NumPages; i++)
        {
            delete[] frames[i];
        }
        delete[] frames;
        delete[] ultimo;
        fclose(file);
    };
    int& operator[](int index) {
        int NumPagina = index / PageSize;
        int PosPagina = index % PageSize;

        for (int i = 0; i < NumPages; i++)
        {
            if (FramePages[i] == NumPagina)
            {
                PageHits++;
                return frames[i][PosPagina];
            }
        }
        PageFaults++;
        return frames[0][PosPagina];
    }
};

#endif //PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H