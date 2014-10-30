#include "pixel.h"

Pixel::Pixel()
{
    int i =0;
    while(i<=2)
    {
        intensidades[i]=0;
        i++;
    }
}

int Pixel::red() const
{
    return intensidades[0];
}

int Pixel::green() const
{
    return intensidades[1];
}

int Pixel::blue() const
{
    return intensidades[2];
}

Pixel::Pixel(int red,int green,int blue)
{
    intensidades[0]=red;
    intensidades[1]=green;
    intensidades[2]=blue;
}

void Pixel::cambiarPixel(int red,int green,int blue)
{
    intensidades[0]=red;
    intensidades[1]=green;
    intensidades[2]=blue;
}

bool Pixel::operator==(const Pixel &otro) const
{
    int i =0;
    bool res = true;
    while(i<=2)
    {
        if(intensidades[i]!=otro.intensidades[i])
            res=false;
        i++;
    }
    return res;
}

void Pixel::guardar(std::ostream& os) const{
	os << "(" << red() << ";" << green() << ";" << blue() << ")";
}

void Pixel::cargar(std::istream& ss) {
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
	intensidades[0]= r;
	intensidades[1]= g;
	intensidades[2]= b;
}
