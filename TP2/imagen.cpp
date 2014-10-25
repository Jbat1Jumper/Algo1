#include "imagen.h"

Imagen::Imagen(int alto_param,int ancho_param)
{
    int i=0;
    int j=0;
    Pixel pixelNegro = Pixel(0,0,0);
    Pixel1DContainer fila = Pixel1DContainer();
    Pixel2DContainer img = Pixel2DContainer();
    while(j<ancho_param)
            {
                fila.push_back(pixelNegro);
                j++;
            }

    while (i<alto_param)
        {
            img.push_back(fila);
            i++;
        }
    pixels = img;
}

Pixel Imagen::obtenerPixel(int fila, int columna) const
{
    return (pixels.at(fila)).at(columna);
}

void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel)
{
    (pixels.at(fila)).at(columna) = pixel;
}

int Imagen::alto() const
{
    return pixels.size();
}

int Imagen::ancho() const
{
    return pixels.at(0).size();
}
