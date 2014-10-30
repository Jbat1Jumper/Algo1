#include "imagen.h"
#include <sstream>
#include <algorithm>

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

void DrawProgressBar(int len, double percent) {
  cout << "\x1B[2K"; // Erase the entire current line.
  cout << "\x1B[0E"; // Move to the beginning of the current line.
  string progress;
  for (int i = 0; i < len; ++i) {
    if (i < static_cast<int>(len * percent)) {
      progress += "=";
    } else {
      progress += " ";
    }
  }
  cout << "[" << progress << "] " << (static_cast<int>(100 * percent)) << "%";
  flush(cout); // Required.
}

void Imagen::acuarela(int k)
{
    Imagen aux = *this;
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
		{
			modificarPixel(y,x,modificarPixel(y,x,k,aux,"acuarela"));
		}

		DrawProgressBar(30,y/(double)alto());
	}
	cout << "\x1B[2K"; // Erase the entire current line.
}

void Imagen::blur(int k)
{

	Imagen aux = *this;
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
		{
			modificarPixel(y,x,modificarPixel(y,x,k,aux,"blur"));
		}

		DrawProgressBar(30,y/(double)alto());
	}
	cout << "\x1B[2K"; // Erase the entire current line.
}



Pixel Imagen::modificarPixel(int y,int x,int k,Imagen aux,string modo)
{
	int i= y+k-pixels.size();
	int j = x+k-pixels.at(0).size();
    if(i>0 || y-k<-1 || j>0 || x-k<-1)
        return Pixel(0,0,0);
    else if (modo == "blur")
        return pixelPromedio(y,x,k,aux);
    else if (modo == "acuarela")
        return pixelMediana(y,x,k,aux);
}

Pixel Imagen::pixelMediana(int y,int x,int k, Imagen aux)
{
    vector<int> red;
    vector<int> green;
    vector<int> blue;
    for(int i=y-k+1;i<=y+k-1;i++)
        for(int j=x-k+1;j<=x+k-1;j++)
        {
            blue.push_back(aux.obtenerPixel(i,j).blue());
            green.push_back(aux.obtenerPixel(i,j).green());
            red.push_back(aux.obtenerPixel(i,j).red());
        }
    std::sort (red.begin(),red.end());
    std::sort (blue.begin(),blue.end());
    std::sort (green.begin(),green.end());
    Pixel res = Pixel(red.at(red.size()/2),green.at(green.size()/2),blue.at(blue.size()/2));
    return res;
}

Pixel Imagen::pixelPromedio(int y,int x,int k, Imagen aux)
{
    int cantpixels=0;
    int sumagreen=0;
    int sumared=0;
    int sumablue=0;
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
    int maxOscuridad = maximaOscuridad();
    for(int y = 0; y < alto(); y++) {
		for(int x = 0; x < ancho(); x++)
			{
                if(luminosidad(pixels.at(y).at(x))==maxOscuridad)
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

/*
problema blur (this : Imagen; k : Z) f
requiere k > 0 ;
modifica this ;
asegura mismasDimensiones : alto(this) == alto(pre(this)) ^ ancho(this) == ancho(pre(this)) ;
asegura blurKVecinosIncompletos : (8x   [0::ancho(this)); y   [0::alto(this)))
:KV ecinosCompletos(this; x; y; k) ) esNegro(color(this; x; y)) ;
asegura blurKVecinosCompletos : (8x   [0::ancho(this)); y   [0::alto(this)))
KV ecinosCompletos(this; x; y; k) ) esP romedio(color(this; x; y);Kvecinos(pre(this); x; y; k)) ;
aux esPromedio (p: Pixel, kv: [Pixel]) : Bool = red(p) == promedio([red(x)jx   kv]) ^
green(p) == promedio([green(x)jx   kv]) ^ blue(p) == promedio([blue(x)jx   kv]) ;

*/

void Imagen::blur(int k){

}

/*
problema acuarela (this : Imagen; k : Z) f
requiere k > 0 ;
modifica this ;
asegura mismasDimensiones : alto(this) == alto(pre(this)) ^ ancho(this) == ancho(pre(this)) ;
asegura acuarelaKVecinosIncompletos : (8x   [0::ancho(this)); y   [0::alto(this)))
:KV ecinosCompletos(this; x; y; k) ) esNegro(color(this; x; y)) ;
asegura acuarelaKVecinosCompletos : (8x   [0::ancho(this)); y   [0::alto(this)))
KV ecinosCompletos(this; x; y; k) ) esMediana(color(this; x; y);Kvecinos(pre(this); x; y; k)) ;
aux esMediana (p: Pixel, kv: [Pixel]) : Bool = red(p) == mediana([red(x)jx   kv]) ^
green(p) == mediana([green(x)jx   kv]) ^ blue(p) == mediana([blue(x)jx   kv]) ;
  */

void Imagen::acuarela(int k){

}
