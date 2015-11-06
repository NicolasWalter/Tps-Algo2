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

}

template<class K, class S>
DiccionarioProm<K, S>::~DiccionarioProm(){}

template<class K, class S>
bool DiccionarioProm<K, S>::Definido(const K& clave) const{}

template<class K, class S>
void DiccionarioProm<K, S>::Definir(const K& clave, const S& significado){}

template<class K, class S>
S& DiccionarioProm<K, S>::Obtener(const K& clave){}

template<class K, class S>
typename Conj<K>::Iterador DiccionarioProm<K, S>::Claves(){}

template<class K, class S>
const Nat DiccionarioProm<K, S>::fHash(const Nat n) const{}


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}