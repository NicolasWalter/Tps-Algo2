#ifndef CAMPUS_H_
#define	CAMPUS_H_

#include "TiposBasicos.h"
#include "Arreglo.h"
#include "Lista.h"
#include "Vector.h"
#include "Dicc.h"
#include "Conj.h"
#include "ConjAcotado.h"
#include "Tipos.h"


using namespace std;

namespace aed2{

	
class Campus
{
	public:
		Campus();
		Campus(Nat , Nat);
		Campus(const Campus& otro);
		Campus& operator=(const Campus& otra);
		Nat Fila() const;
		Nat Columna() const;
		bool Ocupadas(Posicion);
		void AgregarObstaculo(Posicion);
		bool PosValida(Posicion);
		bool EsIngreso	(Posicion);
		Conj<Posicion> Vecinos(Posicion);
		Conj<Posicion> VecinosComunes(Posicion, Posicion);
		Posicion ProxPosicion(Direccion, Posicion);
		Conj<Posicion> IngresosMasCercanos(Posicion);


	private:
		const Nat Filas;
		const Nat Columnas;
		Vector<Vector<bool> > Mapa; 
		
};
	template<class T>
	Campus::Campus() : Filas(0), Columnas(0)	{}

	template<class T>
	Campus::Campus(Nat columnas, Nat filas){
		Vector<Vector<bool> > mapa = vector(vector());
		Nat i = 0;
		while (i <= f){
			Vector<bool> nuevo = Vector();
			Nat j = 0;
			while (j <= c){
				nuevo.AgregarAtras(false);
				j++;
			}
			mapa.AgregarAtras(nuevo);
			i++;
		}
	this->Filas = filas;
	this->Columnas = columnas;
	this->Mapa = mapa;

	}


}

#endif