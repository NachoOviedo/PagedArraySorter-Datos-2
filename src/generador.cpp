#include <iostream>
#include <fstream>
#include <random>
using namespace std;
int main()
{
    //Obtenemos del usuario el tamaño de archivo a generar
    cout<<"Ingrese el tamano de el archivo: ";
    string sizeus;
    cin>> sizeus;
    // Depuracion eliminar
    cout<< sizeus << endl;

    int size;
    if (sizeus == "peque")
    {
        size = 5;
    } else if (sizeus == "medi")
    {
        size = 10;
    } else if (sizeus == "grande")
    {
        size = 15;
    } else
    {
        cout<<"Debe escribir una de las siguientes opciones peque, medi o grande"<<endl;
    }

    //Creacion o lectura del archivo de los numeros
    ofstream archivo("C:/Datos 2/PagedArraySorter-Datos-2/src/generados/NumerosRan.txt", ios::binary);
    if(archivo.fail())
    {
        cout<<"Error al abrir el archivo"<<endl;
        // Salida del programa por error
        exit(1);
    }
    // Semilla usando random_device
    random_device seed;

    // Motor Mersenne Twister inicializado con la semilla
    mt19937 Generador(seed());

    // Distribución: números enteros entre 0 y INT_MAX
    uniform_int_distribution<int> RandomNum(0, INT_MAX);

    for (int i = 0; i < size; i++)
    {
        int num = RandomNum(Generador);
        cout<<num<<endl;
        archivo.write((char*)&num, sizeof(num));
    }
    archivo.close();
    // Prueba de lectura para asegurarse de funcionamiento correcto Eliminar al terminar depuracion
    /*
    ifstream lector("C:/Datos 2/PagedArraySorter-Datos-2/src/generados/NumerosRan.txt", ios::binary);
    if(lector.fail())
    {
        cout << "Error al abrir" << endl;
        exit(1);
    }
    for(int i = 0; i < 5; i++) {
        int numR;
        lector.read(reinterpret_cast<char*>(&numR), sizeof(numR));
        cout << numR << endl;
    }
    lector.close();
    */

    return 0;
}