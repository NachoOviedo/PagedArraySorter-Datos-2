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
    int PageSize;
    int NumPages;
    bool* DirtyBite;
    int** frames;
    int* FramePages;
    FILE* file;
    int PageFaults;
    int PageHits;
    int NumElementos;

public:
    //Constructor
    PagedArray(const char* filePath, int pageSize, int numPages, int numElementos)
    {
        PageSize = pageSize;
        NumPages = numPages;
        NumElementos = numElementos;
        PageFaults = 0;
        PageHits = 0;
        file = fopen(filePath, "r+b");
        frames = new int*[NumPages];
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
    };
    // Destructor
    ~PagedArray()
    {
        delete[] FramePages;
        delete[] DirtyBite;
        for (int i = 0; i < NumPages; i++)
        {
            delete[] frames[i];
        }
        delete[] frames;
        fclose(file);
    };
};

#endif //PAGEDARRAYSORTER_DATOS_2_PAGEDARRAY_H