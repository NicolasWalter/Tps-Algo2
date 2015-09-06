// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests


//#include "mini_test.h"
#include <iostream>
#include "TpCasi.h"
using namespace std;


// template<typename T>
// string to_s(const T& m) {
//  	ostringstream os;
// 	os << m;
// 	return os.str();
//  }

/*
 * Crea una mesa de int vacia y no agrega elementos
 */
// void check_crear_mesa_vacia() {
//   CartasEnlazadas<int> mesa;

//   ASSERT_EQ(mesa.esVacia(), true);

//   ASSERT_EQ(mesa.tamanio(), 0);
// }

int main() {
 // RUN_TEST(check_crear_mesa_vacia);
CartasEnlazadas<int> l;
 l.agregarJugador(1);
 l.agregarJugador(2);
  l.agregarJugador(3);
  l.agregarJugador(4);

l.sumarPuntosAlJugador(1,10);
l.sumarPuntosAlJugador(2,10);
l.sumarPuntosAlJugador(3,11);
l.adelantarMazoAzul(2);
l.adelantarMazoRojo(-1);

CartasEnlazadas<int> r(l);

cout<<l.dameJugadorConMazoAzul()<<endl;
cout<<r.dameJugadorConMazoAzul()<<endl;
cout<<r.dameJugadorConMazoRojo()<<endl;
cout<<l.dameJugadorConMazoRojo()<<endl;

cout<<(r==l)<<endl;
//cout<<l.tamanio()<<endl;
cout<<l<<endl;
cout << r <<endl;
  return 0;
}

