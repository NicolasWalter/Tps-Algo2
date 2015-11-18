#include "Rastrillaje.h"
#include <iostream>
#include "aed2.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Dicc<Agente,Posicion> d;
	d.Definir(1,Posicion(1,2));
	d.Definir(3,Posicion(2,2));
	d.Definir(4,Posicion(1,1));
	d.Definir(70,Posicion(6,2));
	Campus camp(8,8);
	//cout<<camp.Ocupada(Posicion(2,1))<<endl;
	camp.AgregarObstaculo(Posicion(2,1));
	//cout<<camp.Ocupada(Posicion(2,1))<<endl;
	Rastrillaje rast(camp,d);
	//cout<<rast.ObsCampus().Ocupada(Posicion(2,1))<<endl;
	//cout<<rast.quienOcupa[1][2].queHay<<endl;
	//cout<<rast.dimeQueHay(Posicion(1,2))<<endl;
	cout<<rast;

	

	return 0;
}