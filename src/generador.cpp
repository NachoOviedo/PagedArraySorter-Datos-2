#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
    //Validacion de informacion correcta
    if(argc != 5)
    {
        cout << "Error argumentos invalidos" << endl;
        return 1;
    }

    //Obtenemos del usuario el tamaño de archivo a generar
    string sizeus;
    // Obtenemos la ruta donde sera creado el archivo
    string path;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-size") == 0)
        {
            sizeus = argv[i+1];
        }
        else if (strcmp(argv[i], "-output") == 0)
        {
            path = argv[i+1];
        }
    }

    map<string, long long> pesos;
                    // ll anuncia que es long long
    pesos ["TINY"] = 1000 * sizeof(int);
    pesos ["SMALL"] = 32ll * 1024 * 1028;  //32 Mb
    pesos ["MEDIUM"] = 64ll * 1024 * 1024; //64 Mb
    pesos ["LARGE"] = 128ll * 1024 * 1024;  //128 Mb

    //Se establece el tamano apartir de la entrada del usuario
    long long size;
    auto buscador = pesos.find(sizeus);
    if (buscador != pesos.end())
    {
        size = buscador->second;
    } else {
        cout<< "Tamaño ingresado invalido";
        return 1;
    }

    //Creacion o lectura del archivo de los numeros
    ofstream archivo(path, ios::binary);
    if(archivo.fail())
    {
        cout<<"Error al abrir el archivo"<<endl;
        // Salida del programa por error
        exit(1);
    }
    //Generador de numeros aleatorios
    // Semilla usando random_device
    random_device seed;
    // Motor Mersenne Twister inicializado con la semilla
    mt19937 Generador(seed());
    // Establece que solo se generen numeros enteros entre 0 y INT_MAX
    uniform_int_distribution<int> RandomNum(0, INT_MAX);

    //Puntero del buffer para ecribir por bloques
    long long BufferSize = size/100/sizeof(int);
    int* buffer = new int[BufferSize];


    //ciclo de escritura por bloques
    long long BytesPorEscribir = size;
    long long BytesEscritos = 0;

    while(BytesEscritos < BytesPorEscribir)
    {
        long long BytesRestantes = BytesPorEscribir - BytesEscritos;
        //Seleccion de cantidad de enteros por escribir en buffer
        int enteros;
        if (BytesRestantes/(long long)sizeof(int) <= BufferSize)
        {
            enteros = BytesRestantes/(long long)sizeof(int);
        } else
        {
            enteros = BufferSize;
        }

        //Llenar buffer
        for (int i = 0; i < enteros; i++){
            buffer[i] = RandomNum(Generador);
        }
        //Escribir Buffer
        //                  Puntero al primer elemento     Tamano en bytes a escribir
        archivo.write((char*)buffer,              enteros * sizeof(int));
        // Actualizar BytesEscritos
        BytesEscritos += enteros * sizeof(int);
    }
    archivo.close();
    delete[] buffer;
    cout << "Archivo tamano " << sizeus <<" " << "generado exitosamente" << endl;
    return 0;
}