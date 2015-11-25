#include "Rastrillaje.h"
#include <iostream>
#include "aed2.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Dicc<Agente,Posicion> d;
	//d.Definir(11,Posicion(0,0));
	d.Definir(30,Posicion(1,3));
	Campus camp(4,4);
	camp.AgregarObstaculo(Posicion(2,2));
	Dicc<Agente,Posicion>::Iterador iter = d.CrearIt();
	Rastrillaje rast(camp,d);
	rast.IngresarHippie(Posicion(0,0),"a");
	rast.IngresarHippie(Posicion(0,2),"al");
	rast.IngresarEstudiante("eo",Posicion(3,1));
	rast.MoverHippie("al");
	//rast.MoverHippie("a");
	cout<<rast;
	cout<<" "<<endl;
	cout<<rast.dimeSiEsHippizable(Posicion(0,1))<<endl;
	rast.IngresarEstudiante("eu",Posicion(0,1));
	rast.IngresarEstudiante("gil",Posicion(0,3));
	cout<<rast;
	cout<<" "<<endl;
	rast.IngresarHippie(Posicion(0,2),"bardoo");
	cout<<rast;
	cout<<" "<<endl;


	Rastrillaje rast2(camp,d);
	rast2.IngresarHippie(Posicion(0,1),"ee");
	rast2.IngresarEstudiante("gil",Posicion(3,1));
	rast2.MoverHippie("ee");
	//rast.IngresarEstudiante("asd",Posicion(0,1));
	rast2.IngresarEstudiante("asde",Posicion(0,2));
	rast2.IngresarEstudiante("asdaa",Posicion(0,0));
	cout<<rast2;
	cout<<" "<<endl;
	rast2.MoverEstudiante("asdaa",abajo);
	rast2.MoverEstudiante("asde",abajo);
	cout<<rast2;
	cout<<" "<<endl;


	rast2.IngresarEstudiante("baaaaaaaardo",Posicion(0,1));
		cout<<rast2;
	cout<<" "<<endl;
	rast2.MoverEstudiante("gil",arriba);

	
	cout<<rast2;





	return 0;
}