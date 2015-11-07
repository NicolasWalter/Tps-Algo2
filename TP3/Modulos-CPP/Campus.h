#ifndef CAMPUS_H_
#define	CAMPUS_H_
#include "aed2.h"

	
class Campus
{
	public:
		Campus(const Nat columnas ,const Nat filas);
		~Campus();
		Nat Filas() const;
		Nat Columnas() const;
		bool Ocupadas(Posicion pos);
		// void AgregarObstaculo(Posicion);
		// bool PosValida(Posicion);
		// bool EsIngreso	(Posicion);
		// Conj<Posicion> Vecinos(Posicion);
		// Conj<Posicion> VecinosComunes(Posicion, Posicion);
		// Posicion ProxPosicion(Direccion, Posicion);
		// Conj<Posicion> IngresosMasCercanos(Posicion);


	private:
		Nat filas;
		Nat columnas;
		Vector<Vector<bool> > mapa; 
		
};


Campus::Campus(const Nat col,const Nat fil){
	Vector<Vector<bool> > map;
	Nat i = 0;
	while (i <= fil){
		Vector<bool> nuevo;
		Nat j = 0;
		while (j <= col){
			nuevo.AgregarAtras(false);
			j++;
		}
		map.AgregarAtras(nuevo);
		i++;
	}
	filas = fil;
	columnas = col;
	mapa = map;
}

Nat Campus::Filas() const{
	return filas;
}

Nat Campus::Columnas() const{
	return columnas;
}



#endif