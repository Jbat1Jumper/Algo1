#include <stdio.h>
#include <iostream>
#include <fstream>
#include "imagen.h"
#include "galeria_imagenes.h"

using namespace std;

GaleriaImagenes miGaleria;

int MostrarMenuPrincipal() {
	int opcion;
	cout << "\nSeleccione alguna opcion para continuar\n";
	cout << "1 - blur\n";
	cout << "2 - acuarela\n";
	cout << "3 - cargar galeria\n";
	cout << "4 - dividir y agregar\n";
	cout << "5 - posisiones mas oscuras\n";
	cout << "6 - top 10\n";
	cout << "7 - la mas chiquita con punto blanco\n";
	cout << "8 - agregar imagen\n";
	cout << "9 - votar\n";
	cout << "10 - eliminar mas votada\n";
	cout << "11 - guardar galeria\n";
	cout << "12 - salir\n";
	cout << "\n42 - debug\n";
	cout << ">>> ";
	cin >> opcion;
	return opcion;
}

void opcion_debug() {
	Imagen img(1, 1);
	cout << "Abriendo img.txt para hacer unas pruebas \n";
	std::ifstream ifs("img.txt");
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	img.cargar(ifs);
	cout << "Mostrando imagen: \n";
	img.guardar(cout);
	cout << endl;
	Imagen img2(1, 1);
	cout << "Abriendo img.txt para hacer unas pruebas \n";
	std::ifstream ifs3("img2.txt");
	img2.cargar(ifs3);
	bool res = img2==img;
	cout << endl << "Comparar Imagenes: \n" << endl << res;
	cout << endl <<"Posiciones mas oscuras" << endl;
    vector<pair<int, int> > posiciones2 = img.posicionesMasOscuras();
	for(int i=0; i<posiciones2.size();i++)
	{
        cout << "(" << posiciones2.at(i).first << "," << posiciones2.at(i).second << ")";
	}
	cout << "Modificando pixel 2,0 \n";
	img.modificarPixel(2,0, Pixel(255, 255, 255));
	cout << "Guardando copia modificada en img2.txt \n";
	std::ofstream ofs("img2.txt");
	img.guardar(ofs);
	ifs.close();
	ofs.close();
	cout << "Listo \n";
	std::ifstream ifs2("img2.txt");
	if(!ifs2.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	img.cargar(ifs2);
	cout << "Mostrando imagen 2: \n";
	img.guardar(cout);
	cout << endl <<"Posiciones mas oscuras" << endl;
	vector<pair<int, int> > posiciones = img.posicionesMasOscuras();
	for(int i=0; i<posiciones.size();i++)
	{
        cout << "(" << posiciones.at(i).first << "," << posiciones.at(i).second << ")";
	}
	std::ifstream ifs4("galeria.txt");
	cout << endl << "Cargando galeria" << endl;
	GaleriaImagenes galeria;
	galeria.cargar(ifs4);

}

void posicionesMasOscuras()
{
    cout << "Ingrese nombre de archivo \n";
    string nombre;
    cin >> nombre;
    Imagen img(1,1);
    std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	img.cargar(ifs);
	ifs.close();
	cout << endl <<"Posiciones mas oscuras" << endl;
    vector<pair<int, int> > posiciones = img.posicionesMasOscuras();
	for(int i=0; i<posiciones.size();i++)
	{
        cout << "(" << posiciones.at(i).first << "," << posiciones.at(i).second << ")";
	}
	cout << endl;
}

void acuarela()
{
 cout << "Ingrese nombre de archivo \n";
    string nombre;
    cin >> nombre;
    Imagen img(1,1);
    std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	img.cargar(ifs);
	cout << endl <<"Ingrese nombre de destino" << endl;
    string archivonuevo;
    cin >> archivonuevo;
    cout << endl <<"Ingrese parametro de acuarela" << endl;
    int k;
    cin >> k;
    ifs.close();
    img.acuarela(k);
    std::ofstream ofs(archivonuevo.c_str());
	img.guardar(ofs);
    ofs.close();
	cout << endl << "Imagen Guardada" <<endl;
}

void blur()
{
 cout << "Ingrese nombre de archivo \n";
    string nombre;
    cin >> nombre;
    Imagen img(1,1);
    std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	img.cargar(ifs);
	cout << endl <<"Ingrese nombre de destino" << endl;
    string archivonuevo;
    cin >> archivonuevo;
    cout << endl <<"Ingrese parametro de blureo" << endl;
    int k;
    cin >> k;
    ifs.close();
    img.blur(k);
    std::ofstream ofs(archivonuevo.c_str());
	img.guardar(ofs);
    ofs.close();
	cout << endl << "Imagen Guardada" <<endl;
}

void cargargaleria()
{
	cout << "Ingrese nombre de archivo \n";
    string nombre;
    cin >> nombre;
	std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	miGaleria.cargar(ifs);
	ifs.close();
	cout << "Galeria cargada" << endl;
}

void eliminarMasVotada()
{
	miGaleria.eliminarMasVotada();
	cout << "Imagen eliminada" << endl;
}

void guardarGaleria()
{
	cout <<"Ingrese nombre de destino" << endl;
    string archivonuevo;
    cin >> archivonuevo;
	std::ofstream ofs(archivonuevo.c_str());
	miGaleria.guardar(ofs);
	ofs.close();
	cout << "Galería guardada" << endl; 
}

void top10()
{
	vector<Imagen> miTop10 = miGaleria.top10();
	cout <<"Ingrese nombre de destino" << endl;
    string archivonuevo;
    cin >> archivonuevo;
	std::ofstream ofs(archivonuevo.c_str());
	ofs << "[" ;
	for(int i=0;i<miTop10.size();i++)
	{
	ofs <<miTop10[i].alto() << " ";
	ofs << miTop10[i].ancho() << " ";
	ofs << "[";
	for(int y = 0; y < miTop10[i].alto(); y++){
		for(int x = 0; x < miTop10[i].ancho(); x++){
			if(x + y != 0)
				ofs << ",";
			Pixel miPixel = miTop10[i].obtenerPixel(y,x);
			miPixel.guardar(ofs);
		}
		if(miTop10[i].alto()-1==y)
			ofs <<"]";
	}
		if(i==miTop10.size()-1)
		ofs << "]";
		else
			ofs <<",";
	}
	cout << "Imagenes guardadas" << endl ;
}

void laMasChiquitaConPuntoBlanco()
{
	Imagen chConPuntoBlanco = miGaleria.laMasChiquitaConPuntoBlanco();
	if(chConPuntoBlanco == Imagen(1,1)){
		cout << "No existe imagen con punto blanco" << endl;
		return;
	}
	cout <<"Ingrese nombre de destino" << endl;
    string archivonuevo;
    cin >> archivonuevo;
	std::ofstream ofs(archivonuevo.c_str());
	chConPuntoBlanco.guardar(ofs);
	ofs.close();
	cout << "Imagen Guardada" <<endl;
}

void agregarImagen()
{
	cout << "Ingrese nombre de archivo de imagen \n";
    string nombre;
    cin >> nombre;
	std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	Imagen miImagen(1,1);
	miImagen.cargar(ifs);
	miGaleria.agregarImagen(miImagen);
}

void votar()
{
	cout << "Ingrese nombre de archivo de imagen a votar \n";
    string nombre;
    cin >> nombre;
	std::ifstream ifs(nombre.c_str());
	if(!ifs.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	Imagen miImagen(1,1);
	miImagen.cargar(ifs);
	miGaleria.votar(miImagen);
}

int main() {
	int opcion_menu = -1;
	int opcion_salir = 12;

	while(opcion_menu != opcion_salir){
		opcion_menu = MostrarMenuPrincipal();
		cout << endl;
		switch(opcion_menu)
		{
			case 42:
                opcion_debug();
			break;
			case 5:
                posicionesMasOscuras();
			break;
			case 1:
                blur();
            break;
            case 2:
                acuarela();
            break;
			case 3:
				cargargaleria();
			break;
			case 6:
				top10();
			break;
			case 7:
				laMasChiquitaConPuntoBlanco();
			break;
			case 8:
				agregarImagen();
				break;
			case 9:
				votar();
				break;
			case 10:
				eliminarMasVotada();
			break;
			case 11:
				guardarGaleria();
			break;
        }
	}
	cout << "\nsaliendo\n";

	return 0;
}
