/*
**La galeria esta ordenada de menor voto a mayor voto tanto vector votos como imagenes.
**Se realizo de esta manera para que facilite la reorganizacion cuando se agregan y/o
**eliminan imagenes.
**
*/
#include "galeria_imagenes.h"
#include <sstream>
#include <algorithm>

void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m){

}
Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco() const{
    int tam = imagenes.size();
    int i = 0;
    Imagen menor = getPrimeraBlanca();
    Imagen actual = Imagen(10,10);
    while (i<tam){
        if(tienePixelBlanco(imagenes[i])){
            actual = imagenes[i];
            if(actual.alto()<=menor.alto() && actual.ancho()<=actual.ancho()){
                menor = actual;
            }
        }
        i++;
    }
    return menor;
}
Imagen GaleriaImagenes::getPrimeraBlanca() const{
    int i = 0;
	Imagen result(1,1);
    while (i<imagenes.size()){
        if (tienePixelBlanco(imagenes[i])){
        result = imagenes[i];
        break;
        }
        i++;
    }
    return result;
}

bool GaleriaImagenes::tienePixelBlanco(Imagen imagen) const{
    int i = 0;
    int j = 0;
    bool result = false;
    Pixel whitepxl = Pixel(255,255,255);
    Pixel pxl;
    while (i<imagen.alto()){
        while(j<imagen.ancho()){
            pxl = imagen.obtenerPixel(i,j);
            if (pxl == whitepxl){
                result = true;
                break;
            }
            j++;
        }
        i++;
    }
    return result;

}

void GaleriaImagenes::agregarImagen(const Imagen& imagen){
	if(std::find(imagenes.begin(), imagenes.end(), imagen)!=imagenes.end())
	{
		cout << "Ya existe una imagen identica" << endl;
		return;
	}
	imagenes.push_back(imagen);
	votos.push_back(0);
	Ordenar();
	cout << "Imagen agregada" << endl;
	
}

void GaleriaImagenes::votar(const Imagen& imagen){
    int i = 0;
    while(i < imagenes.size()){
        if (imagenes[i]== imagen){
            votos[i]++;
			cout << "Imagen Votada";
            Ordenar();
			return;
        }
        i++;
    }
	cout << "No esta cargada la imagen en la galeria" << endl;
}


void GaleriaImagenes::eliminarMasVotada(){
    imagenes.pop_back();
    votos.pop_back();
}

vector <Imagen> GaleriaImagenes::top10() const{
	if(votos.size()<10)
	{
		return imagenes; 
	}
	int max = 10;
    int i = 1;
    vector<Imagen> result; 
    while(i<=max){
       result.push_back(imagenes[imagenes.size()-i]);
       i++;
    }
    return result;
}

void GaleriaImagenes::guardar(std::ostream& os) const{
	os << "[";
	for(int i = 0; i < votos.size(); i++)
			{
				os << "(";
				Imagen miImagen = imagenes[i];
				int voto = votos[i];
				miImagen.guardar(os);
				os << ",";
				os << voto;
				os << ")";
				if(i < votos.size()-1)
					os << ",";
	}	os << "]";
}
void GaleriaImagenes::cargar (std::istream& is){

	int voto;
	char corchete;
	char parentesis;
	char coma;
	int i =0;
	is >> corchete;
	while (i<1)
	{
		is >> parentesis;
		Imagen miImagen(1,1);
		miImagen.cargar(is);
		imagenes.push_back(miImagen);
		is >> coma;
		is >> voto;
		votos.push_back(voto);
		is >> parentesis;
		is >> coma;
		if(coma != ',')
			i=1;
	}
	Ordenar();
}

void GaleriaImagenes::Ordenar()
{
	int i= 0;
	int n= votos.size();
	while(i < n){
		int j= 0;
		while(j < n-1){
			if(votos[j] > votos[j+1])
			{
				swap(votos[j],votos[j+1]);
				swap(imagenes[j],imagenes[j+1]);
			}
			j++;
		}
		i++;
}
}


