#include <stdio.h>
#include <iostream>
#include <fstream>
#include "imagen.h"

using namespace std;

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
	cout << "Modificando pixel 0,1 \n";
	img.modificarPixel(0,1, Pixel(255, 255, 255));
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
	cout << endl;
}

int main() {
	int opcion_menu = -1;
	int opcion_salir = 12;

	while(opcion_menu != opcion_salir){
		opcion_menu = MostrarMenuPrincipal();
		cout << "\n Su opcion fue la " << opcion_menu << "\n";

		if(opcion_menu == 42)
			opcion_debug();
	}
	cout << "\nsaliendo\n";

	return 0;
}
