#ifndef IMAGEN_H
#define IMAGEN_H

#include "pixel.h"

#include <vector>

typedef std::vector<Pixel> Pixel1DContainer;
typedef std::vector<Pixel1DContainer> Pixel2DContainer;



class Imagen {
 public:
  Imagen(int alto_param, int ancho_param);
  Pixel obtenerPixel(int fila, int columna) const;
  void modificarPixel(int fila, int columna, const Pixel &pixel);
  int alto() const;
  int ancho() const;
  vector<pair<int, int> > posicionesMasOscuras() const;
  void blur(int k);
  void acuarela(int k);

  bool operator==(const Imagen &otra) const;

  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);

 private:
  Pixel2DContainer pixels;
  void resize(int alto, int ancho);
  int maximaOscuridad() const;
  int luminosidad(Pixel p) const;
  Pixel blurearPixel(int y,int x,int k,Imagen aux);
  Pixel pixelPromedio(int y,int x, int k,Imagen aux);
};

#endif  // IMAGEN_H
