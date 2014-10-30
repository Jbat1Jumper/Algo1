private:
  std::vector<Imagen> imagenes;
  std::vector<int> votos;

public:

void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m){

    }
Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco() const{
    int tam = imagenes.size();
    int i = 0;
    Imagen menor = getPrimeraBlanca();
    Imagen actual = Imagen(10,10);
    while (i<tam){
        if(tienePixelBlanco(imagenes[i]){
            actual = imagenes[i];
            if(actual.alto()<=menor.alto() && actual.ancho()<=actual.ancho()){
                menor = actual;
            }
        }
    }
    return menor;
}
Imagen getPrimeraBlanca(){
    int i = 0;
    Imagen result;
    while (i<imagenes.size()){
        if tienePixelBlanco(imagenes[i]){
        result = imagenes[i];
        break;
        }
    }
    return result;
}

bool tienePixelBlanco(Imagen &imagen){
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
        }
    }
    return result;

}
void GaleriaImagenes::agregarImagen(const Imagen &imagen){


    }
void GaleriaImagenes::votar(const Imagen &imagen){

    }


void GaleriaImagenes::eliminarMasVotada(){
    imagenes.pop_back();
    votos.pop_back();
}

vector <Imagen> top10() const{
    int max = 10;
    int i = 0;
    vector<Imagen> result; //vector va a ser un vector con las primeras 10 cantidad de votos.

    while(i<max){
       result.push_back(imagenes[i]);
    }
    return result;
}

void guardar(std::ostream& os) const{

}
void cargar (std::istream& is){

}

