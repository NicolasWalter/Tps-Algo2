#include <iostream>
using namespace std;
#include "aed2.h"

int main(int argc, char const *argv[])
{
	DiccionarioProm<Nat, Nat> d(5);
	d.Definir(8,12);
	cout<<d.Obtener(8)<<endl;
	d.Obtener(8)=299;
	cout<<d.Obtener(8)<<endl;




	return 0;
}