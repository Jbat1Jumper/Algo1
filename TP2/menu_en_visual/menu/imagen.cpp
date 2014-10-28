#include "imagen.h"
#include <sstream>
int cantpixels=0;
int sumagreen=0;
int sumared=0;
int sumablue=0;

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

void Imagen::blur(int k)
{
	Imagen aux = *this;
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
		{
			modificarPixel(y,x,blurearPixel(y,x,k,aux));
		}
	}
}

Pixel Imagen::blurearPixel(int y,int x,int k,Imagen aux)
{
	int i= y+k-pixels.size();
	int j = x+k-pixels.at(0).size();
    if(i>0 || y-k<-1 || j>0 || x-k<-1)
    {
        return Pixel(0,0,0);
    }
    else
    {
		return pixelPromedio(y,x,k,aux);
    }
}
Pixel Imagen::pixelPromedio(int y,int x,int k, Imagen aux)
{
    cantpixels=0;
    sumagreen=0;
    sumared=0;
    sumablue=0;
    for(int i=y-k+1;i<=y+k-1;i++)
        for(int j=x-k+1;j<=x+k-1;j++)
        {
            sumablue+= aux.obtenerPixel(i,j).blue();
            sumagreen+=aux.obtenerPixel(i,j).green();
            sumared+=aux.obtenerPixel(i,j).red();
            cantpixels++;
        }
    Pixel res = Pixel(sumared/cantpixels,sumagreen/cantpixels,sumablue/cantpixels);
    return res;
}


vector<pair<int, int> > Imagen::posicionesMasOscuras() const
{
    vector<pair<int, int> > posiciones;
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
			{
                if(luminosidad(pixels.at(y).at(x))==maximaOscuridad())
                    posiciones.push_back(pair<int,int>(y,x));
			}
	}
	return posiciones;
}

int Imagen::maximaOscuridad() const
{
    int oscuridad = 1000;
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
		{
            if(oscuridad>luminosidad(pixels.at(y).at(x)))
			oscuridad=luminosidad(pixels.at(y).at(x));
        }
	}
	return oscuridad;
}

int Imagen::luminosidad(Pixel miPixel) const
{
    return miPixel.blue() + miPixel.green() + miPixel.red();
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
			guardar_pixel(os, obtenerPixel(y, x));
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

bool Imagen::operator==(const Imagen &otra) const
{
    int j =0;
    int k =0;
    bool res = true;
    while(j<otra.pixels.size())
    {
    k=0;
    while(k<otra.pixels.at(0).size())
    {
        if(!(otra.obtenerPixel(j,k)==obtenerPixel(j,k)))
            {
                res=false;
                return res;
            }
    k++;
    }
    j++;
    }
    return res;
}


void Imagen::cargar (std::istream& is) {
	std::string line;
	std::getline(is, line);
	std::stringstream ss(line);

	int ancho, alto;
	char acasedeberiaverificar;
	ss >> alto;
	ss >> ancho;
	resize(alto, ancho);

	for(int y = 0; y < this->alto(); y++)
		for(int x = 0; x < this->ancho(); x++){
			ss >> acasedeberiaverificar;
			modificarPixel(y,x, cargar_pixel(ss));
		}
	is >> acasedeberiaverificar;
}
