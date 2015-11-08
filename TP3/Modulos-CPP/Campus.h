
#include "aed2.h"

	
class Campus
{
	public:
		Campus();
		Campus(const Nat columnas ,const Nat filas);
		//~Campus();
		Nat Filas() const;
		Nat Columnas() const;
		bool Ocupada(Posicion) const;
		void AgregarObstaculo(Posicion pos);
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

Campus::Campus(){
 filas=0;
 columnas=0;
 mapa=(Vector<Vector<bool> > ());
}

Campus::Campus(const Nat fil,const Nat col){
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

bool Campus::Ocupada(Posicion pos) const{
	return true;
}

void Campus::AgregarObstaculo(Posicion pos){
	mapa[pos.x-1][pos.y-1] = true;
}


