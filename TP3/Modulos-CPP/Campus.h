#include "aed2.h"
	
class Campus
{
	public:
		Campus();
		Campus(const Nat filas, const Nat columnas);
		~Campus();
		const Nat Filas() const;
		const Nat Columnas() const;
		bool Ocupada(Posicion) const;
		void AgregarObstaculo(Posicion pos);
		bool PosValida(Posicion) const;
		bool EsIngreso(Posicion) const;
		Conj<Posicion> Vecinos(Posicion);
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

Campus::~Campus(){}

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

const Nat Campus::Filas() const{
	return filas;
}

const Nat Campus::Columnas() const{
	return columnas;
}

bool Campus::Ocupada(Posicion pos) const{
	return mapa[pos.x][pos.y];
}

void Campus::AgregarObstaculo(Posicion pos){
	mapa[pos.x-1][pos.y-1] = true;
}

bool Campus::PosValida(Posicion pos) const{
	return (0 < pos.x) && (pos.x<=filas) && (0<pos.y) && (pos.y <= columnas);
}

bool Campus::EsIngreso(Posicion pos) const{
	return (pos.y == 1) || (pos.y==filas);
}

Conj<Posicion> Campus::Vecinos(Posicion pos){
	Conj<Posicion> nuevo;
	Posicion v1(pos.x+1,pos.y);
	//Posicion v2(pos.x-1,pos.y);
	//Posicion v3(pos.x,pos.y+1);
	//Posicion v4(pos.x,pos.y-1);
	//nuevo.Agregar(v1);
	//nuevo.Agregar(v2);
	//nuevo.Agregar(v3);
	//nuevo.Agregar(v4);
	return nuevo;
}	
















