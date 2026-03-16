#include "PagedArray.h"

int PagedArray::LRU()
{
    int MinUltimo = ultimo[0];
    int indice = 0;

    for (int i = 0; i < NumPage; i++) {
        if (ultimo[i] < MinUltimo) {
            MinUltimo = ultimo[i];
            indice = i;
        }
    }
    return indice;
}

void PagedArray::Cargador(int pageNum, int indice)
{
    if (DirtyBite[indice] == true) {
        fseek(file, FramePages[indice] * PageSize * sizeof(int), SEEK_SET);
        fwrite(frames[indice], sizeof(int), PageSize, file);
    }
    int Pageoffset = pageNum * PageSize * sizeof(int);
    fseek(file, Pageoffset, SEEK_SET);
    fread(frames[indice], sizeof(int), PageSize, file);

    FramePages[indice] = pageNum;
    DirtyBite[indice] = false;
}