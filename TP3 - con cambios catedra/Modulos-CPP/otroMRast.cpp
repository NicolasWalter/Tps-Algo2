#include "Rastrillaje.h"
#include <iostream>
#include "aed2.h"
#include "mini_test.h"


using namespace std;

int main(int argc, char const *argv[])
{
	
	Campus camp(10,10);
	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;
	camp.AgregarObstaculo(p2);
	camp.AgregarObstaculo(p3);

	Dicc<Agente,Posicion> agentes;
	
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;


	agentes.Definir(a2,Posicion(5,5));
	agentes.Definir(a,p);
	//agentes.Definir(a2,p2);
	//agentes.Definir(a3,p3);

	Rastrillaje rast(camp,agentes);
	

	Posicion pe;
	pe.x = 2;
	pe.y = 1;

	Nombre e = "pepe";
	cout<<rast;
	cout<<" "<<endl;
	cout<<rast.CantSanciones(a)<<endl;
	cout<<"conMismas: "<<rast.ConMismasSanciones(a).Cardinal()<<endl;
 	rast.IngresarEstudiante(e,pe);
 	cout<<"conMismas: "<<rast.ConMismasSanciones(a).Cardinal()<<endl;
 	 cout<<"conMismas: "<<rast.ConMismasSanciones(a2).Cardinal()<<endl;
	//rast.Sancionar(p);
	cout<<rast;
	cout<<" "<<endl;
	cout<<"dime: "<<rast.dimeSiEsCapturable(pe)<<endl;
	cout<<rast.CantSanciones(a)<<endl;

	return 0;
}