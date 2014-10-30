private:
  std::vector<Imagen> imagenes;
  std::vector<int> votos;

public:

void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m){

    }
Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco() const{

    }
void GaleriaImagenes::agregarImagen(const Imagen &imagen){

//agregar imagen y ordenar
    }
void GaleriaImagenes::votar(const Imagen &imagen){
    //agregar voto y ordenar

    }


void GaleriaImagenes::eliminarMasVotada(){

    int i = 0;
    int posMasVotada = 0;
    int masVotada = 0;

    while (i<votos.size()){
      if (masVotada<votos.at(i)){
        masVotada = votos.at(i);
        posMasVotada = i;
      }
    }

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

