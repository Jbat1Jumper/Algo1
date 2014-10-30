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
    int i = 1;
    Imagen aux1 = imagenes[0];
    int votos1 = votos[0];
    Imagen aux2 = imagenes[0];
    int votos2 = votos[0];
    imagenes.push_back(imagenes[imagenes.size()-1]);
	votos.push_back(votos[imagenes.size()-1]);
    while (i<(imagenes.size()-1)){
           aux2 = imagenes[i];
           votos2 = votos[i];
           imagenes[i]= aux1;
           votos[i]=votos1;
           aux1 = aux2;
           votos1=votos2;
    }
    imagenes[0] = imagen;
    votos[0]=0;
}

void GaleriaImagenes::votar(const Imagen& imagen){
    int i = 0;
    while(i < imagenes.size()){
        if (imagenes[i]== imagen){
            votos[i]++;
            //reordenar(); ----->> falta!
        }
        i++;
    }
}


void GaleriaImagenes::eliminarMasVotada(){
    imagenes.pop_back();
    votos.pop_back();
}

vector <Imagen> GaleriaImagenes::top10() const{
    int max = 10;
    int i = 0;
    vector<Imagen> result; //vector va a ser un vector con las primeras 10 cantidad de votos.

    while(i<max){
       result.push_back(imagenes[imagenes.size()-i]);
       i++;
    }
    return result;
}

void GaleriaImagenes::guardar(std::ostream& os) const{

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
		if(coma == ']')
			i=1;
	}
	
}

