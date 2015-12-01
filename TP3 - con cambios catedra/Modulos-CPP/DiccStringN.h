#include <assert.h>
#include <iostream>
#include "aed2.h"

using namespace std;
using namespace aed2;

template<class K, class S>
class DiccString{
private:

	struct Nodo{
		S significado;
		Nodo* caracteres[256];
		Nodo* padre;
		bool finPalabra;
		Nodo () :significado() , padre(NULL) , finPalabra(false) {for(Nat j=0; j< 256;j++){
			caracteres[j]=NULL;}
		};


	};
	Nodo* estr;



public:
	DiccString();
    ~DiccString();  
    void definir(const K, S);
    S& obtener(const K) const;
    void borrar(const K&);
    bool definido(const K&);
    bool todosNull(Nodo*[], int);
    void mataNodosRecu(Nodo*);
    DiccString<K,S>& operator=( DiccString<K,S>& otro); //es fruta,solo sirve al asignar tries recien creados



};
template<class K, class S>
void DiccString<K,S>::mataNodosRecu(Nodo* nodete){
	if(todosNull(nodete->caracteres,256)){
		delete nodete;
	}else{
		int i=0;
		while(i<256){
			if(nodete->caracteres[i]!=NULL){
				mataNodosRecu(nodete->caracteres[i]);
			}
			i++;
		}
		delete nodete;
	}
}

template<class K, class S>
DiccString<K,S>::DiccString(){
	Nodo* nuevo = new Nodo();
	estr=nuevo;
}

template<class K, class S>
DiccString<K,S>::~DiccString(){
	mataNodosRecu(this->estr);

}

template<class K, class S>
	void DiccString<K,S>::definir(const K clave, S signif){
	Nat i=0;
	Nodo* actual=estr;
	while(i<clave.size()){
		Nat ord=clave[i];
		if(actual->caracteres[ord]==NULL) {
			Nodo* nuevaLetra = new Nodo();
			nuevaLetra->padre=actual;
			actual->caracteres[ord]=nuevaLetra;
			actual = nuevaLetra;
		}else{
			actual=actual->caracteres[ord];
		}
		i++;
	}
	actual->significado=signif;
	actual->finPalabra = true;
}

template<class K, class S>
S& DiccString<K,S>::obtener(const K clave) const{
	Nat i=0;
	Nodo* actual=estr;
	while(i<clave.size()){
		Nat ord=clave[i];
		actual=actual->caracteres[ord];
		i++;
	}    	
	return (actual->significado);
}

template<class K, class S>
bool DiccString<K,S>::todosNull(Nodo* caracteres[], int n){
	int i=0;
	bool res=true;
	while(i<n){
		res=res && caracteres[i]==NULL;
		i++;
	}
	return res;
}

template<class K, class S>
void DiccString<K,S>::borrar(const K& clave){
	Nodo* actual=estr;
	int i=0;
	while(i<clave.size()){
		int ord=clave[i];
		actual=actual->caracteres[ord];
		i++;
	}
	actual->finPalabra=false;
	Nodo* camino=NULL;
	int lug=clave.size() -1;
	while(todosNull(actual->caracteres,256) && actual->padre!=NULL && actual->finPalabra==false) {
		camino=actual;
		actual=actual->padre;
		int ord2=clave[lug];
		actual->caracteres[ord2]=NULL;
		delete camino;
		lug--;

	}
}
    
template<class K, class S>
bool DiccString<K,S>::definido(const K& clave){
	int i=0;
	Nodo* actual=estr;
	bool def=true;
	while(i<clave.size() && def){
		int ord=clave[i];
		if((actual->caracteres[ord])==NULL){
			def=false;
		}else{
			actual=actual->caracteres[ord];
			i++;
		}
	}
	return (def && !(actual->finPalabra == false));
}


template<class K, class S>
DiccString<K,S>& DiccString<K,S>::operator = ( DiccString<K,S>& otro)
{
  estr = new Nodo();
  //significados_ = otro.significados_;

  return *this;
}