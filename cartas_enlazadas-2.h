#ifndef CARTAS_ENLAZADAS_H_
#define CARTAS_ENLAZADAS_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CartasEnlazadas {

  public:

	/**
	 * Crea un nuevo juego.
	 */	
	CartasEnlazadas();

	/**
	 * Una vez copiada, ambos juegos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CartasEnlazadas(const CartasEnlazadas<T>&);
	
	/**
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CartasEnlazadas();  
	
	/**
	* Agrega un jugador a la mesa. El mismo debe sentarse en la posición 
	* siguiente a la posición del jugador con el mazo azul. Por ejemplo si en la
	* mesa hay 3 jugadores sentados de la siguiente forma: [j1 j2 j3], y el 
	* mazo rojo lo tiene el jugador j3, la mesa debe quedar: [j1 j2 j3 j4].
	* PRE: el jugador a agregar no existe.
	*/
	void agregarJugador(const T&);
	
	/**
	* Adelanta el mazo rojo n posiciones. Por ejemplo: si en la mesa hay 3 
	* jugadores sentados de la siguiente forma: [j1 j2 j3] y el jugador j2
	* tiene el mazo rojo, si se adelanta 1 posicion el mazo rojo pasa al jugador j3. En
	* cambio si el mazo rojo se adelanta 2 posiciones el mazo rojo pasa al jugador j1.
	* En caso de que n sea negativo debe retroceder el mazo rojo -n posiciones.
	* PRE: existe al menos un jugador
	*/
	void adelantarMazoRojo(int n);
	
	/**
	* Adelanta el mazo azul n posiciones. Por ejemplo: si en la mesa hay 3 
	* jugadores sentados de la siguiente forma: [j1 j2 j3] y el jugador j2
	* tiene el mazo azul, si se adelanta 1 posicion el mazo azul pasa al jugador j3. En
	* cambio si el mazo azul se adelanta 2 posiciones el mazo azul pasa al jugador j1.
	* En caso de que n sea negativo debe retroceder el mazo azul -n posiciones.
	* PRE: existe al menos un jugador
	*/
	void adelantarMazoAzul(int n);
	
	/**
	* Devuelve el jugador que tiene el mazo Rojo actualmente.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugadorConMazoRojo() const;
	
	/**
	* Devuelve el jugador que tiene el mazo Azul actualmente.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugadorConMazoAzul() const;
	
	/**
	* Devuelve el jugador que se encuentra n posiciones adelante a la posicion 
	* del jugador con el mazo rojo. En caso de que n sea negativo deberia devolver 
	* el jugador que se encuentra -n posiciones atrás.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugador(int n) const;
	
	/**
	* Devuelve el jugador que se encuentra enfreantado al jugador que tiene el 
	* mazo rojo. Por ejemplo si en la mesa hay cuatros jugadores sentados de la
	* siguiente forma: [J1 J2 J3 J4] y el el jugador J2 tiene el mazo rojo, el
	* resultado debe ser J4.
	* PRE: cantidad de jugadores par, al menos un jugador
	*/
	const T& dameJugadorEnfrentado() const;
	
	/**
	* Elimina el jugador pasado como parámetro.
	* En el caso de que el jugador no exista, el método no debe hacer nada.
	* En el caso de que el jugador tenga algún mazo, se le pasa el mazo al 
	* siguiente jugador en la ronda.
	*/
	void eliminarJugador(const T&);
	
	/**
	* Elimina al jugador que tiene el mazo azul.
	* Por ejemplo si los jugadores estan sentadods de la siguiente forma: 
	* [J1 J2 J3 J4 J5] y el mazo lo tiene el jugador J3. Cuando se eliminan al 
	* jugador con  del mazo, la mesa * debería quedar de la siguiente forma 
	* [J1 J2 J4 J5].
	* En el caso de que algún jugador tenga algún mazo, se le pasa el mazo al 
	* siguiente jugador en la ronda.
	* PRE: al menos un jugador
	*/
	void eliminarJugadorConMazoAzul();
	
	/**
	* Dice si el jugador existe.
	*/
	bool existeJugador(const T&) const;

	/**
	* Le suma los puntos al jugador.
	* PRE: el jugador existe
	*/
	void sumarPuntosAlJugador(const T&, int);
	
	/**
	* Devuelve la cantidad de puntos que tiene el jugador pasado como 
	* parámetro.
	* PRE: el jugador existe
	*/
	int puntosDelJugador(const T&) const;
	
	/**
	* Devuelve al jugador que más puntos tiene.
	* PRE: hay un único jugador que tiene más puntos que todos los demás.
	*/
	const T& ganador() const;
	
	/*
	 * Dice si hay jugadores en la mesa.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de jugadores.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si los juegos son iguales.
	 */
	bool operator==(const CartasEnlazadas<T>&) const;	
	
	/*
	 * Debe mostrar la ronda por el ostream (y retornar el mismo).
	 * CartasEnlazadas vacio: []
	 * CartasEnlazadas con 1 elementos (e1 tiene el mazo azul y el rojo, p es el puntaje): [(e1,p)*]
	 * CartasEnlazadas con 2 elementos (e2 tiene el mazo azul y e1 el mazo rojo, p es el puntaje): [(e2,p), (e1,p)*]
	 * CartasEnlazadas con 3 elementos (e1 tiene el mazo, e3 fue agregado después que e2,
	 * e1 fue agregado antes que e2): [(e1, 0)*, (e3, 0), (e2, 0)]
	 */
	ostream& mostrarCartasEnlazadas(ostream&) const;
  private:
  
	/*
	 * No se puede modificar esta funcion.
	 */
	CartasEnlazadas<T>& operator=(const CartasEnlazadas<T>& otra) {
		assert(false);
		return *this;
	}


	/*
	 * Aca va la implementación del nodo.
	 */
    struct Nodo {
    	T elem;
    	Nodo* sig;
    	int puntos;
 		//Nodo* ant;
    };
    Nodo* prim;
    Nodo* ult;



   int mazoRojo; //posicion dond esta el mazo
    int mazoAzul;
    int posicion(const T&);
    int len;

};


template<class T>
ostream& operator<<(ostream& out, const CartasEnlazadas<T>& a) {
	return a.mostrarCartasEnlazadas(out);
}


// Implementación a hacer por los alumnos.
template<class T>
CartasEnlazadas<T>::CartasEnlazadas(){
	// Nodo* n = new Nodo;

	// n->elem = 0;
	// n->sig = n;
	// prim = n;
	// n->puntos=0;
	// ult = n;
	prim=NULL;
	ult=NULL;

	mazoRojo=-1;
	mazoAzul=-1;
	len=0;
}

template<class T>
CartasEnlazadas<T>::CartasEnlazadas(const CartasEnlazadas<T>& otra){
	*this=otra;
}

template<class T>
CartasEnlazadas<T>::~CartasEnlazadas(){
}

template<class T>
void CartasEnlazadas<T>::agregarJugador(const T& jug){
	Nodo* nuevo=new Nodo;
	Nodo* actual=prim;
	int pos=0;
	if(prim==NULL){
		prim=nuevo;
		ult=nuevo;
		nuevo->sig=nuevo;
		mazoAzul++;
		mazoRojo++;
	}else if(len==1 || mazoAzul==len-1){
		ult->sig=nuevo;
		ult=nuevo;
		nuevo->sig=prim;
	}else{
		while(pos<mazoAzul){
			//actual->ant=actual;
			actual=actual->sig;
			pos++;
		}
		nuevo->sig=actual->sig;
		actual->sig=nuevo;
		ult->sig=prim;
	}
		//nuevo->ant=actual;
	
		nuevo->elem=jug;
	
	len++;
}
template<class T>
void CartasEnlazadas<T>::adelantarMazoRojo(int n){
	mazoRojo=((mazoRojo+n)%len);
}

template<class T>
void CartasEnlazadas<T>::adelantarMazoAzul(int n){
	mazoAzul=((mazoAzul+n)%len);
}
template<class T>
const T& CartasEnlazadas<T>::dameJugadorConMazoRojo() const{
	int pos=0;
	Nodo* aux=prim;
	while(pos<mazoRojo){
		aux=aux->sig;
		pos++;
	}
	return aux->elem;
}

template<class T>
const T& CartasEnlazadas<T>::dameJugadorConMazoAzul() const{
	int pos=0;
	Nodo* aux=prim;
	while(pos<mazoAzul){
		aux=aux->sig;
		pos++;
	}
	return aux->elem;
}

template<class T>
int CartasEnlazadas<T>::tamanio() const{
	return len;
}




template<class T>
ostream& CartasEnlazadas<T>::mostrarCartasEnlazadas(ostream& os) const{
	// os << "[";
	// Nodo* actual = prim;
	// os << actual->elem << ",";
	// actual = actual -> sig;
	// while(actual != prim){
	// 	os << actual->elem;
	// 		if(actual != ult){
	// 			os << ",";
	// 		}
	// 	actual = actual -> sig;
	// }
	// os << "]";
	os << "[";
	Nodo* actual = prim;
	os <<"(" << actual->elem << "," << actual->puntos << ")" <<",";
	actual = actual -> sig;
	while(actual != prim && actual!=ult ){
		os <<"(" << actual->elem << "," << actual->puntos << ")"<<",";
			// if(actual != ult){
			// 	os << ",";
			// }else{break;}
		actual = actual -> sig;
	}

	os <<"(" << actual->elem << "," << actual->puntos << ")" << "]";

}





#endif //CARTAS_ENLAZADAS_H_
