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
		Conj<Posicion> VecinosComunes(Posicion, Posicion);
		Posicion ProxPosicion(Direccion, Posicion);
		Conj<Posicion> IngresosMasCercanos(Posicion);
		Nat distancia(Posicion,Posicion) const;


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
	Conj<Posicion> vec;
	Posicion v1(pos.x+1,pos.y);
	Posicion v2(pos.x-1,pos.y);
	Posicion v3(pos.x,pos.y+1);
	Posicion v4(pos.x,pos.y-1);
	vec.Agregar(v1);
	vec.Agregar(v2);
	vec.Agregar(v3);
	vec.Agregar(v4);
	Conj<Posicion>::Iterador it = vec.CrearIt();
	while(it.HaySiguiente()){
		if(!PosValida(it.Siguiente())){
			it.EliminarSiguiente();
		}else{
			it.Avanzar();
		}
	}
	return vec;
}	

Conj<Posicion> Campus::VecinosComunes(Posicion p1, Posicion p2){
	Conj<Posicion> v1 = Vecinos(p1);
	Conj<Posicion> v2 = Vecinos(p2);
	Conj<Posicion> res;
	Conj<Posicion>::Iterador it = v1.CrearIt();
	while(it.HaySiguiente()){
		if(v2.Pertenece(it.Siguiente())){
			res.Agregar(it.Siguiente());
		}
		it.Avanzar();
	}
	return res;
}

Posicion Campus::ProxPosicion(Direccion dir, Posicion pos){
	if (dir==izq){
		pos = Posicion(pos.x-1,pos.y);
	}else if(dir==der){
		pos = Posicion(pos.x+1,pos.y);
	}else if(dir==arriba){
		pos = Posicion(pos.x,pos.y+1);
	}else{
		pos = Posicion(pos.x,pos.y-1);
	}
	return pos;
}


Nat Campus::distancia(Posicion p1, Posicion p2) const{
	Nat xGr = p1.x;
	Nat xCh = p2.x;
	Nat yGr = p1.y;
	Nat yCh = p2.y;
	if(p2.x > p1.x){
		xGr = p2.x;
		xCh = p1.x;
	}
	if(p2.y > p1.y){
		yGr = p2.y;
		yCh = p1.y;
	}
	return (xGr - xCh) + (yGr - yCh) ;
}

Conj<Posicion> Campus::IngresosMasCercanos(Posicion pos){
	Conj<Posicion> nuevo;
	Posicion ingSup = Posicion(pos.x, Filas());
	Posicion ingInf = Posicion(pos.x, 1);
	if(distancia(pos,ingInf) < distancia(pos,ingSup)){
		nuevo.Agregar(ingInf);
	}else if(distancia(pos,ingInf) > distancia(pos,ingSup)){
		nuevo.Agregar(ingSup);
	}else{
	nuevo.Agregar(ingInf);
	nuevo.Agregar(ingSup);
	}
	return nuevo;
}
















