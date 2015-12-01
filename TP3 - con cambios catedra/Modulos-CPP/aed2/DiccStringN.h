#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include "aed2.h"

using namespace std;
using namespace aed2;

template<class K, class S>
class DiccString{
private:

	struct Nodo{
		S* significado;
		Nodo* caracteres[256];
		Nodo* padre;
		Nodo () :significado(NULL) , padre(NULL){for(Nat j=0; j< 256;j++){
			caracteres[j]=NULL;
		}};

	};
	Nodo* estr;


public:
	DiccString();
    void definir(const K, S);
    S& obtener(const K);
    void borrar(const K&);
    bool definido(const K&);


};


	template<class K, class S>
	DiccString<K,S>::DiccString(){
		Nodo* letras[256];
		Nat i=0;
		while(i<255){
			letras[i]=NULL;
			i++;
		}
		Nodo* nuevo = new Nodo;
		nuevo->significado=NULL;
		for(Nat j=0; j< 256;j++){
			nuevo->caracteres[j]=letras[j];
		}
		nuevo->padre=NULL;
		estr=nuevo;
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
    	actual->significado=&signif;
 /*   	int x=2;
    	int* nuevo=&x;
    	actual->significado=nuevo;*/
    }

	template<class K, class S>
	S& DiccString<K,S>::obtener(const K clave){
    	Nat i=0;
    	Nodo* actual=estr;
    	while(i<clave.size()){
    		Nat ord=clave[i];
    		actual=actual->caracteres[ord];
    		i++;
    	}
    	
    	return *(actual->significado);

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
		actual->significado=NULL;
		Nodo* camino=NULL;
		while((actual->significado==NULL) || todosNull(actual->significado)){
			camino=actual;
			actual=actual->padre;
			delete camino;
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
		return (def && !(actual->significado ==NULL));
	}
