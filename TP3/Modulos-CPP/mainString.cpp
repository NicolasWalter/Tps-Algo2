#include <string>
#include <iostream>

#include "aed2.h"

using namespace std;
 int main(int argc, char const *argv[])
 {
	 	DiccString<string,int> a;
	 	string wea="ar";
	 	string qlo="ab";
	 	string fome="a";


	 	a.definir(fome,200);
	 	a.definir(wea,12);
		cout<<(a.obtener(wea))<<endl;
		cout<<(a.obtener(fome))<<endl;
		cout<<(a.definido(wea))<<endl;
		a.borrar(wea);
		cout<<(a.definido(wea))<<endl;
	 	//cout<<*(a.estr->caracteres[97]->caracteres[114]->significado)<<endl;


		//string wea="abcda";
		//int x=wea[0];
	 	
	 	/*cout<<(a.obtener(wea))<<endl;
	 	cout<<a.definido(wea)<<endl;
	 	//a.definir(qlo,950);
	 	cout<<a.definido(qlo)<<endl;
	 	//a.borrar(wea);
	 	cout<<a.definido(fome)<<endl;
	 	cout<<(a.obtener(fome))<<endl;
	 	cout<<(a.obtener(wea))<<endl;*/
	 	//cout<<(a.obtener(qlo))<<endl;

	 	//cout<<(a.obtener(wea))<<endl;




	 	//cout<<*(a.estr->caracteres[97]->significado)<<endl;

	 	//cout<<(a.obtener(wea));
	 	//cout<<"este cout groso da: "<<*(a.estr->caracteres[97]->significado)<<endl;

	 	//cout<<a.definido("b")<<endl;
		
 	return 0;
 }
