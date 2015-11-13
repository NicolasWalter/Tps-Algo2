#include <iostream>
using namespace std;
#include "aed2.h"

int main(int argc, char const *argv[])
{
	DiccionarioProm<Nat, Nat> d(5);
	d.Definir(8,12);
//	d.Definir(5,9);
	bool b = d.Definido(7);
	Conj<Nat>::const_Iterador it = d.Claves();
/*	cout<< it.Siguiente() << endl;
	it.Avanzar();
	cout<< it.Siguiente() << endl;
	cout << d.Obtener(10) << endl;*/
	Lista<typename DiccionarioProm<Nat, Nat>::TElem>::Iterador iter = d.DefinirRapido(12,3);
	d.Definir(5,9);

	cout<< iter.Siguiente().clave << endl;



	return 0;
}