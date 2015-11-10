#include "Campus.h"
#include <iostream>
using namespace std;

int main(){
	Campus nuevo(2,3);
	Posicion pos(1,1);

	cout << pos.y << endl;
	cout << nuevo.Filas() << endl;
	return 0;
}