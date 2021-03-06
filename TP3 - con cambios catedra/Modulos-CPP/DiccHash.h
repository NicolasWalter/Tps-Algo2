#include "aed2.h"
using namespace std;
#include <iostream>

template<class K, class S>

class DiccionarioProm{
	public:
		struct TElem;

		DiccionarioProm();
		DiccionarioProm(const Nat n);
		~DiccionarioProm();
		bool Definido(const K& clave) const;
		void  Definir(const K& clave,  S& significado);
		S& Obtener(const K& clave);
		const S& Obtener(const K& clave) const;
		typename Conj<K>::const_Iterador Claves() const;
		typename Lista<TElem>::Iterador DefinirRapido(const K& clave, S& significado);
/*		DiccionarioProm<K,S>& operator=(const DiccionarioProm<K,S>& otro);
*/
		Conj<K> ClavesPublic() const;
		struct TElem{
			K 	 clave;
			S 	 significado;
			TElem(const K& c,  S& v) : clave(c), significado(v) {}
		};
	private:
		Nat clavesMax;
		Conj<K> cClaves;
		
		Arreglo<Lista<TElem> > 	tabla;
	 	Nat fHash(const Nat n) const;

};

/*template<class K, class S>
Dicc<K,S>& Dicc<K,S>::operator = (const Dicc<K,S>& otro)
{
  claves_ = otro.claves_;
  significados_ = otro.significados_;

  return *this;
}*/
/*template<class K, class S>
DiccionarioProm<K,S>& operator=(const DiccionarioProm<K,S>& otro) : cClaves(otro.cClaves), clavesMax(otro.clavesMax), tabla(otro.tabla) {}*/



template<class K, class S>
DiccionarioProm<K, S>::DiccionarioProm(){
	clavesMax=0;
	tabla = Arreglo<Lista<TElem> >();
}

template<class K, class S>
DiccionarioProm<K, S>::DiccionarioProm(const Nat n){
 	clavesMax = n;
  	cClaves = Conj<K>();
 	tabla = Arreglo<Lista<TElem> >(n);
 	for(Nat i=0; i<n; i++){
 		tabla.Definir(i,Lista<TElem>());
 	}
}

template<class K, class S>
DiccionarioProm<K, S>::~DiccionarioProm(){}

template<class K, class S>
 Nat DiccionarioProm<K, S>::fHash(const Nat n) const{
	return n % clavesMax;
}

template<class K, class S>
bool DiccionarioProm<K, S>::Definido(const K& clave) const{
	Nat i = fHash(clave);
	typename Lista<TElem>::const_Iterador it = tabla[i].CrearIt();
	bool aux=false;
	while(it.HaySiguiente()){
		if (it.Siguiente().clave==clave){
			aux=true;
		}
		it.Avanzar();
	}
	return aux;
}

template<class K, class S>
void DiccionarioProm<K, S>::Definir(const K& clave, S& significado){
	cClaves.Agregar(clave);					// agrego la clave al conjunto de claves
	Nat i= fHash(clave); 					//elijo la posicion de la tabla
	TElem tupla= TElem(clave,significado); 	// defino una tupla (clave,significado)
	tabla[i].AgregarAtras(tupla);			// agrego la tupla en la lista dentro de i
}

template<class K, class S>
S& DiccionarioProm<K, S>::Obtener(const K& clave){
	Nat i= fHash(clave); 					//elijo la posicion de la tabla
	typename Lista<TElem>::Iterador it = tabla[i].CrearIt();
	while(it.HaySiguiente()){
		if (it.Siguiente().clave==clave){
			return (it.Siguiente().significado);
		}
		it.Avanzar();
	}
}
template<class K, class S>
const S& DiccionarioProm<K, S>::Obtener(const K& clave) const{
	Nat i= fHash(clave); 					//elijo la posicion de la tabla
	typename Lista<TElem>::const_Iterador it = tabla[i].CrearIt();
	while(it.HaySiguiente()){
		if (it.Siguiente().clave==clave){
			return (it.Siguiente().significado);
		}
		it.Avanzar();
	}
}
template<class K, class S>
typename Conj<K>::const_Iterador DiccionarioProm<K, S>::Claves() const{
	typename Conj<K>::const_Iterador it = cClaves.CrearIt();
	return it;
}

template<class K, class S>
typename Lista<typename DiccionarioProm<K, S>::TElem>::Iterador DiccionarioProm<K, S>::DefinirRapido(const K& clave, S& significado){
	cClaves.Agregar(clave);					// agrego la clave al conjunto de claves
	Nat i= fHash(clave); 					//elijo la posicion de la tabla
	TElem tupla = TElem(clave,significado); 	// defino una tupla (clave,significado)
	tabla[i].AgregarAtras(tupla);			// agrego la tupla en la lista dentro de i
	typename Lista<typename DiccionarioProm<K, S>::TElem>::Iterador itin = tabla[i].CrearItUlt();
	itin.Retroceder();
	return itin;
}

template<class K, class S>
Conj<K> DiccionarioProm<K,S>::ClavesPublic() const{
	return cClaves;
}