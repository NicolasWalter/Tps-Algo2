#ifndef AED2_TIPOS_H_
#define AED2_TIPOS_H_

#include "TiposBasicos.h"


namespace aed2{
	typedef enum {izq,der,arriba,abajo} Direccion;
	typedef Nat Agente;
	typedef String Nombre;

	struct Posicion{
		Nat x,y;
		Posicion(Nat a, Nat b) : x(a), y(b){}

		Posicion(const Posicion& p) : x(p.x), y(p.y) {}

		bool operator==(const Posicion& p1) const{
			return (p1.x==x) && (p1.y==y);
		}
		
		bool operator!=(const Posicion& p1) const{
			return !((p1.x==x) && (p1.y==y));
		}

		Posicion& operator =(const Posicion& p1){
    		x = p1.x;
    		y = p1.y;
    		return *this;
		}

		Posicion(){}
	};

	struct datosK{
		Nat k;
		Conj<Agente> grupoK;
		datosK(Nat ka, Conj<Agente> gru) : k(ka), grupoK(gru) {}
	};


	struct datosAg{
		Nat Qsanciones;
		Nat premios;
		Posicion posActual;
		Conj<Agente>::Iterador grupoSanciones;
		Lista<datosK>::Iterador verK;

	datosAg(Nat q, Nat p,Posicion pos,Conj<Agente>::Iterador gr, Lista<datosK>::Iterador v) 
	: Qsanciones(q), premios(p), posActual(pos), grupoSanciones(gr), verK(v) {}
	};

	struct TuplaPos{
		Agente placa;
		Posicion posi;
		TuplaPos(Agente p, Posicion pos) : placa(p), posi(pos) {}
		TuplaPos(){}
		TuplaPos& operator =(const TuplaPos& t1){
    		placa = t1.placa;
    		posi = t1.posi;
    		return *this;
		}

	};

	struct datosHoE{
		Nombre ID;
		Dicc<Nombre,Posicion>::Iterador posActual;
		datosHoE(Nombre id, Dicc<Nombre,Posicion>::Iterador it ): ID(id), posActual(it) {}
	};

	typedef enum {agente,estudiante,hippie,obstaculo,nada} Clases;

	struct datosPos{
		bool ocupada;
		Clases queHay;
		Conj<Nombre>::Iterador hayHoE;
		Dicc<Agente,datosAg>::Iterador hayCana; //falta el tipo del significado
		datosPos(bool b, Clases c, Conj<Nombre>::Iterador hoe, Dicc<Agente,datosAg>::Iterador iter) : ocupada(b), queHay(c), hayHoE(hoe), hayCana(iter) {} 
		//en el constructor falta haycana
	};



} // namespace aed2

#endif // AED2_TIPOS_H_