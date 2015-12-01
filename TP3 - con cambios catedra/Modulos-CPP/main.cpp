#include <iostream>
using namespace std;
#include "aed2.h"

int main(int argc, char const *argv[])
{
	DiccionarioProm<Nat, Nat> d(5);

	d.Definir(10,3);
	d.Definir(5,4);
	d.Definir(4,23);
	d.Definir(2,12);
	bool b = d.Definido(7);
	Conj<Nat>::Iterador it = d.Claves();
	cout<< it.Siguiente() << endl;

	return 0;
}