#include "aed2.h"
//using namespace aed2;
using namespace std;
#include <iostream>

template<class K, class S>

class DiccionarioProm{
	public:
		DiccionarioProm(const Nat n);
		~DiccionarioProm();

		bool Definido(const K& clave) const;
		void  Definir(const K& clave, const S& significado);
		S& 	 Obtener(const K& clave);
		typename Conj<K>::Iterador Claves();
	

	private:
		Nat clavesMax;
		Conj<K> cClaves;
		
		struct TElem{
			K 	 clave;
			S 	 signif;

			TElem(const K& c, const S& v) : clave(c), signif(v) {}
		};


	Arreglo<Lista<TElem> > 	tabla;
	const Nat fHash(const Nat n) const;

};

template<class K, class S>
DiccionarioProm<K, S>::DiccionarioProm(const Nat n){
 clavesMax=n;
  cClaves= Conj<K>();
 tabla = Arreglo<Lista<TElem> >(n);
 for(Nat i=0; i<n; i++){
 	tabla[i]=Lista<TElem>();
 }
}

template<class K, class S>
DiccionarioProm<K, S>::~DiccionarioProm(){}

template<class K, class S>
const Nat DiccionarioProm<K, S>::fHash(const Nat n) const{
	return n % clavesMax;
}


template<class K, class S>
bool DiccionarioProm<K, S>::Definido(const K& clave) const{
	Nat i = fHash(clave,clavesMax);

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
void DiccionarioProm<K, S>::Definir(const K& clave, const S& significado){
	Nat i= fHash(clave,clavesMax); //elijo la posicion de la tabla
	TElem tupla= TElem(clave,significado); // defino una tupla (clave,significado)
	tabla[i].AgregarAtras(tupla);		// agrego la tupla en la lista dentro de i
	cClaves.Agregar(clave);				// agrego la clave al conjunto de claves
}

template<class K, class S>
S& DiccionarioProm<K, S>::Obtener(const K& clave){
	S& res;
	Nat i= fHash(clave,clavesMax); //elijo la posicion de la tabla
	typename Lista<TElem>::const_Iterador it = tabla[i].CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente().clave==clave){
				res= it.Siguiente().significado;
		}

		it.Avanzar();
	}
	return res;
}

template<class K, class S>
typename Conj<K>::Iterador DiccionarioProm<K, S>::Claves(){
	typename Conj<K>::Iterador it=cClaves.CrearIt();

}

 

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}