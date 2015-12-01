#include <string>
#include <iostream>
#include "aed2.h"

using namespace std;
 int main(int argc, char const *argv[])
 {
	 	DiccString<string,int> a;
	 	a.definir("A",10);
	 	cout<<a.definido("A")<<endl;
	 	cout<<a.obtener("A")<<endl;
	 	//cout<<a.definido("b")<<endl;
		
 	return 0;
 }
