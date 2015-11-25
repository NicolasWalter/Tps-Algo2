#include "Rastrillaje.h"
#include <iostream>
#include "aed2.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Dicc<Agente,Posicion> d;
	d.Definir(11,Posicion(1,2));
	d.Definir(3,Posicion(2,2));
	d.Definir(4,Posicion(1,1));
	d.Definir(70,Posicion(5,2));
	Campus camp(8,8);
	cout<<camp.Ocupada(Posicion(2,1))<<endl;
	camp.AgregarObstaculo(Posicion(0,3));
	camp.AgregarObstaculo(Posicion(1,2));
	camp.AgregarObstaculo(Posicion(0,5));
	Dicc<Agente,Posicion>::Iterador iter = d.CrearIt();
	Arreglo<TuplaPos> arr(d.CantClaves());
/*while(iter.HaySiguiente()){
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);
		iter.Avanzar();
	}
	int i=0;
	while(i<arr.Tamanho()){
		cout<<"("<<arr[i].placa<<" , "<<arr[i].posi.x<<arr[i].posi.y<<")";
		i++;
	}*/

	//cout<<camp.Ocupada(Posicion(2,1))<<endl;
	Rastrillaje rast(camp,d);
	//cout<<rast.ObsCampus().Ocupada(Posicion(2,1))<<endl;
	//cout<<rast.quienOcupa[1][2].queHay<<endl;
	cout<<"acaaaaaaaaaaa: "<<rast.dimeQueHay(Posicion(0,2))<<endl;
	cout<<rast.ocupadaD(Posicion(1,2),arriba)<<endl;
	cout<<rast;
	cout<<" "<<endl;
	rast.IngresarHippie(Posicion(0,4),"pacha");
	cout<<rast;
	cout<<" "<<endl;
		rast.MoverHippie("pacha");
			cout<<rast;



	//cout<<rast;
	cout<<" "<<endl;
	cout<<rast.PosAgente(4).x<<" "<<rast.PosAgente(4).y<<endl;
	rast.MoverAgente(4);
	cout<<rast.PosAgente(4).x<<" "<<rast.PosAgente(4).y<<endl;

	cout<<rast;
	cout<<"est objetivo: "<<rast.estudianteObjetivo(Posicion(3,3)).x<<" "<<rast.estudianteObjetivo(Posicion(3,3)).y<<endl;

	cout<<rast;
	cout<<rast.dimeCantidadHippies()<<endl;
		//cout<<"dir: "<<rast.proxPosicionA(4)<<endl;
		rast.dimeQueHay(Posicion(0,0));

		rast.MoverAgente(4);
			cout<<rast;
				cout<<" "<<endl;

			rast.MoverAgente(3);
			cout<<rast;

	//cout<<"dir: "<<rast.proxPosicionA(3)<<endl;
			rast.MoverAgente(3);
			cout<<rast;

	//cout<<"dir: "<<rast.proxPosicionA(3)<<endl;
	cout<<rast.dimeQueHay(Posicion(1,4))<<endl;
	cout<<rast.PosAgente(3).x<<" "<<rast.PosAgente(3).y<<endl;
	//cout<<	rast.vecinoMasCercano(Posicion(2,4),Posicion(0,4))<<endl;
	cout<< rast.hippieObjetivo(Posicion(2,4)).x<<" "<<rast.hippieObjetivo(Posicion(2,4)).y<<endl;
	cout<< rast.queCaminoTomar(Posicion(2,4),rast.hippieObjetivo(Posicion(2,4)))<<endl;
	cout<<rast.dimeCantidadHippies()<<endl;
/*	cout<<"premiooos: "<<rast.CantHippiesAtrapados(3)<<endl;

rast.MoverAgente(3);
			cout<<rast;
//rast.capturarHippie(Posicion(0,4));
	cout<<rast.dimeCantidadHippies()<<endl;
	cout<<rast.dimeQueHay(Posicion(0,4))<<endl;
	//rast.MoverAgente(4);
	cout<<"premiooos: "<<rast.CantHippiesAtrapados(3)<<endl;*/
	rast.IngresarEstudiante("walter",Posicion(7,4));
cout<<rast;
cout<<" "<<endl;
rast.MoverHippie("pacha");
cout<<rast;
	cout<<"est objetivo: "<<rast.estudianteObjetivo(Posicion(3,3)).x<<" "<<rast.estudianteObjetivo(Posicion(3,3)).y<<endl;
	rast.MoverEstudiante("walter",arriba);	
cout<<rast;
cout<<" "<<endl;
	//rast.agentes.Obtener(70);

	


	


	return 0;
}

