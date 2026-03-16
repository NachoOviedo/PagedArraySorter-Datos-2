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
    int NumPage;       //Frames disponibles
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
        NumPage = numPages;
        NumArray = numArray;
        PageFaults = 0;
        PageHits = 0;
        file = fopen(filePath, "r+b");
        frames = new int*[NumPage];
        contador = 0;
        for(int i = 0; i < NumPage; i++) {
            frames[i] = new int[PageSize];
        }
        DirtyBite = new bool[NumPage];
        for(int i = 0; i < NumPage; i++)
        {
            DirtyBite[i] = false;
        }
        FramePages = new int[NumPage];
        for (int i = 0; i < NumPage; i++)
        {
            FramePages[i] = -1;
        }
        ultimo = new int[NumPage];
        for (int i = 0; i < NumPage; i++)
        {
            ultimo[i] = 0;
        }
    };
    // Destructor
    ~PagedArray()
    {
    for (int i = 0; i < NumPage; i++) {
        if (DirtyBite[i] == true) {
            fseek(file, FramePages[i] * PageSize * sizeof(int), SEEK_SET);
            fwrite(frames[i], sizeof(int), PageSize, file);
        }
    }
        //Limpia la memoria del heap
        delete[] FramePages;
        delete[] DirtyBite;
        for (int i = 0; i < NumPage; i++)
        {
            delete[] frames[i];
        }
        delete[] frames;
        delete[] ultimo;
        fclose(file);
    };
    int& operator[](int index) {
        //Determina el numero de pagina que es
        int NumPagina = index / PageSize;
        //Determina la posicion de la pagina
        int PosPagina = index % PageSize;
        //Busco el frame en memoria
        for (int i = 0; i < NumPage; i++)
        {
            if (FramePages[i] == NumPagina)
            {
                //Actulizo ultima vez que se accedio al frame
                ultimo[i] = contador++;

                PageHits++;
                //Actualizo indicador de acceso
                DirtyBite[i] = true;
                return frames[i][PosPagina];
            }
        }

        PageFaults++;
        int FrameRemplazo = -1;
        //Busco un frame vacio
        for (int i = 0; i < NumPage; i++)
        {
            if (FramePages[i] == -1)
            {
                FrameRemplazo = i;
            }
        }
        //No hay frame vacio, asigno uno existente para remplzar
        if (FrameRemplazo == -1)
        {
            FrameRemplazo = LRU();
        }
        //Cargo el exitente en disco
        Cargador(NumPagina, FrameRemplazo);
        //Actualizo la ultima vez que se accedio al frame
        ultimo[FrameRemplazo] = contador++;
        //Actualizo indicador de acceso
        DirtyBite[FrameRemplazo] = true;
        //Remplazo el frame por el escogido
        return frames[FrameRemplazo][PosPagina];
    }
    void estadisicas(){
        cout<< "____________estadisticas____________"<<endl;
        cout<< "Cantidad de paginas en memoria: " << NumPage<<endl;
        cout<< "Dimencion de pagina: " << PageSize<<endl;
        cout<< "Page Hits: "<<PageHits<<endl;
        cout<< "Page Faults: "<<PageFaults<<endl;
        cout<< "Cantidad de paginas accedidas: "<< contador<<endl;

    };
};


#endif //PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H