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
    long long PageFaults;     //Contador de Faultds
    long long PageHits;       //Contador de hits
    int NumArray;       //Total de enteros en el array
    int* ultimo;        //Registro de ultimo uso
    long long contador;       //Contador de accesos

    //Metodos declarados
    //Metodo para guardar la pagina a disco
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
        contador = 0;
        frames = new int*[NumPage];

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
    void estadisticas(long long duracion, string algoritmo, long long tamano, bool testing)
    {
        cout<< "____________estadisticas____________"<<endl;
        cout<< "Cantidad de paginas en memoria: " << NumPage<<endl;
        cout<< "Dimencion de pagina: " << PageSize<<endl;
        cout<< "Page Hits: "<<PageHits<<endl;
        cout<< "Page Faults: "<<PageFaults<<endl;
        cout<< "Cantidad de paginas accedidas: "<< contador<<endl;

        if (testing)
        {
            estadisticasCSV(duracion, algoritmo, tamano);
        }
    }

    void estadisticasCSV(long long duracion, string algoritmo, long long tamano){
        const char* rutaCSV = "C:\\RegistrosCSV.csv";

        // Verificar si el archivo existe para saber si escribir encabezado
        FILE* verificar = fopen(rutaCSV, "r");
        bool esNuevo = (verificar == nullptr);
        if (!esNuevo) fclose(verificar);

        // Abrir en modo append
        FILE* csv = fopen(rutaCSV, "a");
        if (csv == nullptr) {
            cout << "Error al abrir archivo CSV" << endl;
            return;
        }

        // Escribir encabezado si es nuevo
        if (esNuevo) {
            fprintf(csv, "Algoritmo;PageSize;PageCount;TamanoArchivo;TiempoMs;PageFaults;PageHits;TotalAccesos\n");
        }

        // Escribir fila de datos
        fprintf(csv, "%s;%d;%d;%lld;%lld;%lld;%lld;%lld\n",
            algoritmo.c_str(),
            PageSize,
            NumPage,
            tamano,
            duracion,
            PageFaults,
            PageHits,
            contador);

        fclose(csv);
    }
};

inline void mySwap(PagedArray& arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}


#endif //PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H