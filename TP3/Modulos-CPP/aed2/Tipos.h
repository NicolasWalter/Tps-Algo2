#ifndef AED2_TIPOS_H_
#define AED2_TIPOS_H_

#include "TiposBasicos.h"


namespace aed2{
	struct Posicion{
		Nat x,y;
		Posicion(Nat a, Nat b) : x(a), y(b){}

		Posicion(const Posicion& p) : x(p.x), y(p.y) {}

		bool operator==(const Posicion& p1) const{
			return (p1.x==x) && (p1.y==y);
		}
		
		//bool operator!=(const Posicion& p1, const Posicion& p2){
		//	return (p1.x!=p2.x) || (p1.y!=p2.y);
		//}
	};

	typedef enum {izq,der,arriba,abajo} Direccion;
	typedef Nat Agente;
	typedef String Nombre;

} // namespace aed2

#endif // AED2_TIPOS_H_
