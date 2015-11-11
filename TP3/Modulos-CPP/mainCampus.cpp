#include "Campus.h"
#include <iostream>
using namespace std;

int main(){
	Campus camp(9,9);
	Posicion p1(2,5);
	Posicion p2(3,3);
	Posicion ing1(2,3);
	Posicion ing2(2,1);
	//Conj<Posicion> v1 = camp.Vecinos(p1);
	// Conj<Posicion> v2 = camp.Vecinos(p2);
	// Conj<Posicion> comunes = camp.VecinosComunes(p1,p2);
	// Conj<Posicion>::Iterador it = comunes.CrearIt();
	// cout << "(" << (it.Siguiente()).x << "," << (it.Siguiente()).y << ")" << endl;
	//Posicion sig = camp.ProxPosicion(arriba,p1);
	//cout << "(" << sig.x << "," << sig.y << ")" << endl;
	cout << camp.distancia(p1,ing1) << endl;
	Conj<Posicion> ingresosCercanos = camp.IngresosMasCercanos(p1);
	Conj<Posicion>::Iterador it = ingresosCercanos.CrearIt();
	cout << "(" << (it.Siguiente()).x << "," << (it.Siguiente()).y << ")" << endl;
	it.Avanzar();
	cout << "(" << (it.Siguiente()).x << "," << (it.Siguiente()).y << ")" << endl;

	return 0;
}