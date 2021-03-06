#ifndef GALERIA_IMAGENES_H
#define GALERIA_IMAGENES_H

#include "imagen.h"

#include <vector>

class GaleriaImagenes {
 public:
  void dividirYAgregar(const Imagen &imagen, int n, int m);
  Imagen laMasChiquitaConPuntoBlanco() const;
  void agregarImagen(const Imagen &imagen);
  void votar(const Imagen &imagen);
  void eliminarMasVotada();
  vector <Imagen> top10() const;

  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);
 private:
  std::vector<Imagen> imagenes;
  std::vector<int> votos;
  /*
    invRep(x) :
    paratodo i < votos.size(), votos[i] >=0 Y
    paratodo i,j <imagenes.size(), i=!j ,imagenes[i] != imagenes[j].
    abs(x,galeriaImagenes) :
    imagenes (g: Galeria) == imagenes;
    votos (g: Galeria, i: Imagen) == votos[std::find(imagenes.begin(), imagenes.end(), imagen)];
  */
  Imagen getPrimeraBlanca() const;
  bool tienePixelBlanco(Imagen imagen) const;
  void Ordenar();
};

#endif  // GALERIA_IMAGENES_H

