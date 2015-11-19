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
	d.Definir(70,Posicion(5,2));
	Campus camp(8,8);
	//cout<<camp.Ocupada(Posicion(2,1))<<endl;
	camp.AgregarObstaculo(Posicion(3,0));
	camp.AgregarObstaculo(Posicion(2,1));
	camp.AgregarObstaculo(Posicion(5,0));


	//cout<<camp.Ocupada(Posicion(2,1))<<endl;
	Rastrillaje rast(camp,d);
	//cout<<rast.ObsCampus().Ocupada(Posicion(2,1))<<endl;
	//cout<<rast.quienOcupa[1][2].queHay<<endl;
	//cout<<rast.dimeQueHay(Posicion(1,2))<<endl;
	cout<<rast;
	cout<<" "<<endl;
	rast.IngresarHippie(Posicion(4,0),"pachi");
	cout<<rast;
	cout<<" "<<endl;
	cout<<rast.PosEstudianteYHippie("pachi").x<<" "<<rast.PosEstudianteYHippie("pachi").y<<endl;
	cout<<rast.PosAgente(70).x<<" "<<rast.PosAgente(70).y<<endl;
	//rast.MoverAgente(70);
	//rast.agentes.Obtener(70);

	

	return 0;
}