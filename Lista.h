#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <ostream>

typedef unsigned long Nat;

template <typename T>
class Lista
{
	public:

		/**
		 * Constructor por defecto.
		 * Crea una lista enlazada vacía. ( Operación Vacia() )
		 */
		Lista();

		/**
		 * Constructor por copia.
		 * Crea, por copia, una lista enlazada. (operación Copiar())
		 */
		Lista(const Lista& otra);

		/**
		 * Destructor.
		 * Destruye la lista, incluyendo los elementos 'T' alojados.
		 */
		~Lista();

		/**
		 * Operacion de asignacion.
		 * Recrea a la lista como una copia de la pasada como parámetro.
		 */
		Lista<T>& operator=(const Lista<T>& otra);

		//observadores

		/**
		 * Devuelve la cantidad de elementos almacenados en la lista.
		 */
		Nat longitud() const;

		/**
		 * Devuelve el i-esimo elemento (versión modificable)
		 */
		T& iesimo(Nat i);

		/**
		 * Devuelve el i-esimo elemento (versión no modificable)
		 */
		const T& iesimo(Nat i) const;

		/**
		 * Operacion de comparacion.
		 * Retorna verdadero si la lista es igual a otra pasada como
		 * parámetro, falso en caso contrario.
		 */
		bool operator==(const Lista<T>& otra) const;

		// algunas operaciones de lista

		/**
		 * Agrega un nuevo elemento como primer elemento de la lista.
		 */
		void agAdelante(const T& elem);

		/**
		 * Agrega un nuevo elemento como último elemento de la lista.
		 */
		void agAtras(const T& elem);

		/**
		 * Elimina al i-ésimo elemento de la lista.
		 */
		void eliminar(Nat i);

		/**
		 * Muestra la lista en un ostream
		 * formato de salida: [a_0, a_1, a_2, ...], donde a_i es
		 * el resultado del "mostrar" el elemento i de la lista
		 */
		void mostrar(std::ostream& o) const;

		template <typename S>
		friend std::ostream& operator<<(std::ostream& os, const Lista<S> &l);

	private:

		struct Nodo {
			T dato;
			Nodo* sig;
		};

		Nat len;
		Nodo* prim;
		Nodo* fin;
};

template <typename T>
Lista<T>::Lista()
	: len(0), prim(NULL), fin(NULL) {
}

template <typename T>
Lista<T>::Lista(const Lista& otra) {
	*this=otra;
}

template <typename T>
Lista<T>::~Lista() {
	int aux=len;
	for(int i=0;i<aux;i++){
		eliminar(0);
	}
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
	prim = NULL;
	fin = NULL;

	Nodo* aux = otra.prim;
	while(aux != NULL){
		agAtras(aux->dato);
		aux = aux->sig;
	}
}

template <typename T>
Nat Lista<T>::longitud() const {
	return len;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
	Nodo* actual;
	actual=prim;
	for(int j = 0; j<i;j++){
		actual = actual->sig;
	}
	return actual->dato;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
Nodo* actual;
	actual=prim;
	for(int j = 0; j<i;j++){
		actual = actual->sig;
	}
	return actual->dato;
}

template <typename T>
bool Lista<T>::operator==(const Lista<T>& otra) const {
	bool res=false;
	if(len==otra.len){
		Nodo* aux=prim;
		Nodo* aux2=otra.prim;
		res=true;
		while(aux!=NULL && res){
			res=(aux->dato==aux2->dato);
			aux=aux->sig;
			aux2=aux2->sig;
		}
	}
return res;
}

template <typename T>
void Lista<T>::agAdelante(const T& elem) {
	Nodo* n= new Nodo;
	if(prim==NULL){
		prim=n;
		fin=n;
		n->sig=NULL;
	}else{
		n->sig=prim;
		prim=n;
	}
	n->dato=elem;
	len++;
}

template <typename T>
void Lista<T>::agAtras(const T& elem) {
	Nodo* n = new Nodo;
	if(prim==NULL){
		prim=n;
		fin=n;
	}else{
		fin->sig = n;
		fin = n;
	}
	n->dato = elem;
	n->sig=NULL;
	len++;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
	Nodo* actual = prim;
	Nodo* anterior = prim;
	int pos = 0;
	if(i==0){
		prim = actual->sig;
		delete actual;
	}
	else if(i==len-1){
		while(pos<len-1){
			anterior=actual;
			actual=actual->sig;
			pos++;
		}
	fin = anterior;
	anterior->sig= NULL;
	delete actual;
	}else{
		while(pos<i){
			anterior=actual;
			actual=actual->sig;
			anterior->sig=actual->sig;
			pos++;
		}
	 delete actual;
	}
}

template <typename T>
void Lista<T>::mostrar(std::ostream& o) const {
	o << "[";
	Nodo* actual = prim;
	while(actual != NULL){
		o << actual->dato;
			if(actual != fin){
			o << ",";
			}
		actual = actual -> sig;
	}
	o << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Lista<T> &l) {
	l.mostrar(os);
	return os;
}
#endif // LISTA_H_
