#include <stdio.h>
#include <iostream>
#include <fstream>
#include "imagen.h"
#include "galeria_imagenes.h"

using namespace std;

GaleriaImagenes miGaleria;

int MostrarMenuPrincipal() {
	int opcion;
	cout << "\nGalerazo\nSeleccione alguna opcion para continuar\n";
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
	cout << ">>> ";
	cin >> opcion;
	return opcion;
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
	cout << "Galeria guardada" << endl; 
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

void dividiryagregar()
{
	cout << "Ingrese nombre de archivo de galeria \n";
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
	cout << "Ingrese nombre de archivo de imagen a cortar \n";
    string nombre2;
    cin >> nombre2;
	std::ifstream ifs2(nombre2.c_str());
	if(!ifs2.is_open()){
		cout << "no se pudo abrir" << endl;
		return;
	}
	Imagen miImagen(1,1);
	miImagen.cargar(ifs2);
	ifs2.close();
	cout << "Imagen Cargada" << endl;
	cout << "Ingrese divisor de columnas" <<endl;
	int n;
	cin >> n;
	if(miImagen.ancho() % n !=0)
	{
		cout << "La imagen no es divisible por las columnas ingresadas" <<endl;
		return;
	}
	cout << "Ingrese divisor de filas" <<endl;
	int m;
	cin >> m;
	if(miImagen.alto() % m !=0)
	{
		cout << "La imagen no es divisible por las filas ingresadas" <<endl;
		return;
	}
	miGaleria.dividirYAgregar(miImagen,n,m);
}

int main() {
	int opcion_menu = -1;
	int opcion_salir = 12;

	while(opcion_menu != opcion_salir){
		opcion_menu = MostrarMenuPrincipal();
		cout << endl;
		switch(opcion_menu)
		{
			case 1:
                blur();
            break;
			case 2:
                acuarela();
            break;
			case 3:
				cargargaleria();
			break;
			case 4:
				dividiryagregar();
			break;
			case 5:
                posicionesMasOscuras();
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
