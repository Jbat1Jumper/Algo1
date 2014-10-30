/*
**La galeria esta ordenada de menor voto a mayor voto tanto vector votos como imagenes.
**Se realizo de esta manera para que facilite la reorganizacion cuando se agregan y/o
**eliminan imagenes.
**
*/
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
        i++;
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
        i++;
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
    votos.push_back(votos[.size()-1]);
    while (i<(imagenes.size()-1){
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

vector <Imagen> top10() const{
    int max = 10;
    int i = 0;
    vector<Imagen> result; //vector va a ser un vector con las primeras 10 cantidad de votos.

    while(i<max){
       result.push_back(imagenes[imagenes.size()-i]);
       i++;
    }
    return result;
}

void guardar(std::ostream& os) const{

}
void cargar (std::istream& is){

}

