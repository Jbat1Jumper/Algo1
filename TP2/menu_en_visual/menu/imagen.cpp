#include "imagen.h"
#include <sstream>

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

void Imagen::resize(int alto, int ancho){
	pixels.clear();
    Pixel pixelNegro = Pixel(0,0,0);
	for(int y = 0; y < alto; y++) {
		Pixel1DContainer fila = Pixel1DContainer();
		for(int x = 0; x < ancho; x++)
			fila.push_back(pixelNegro);
		pixels.push_back(fila);
	}
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

void guardar_pixel(std::ostream& os, const Pixel& p) {
	os << "(" << p.red() << ";" << p.green() << ";" << p.blue() << ")";
}

void Imagen::guardar(std::ostream& os) const {
	os << alto() << " ";
	os << ancho() << " ";
	os << "[";
	for(int y = 0; y < alto(); y++)
		for(int x = 0; x < ancho(); x++){
			if(x + y != 0)
				os << ",";
			guardar_pixel(os, obtenerPixel(x, y));
		}
	os << "]";
}

Pixel cargar_pixel(std::stringstream& ss) {
	int r, g, b;
	char acatambiensedeberiaverificar;
	{
		ss >> acatambiensedeberiaverificar;
		ss >> r;
		ss >> acatambiensedeberiaverificar;
		ss >> g;
		ss >> acatambiensedeberiaverificar;
		ss >> b;
		ss >> acatambiensedeberiaverificar;
	}
	Pixel t(r, g, b);
	return t;
}

void Imagen::cargar (std::istream& is) {
	std::string line;
	std::getline(is, line);
	std::stringstream ss(line);

	int ancho, alto;
	char acasedeberiaverificar;
	ss >> ancho;
	ss >> alto;
	resize(alto, ancho);
	
	for(int y = 0; y < this->alto(); y++)
		for(int x = 0; x < this->ancho(); x++){
			ss >> acasedeberiaverificar;
			modificarPixel(x, y, cargar_pixel(ss));
		}
	is >> acasedeberiaverificar;
}