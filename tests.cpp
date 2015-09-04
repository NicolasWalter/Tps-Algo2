// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests


//#include "mini_test.h"
#include <iostream>
#include "cartas_enlazadas-2.h"
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
l.agregarJugador(5);
l.agregarJugador(3);
 l.agregarJugador(4);
l.agregarJugador(6);
// l.agregarJugador(3);
//cout<<l.tamanio()<<endl;
l.adelantarMazoRojo(-3);
cout<< l.dameJugadorConMazoRojo()<<endl;
cout << l <<endl;
  return 0;
}

