#include "Rastrillaje.h"
#include <iostream>
#include "aed2.h"
#include "mini_test.h"
#include <string>

using namespace std;

// DIFICIL
// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
void test_agregar_obstaculos() {
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	//campus.comenzarRastrillaje(agentes);


	Posicion p;
	p.x = 2; 
	p.y = 3;

	camp.AgregarObstaculo(p);

	ASSERT(camp.Ocupada(p) == true);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	ASSERT(camp.Ocupada(p2) == false);


}

void test_ingresa_estudiante(){
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarEstudiante(s,p2);	

	ASSERT(rast.dimeSiOcupada(p2) == true);

	Posicion p3 = rast.PosEstudianteYHippie(s);
	ASSERT(p3.x == p2.x && p3.y == p3.x);
}

// DIFICIL
void test_ingresa_hippie_y_convierte() {
	// Testea que cuando ingresa un hippie y esta rodeado de estudiantes se convierte
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p1;
	p1.x = 1; 
	p1.y = 1;

	Posicion p2;
	p2.x = 2; 
	p2.y = 1;


	Posicion p3;
	p3.x = 3; 
	p3.y = 1;

	Nombre s1 = "pepe";
	Nombre s2 = "pepo";
	Nombre s3 = "pepa";
	
	// Ingreso 3 estudiantes uno al lado del otro
	rast.IngresarEstudiante(s1,p1);	
	rast.IngresarEstudiante(s2,p2);	
	rast.IngresarEstudiante(s3,p3);	

	// Avanzo el estudiante del medio
	rast.MoverEstudiante(s2,abajo);

	// Ahora hago Ingresar un hippie,se tiene que convertir a estudiante
	Nombre h1 = "wololoHippie";
	rast.IngresarHippie(p2,h1);
	ASSERT(rast.cantEstudiantes() == 4);
	ASSERT(rast.cantHippies() == 0);
}

// DIFICIL
void test_mueve_estudiante_y_convierte() {
	// Testea que cuando se mueve un estudiante y rodea a un hippie se convierte
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p1;
	p1.x = 1; 
	p1.y = 1;

	Posicion p2;
	p2.x = 2; 
	p2.y = 1;


	Posicion p3;
	p3.x = 3; 
	p3.y = 1;

	Nombre s1 = "pepe";
	Nombre s2 = "pepo";
	Nombre s3 = "pepa";
	
	// Ingreso 3 estudiantes uno al lado del otro
	rast.IngresarEstudiante(s1,p1);	
	rast.IngresarEstudiante(s2,p2);	
	rast.IngresarEstudiante(s3,p3);	

	// Avanzo el estudiante del medio
	rast.MoverEstudiante(s2,abajo);
	rast.MoverEstudiante(s2,abajo);

	// Ahora hago Ingresar un hippie Y NO SE TIENE QUE CONVERTIR
	Nombre h1 = "wololoHippie";
	rast.IngresarHippie(p2,h1);
	
	ASSERT(rast.cantEstudiantes() == 3);
	ASSERT(rast.cantHippies() == 1);

	// Muevo el estudiante hacia arriba y tiene que convertir talannnn
	rast.MoverEstudiante(s2,arriba);

	ASSERT(rast.cantEstudiantes() == 4);
	ASSERT(rast.cantHippies() == 0);

}

void test_Mover_estudiante() {
	
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);


	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarEstudiante(s,p2);	
	rast.MoverEstudiante(s, abajo);

	Posicion p3;
	p3.x = 1; 
	p3.y = 2;

	ASSERT(rast.dimeSiOcupada(p2) == false);
	ASSERT(rast.dimeSiOcupada(p3) == true);

	Posicion p = rast.PosEstudianteYHippie(s);
	ASSERT(p3.x == p.x && p3.y == p.y);

}
void test_Mover_estudiante_fuera() {
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarEstudiante(s,p2);	
	rast.MoverEstudiante(s, arriba);

	
	ASSERT(rast.dimeSiOcupada(p2) == false);
	ASSERT(rast.cantEstudiantes() == 0);	
}


void test_ingresa_hippie() {
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarHippie(p2,s);	
	
	ASSERT(rast.dimeSiOcupada(p2) == true);

	Posicion p = rast.PosEstudianteYHippie(s);
	ASSERT(p2.x == p.x && p2.y == p.y);

}

void test_ingresa_hippie_y_estudiante() {
	// Idea de este test es probar el funcionamiento del Trie
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);


	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarHippie(p2,s);	

	Posicion p3;
	p3.x = 1; 
	p3.y = 2;

	Nombre t = "pepa";
	rast.IngresarEstudiante(t,p3);

	Posicion p;
	p.x = 1; 
	p.y = 3;

	Nombre r = "pepen";
	rast.IngresarEstudiante(r,p);	


	ASSERT(rast.iesimoHippie(0) == s);

	// No importa el orden, pero tienen que estar los dos
	ASSERT(rast.iesimoEstudiante(0) == t || rast.iesimoEstudiante(1) == t);
	ASSERT(rast.iesimoEstudiante(0) == r || rast.iesimoEstudiante(1) == r);

}

void test_Mover_hippie_a_estudiante() {
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);

	Posicion p;
	p.x = 1; 
	p.y = 1;

	Nombre t = "pepa";
	rast.IngresarEstudiante(t,p);

	rast.MoverEstudiante(t, abajo);
	rast.MoverEstudiante(t, abajo);
	rast.MoverEstudiante(t, abajo);
	rast.MoverEstudiante(t, abajo);
	rast.MoverEstudiante(t, abajo);

	// Baja el estudiante
	Posicion p3 = rast.PosEstudianteYHippie(t);
	ASSERT(p3.x == 1 && p3.y == 6);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarHippie(p2,s);	
	rast.MoverHippie(s);	

	// El hippie se mueve hacia abajo
	Posicion p4 = rast.PosEstudianteYHippie(s);
	ASSERT(p4.x == 1 && p4.y == 2);

	Posicion p5;
	p5.x = 3; 
	p5.y = 1;

	Nombre r = "pepo";
	rast.IngresarEstudiante(r,p5);

	// El hippie se mueve hacia el nuevo estudiante
	rast.MoverHippie(s);	
	p4 = rast.PosEstudianteYHippie(s);
	ASSERT((p4.x == 1 && p4.y == 1) || (p4.x == 2 && p4.y == 2) );

}



void test_Mover_hippie_a_ingreso() {
	// Idea del test: el hippie se mueve hacia el estudiante
	// Luego el estudiante se borra
	// Luego el hippie se mueve al ingreso mas cercano

	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Rastrillaje rast(camp,agentes);


	Posicion p;
	p.x = 1; 
	p.y = 1;

	Nombre t = "pepa";
	rast.IngresarEstudiante(t,p);

	for (int i=0; i < 5; i++) {
		rast.MoverEstudiante(t, abajo);
	}

	// Baja el estudiante
	Posicion p3 = rast.PosEstudianteYHippie(t);
	ASSERT(p3.x == 1 && p3.y == 6);

	Posicion p2;
	p2.x = 1; 
	p2.y = 1;

	Nombre s = "pepe";
	rast.IngresarHippie(p2,s);	
	rast.MoverHippie(s);	
	rast.MoverHippie(s);	

	// El hippie se mueve hacia abajo
	Posicion p4 = rast.PosEstudianteYHippie(s);
	ASSERT(p4.x == 1 && p4.y == 3);

	// Hago salir al estudiante, lo muevo a la derecha para no pisar el hippie
	rast.MoverEstudiante(t, der);
	for (int i=0; i < 6; i++) {
		rast.MoverEstudiante(t, arriba);
	}

	ASSERT(rast.cantEstudiantes() == 0);	

	// Muevo al hippie , tiene que ir al ingreso mas cercano
	rast.MoverHippie(s);	
	
	p4 = rast.PosEstudianteYHippie(s);

	ASSERT(p4.x == 1 && p4.y == 2);

}


void test_comenzar_rastrillaje_simple() {
	Campus camp(10,10);
	Dicc<Agente,Posicion> agentes;
	
	Agente a = 1;

	Posicion p;
	p.x = 1;
	p.y = 1;

	agentes.Definir(a,p);

	Rastrillaje rast(camp,agentes);
	ASSERT(rast.cantAgentes() == 1);
}


void test_rastrillaje_Mover_hacia_hippie() {
	
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;

	Posicion p;
	p.x = 1;
	p.y = 1;

	agentes.Definir(a,p);

	Rastrillaje rast(camp,agentes);

	Posicion ph;
	ph.x = 5;
	ph.y = 1;

	Nombre h = "hippie";
	rast.IngresarHippie(ph,h);

	rast.MoverAgente(a);

	Posicion p4 = rast.PosAgente(a);

	ASSERT(p4.x == 2 && p4.y == 1);

}


void test_captura_hippie_entre_agentes()
{
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	Rastrillaje rast(camp,agentes);

	Posicion ph;
	ph.x = 2;
	ph.y = 1;

	Nombre h = "hippie";
	rast.IngresarHippie(ph,h);

	ASSERT(rast.CantHippiesAtrapados(a) == 1);
	ASSERT(rast.CantHippiesAtrapados(a2) == 1);
	ASSERT(rast.CantHippiesAtrapados(a3) == 1);

	ASSERT(rast.MasVigilante() == a || rast.MasVigilante() == a2 || rast.MasVigilante() == a3);

}

/*void test_captura_estudiante()
{
	Campus camp(10,10);

	Dicc<Agente,Posicion> agentes;

	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	Rastrillaje rast(camp,agentes);

	Posicion pe;
	pe.x = 2;
	pe.y = 1;

	Nombre e = "pepe";
	rast.IngresarEstudiante(e,pe);

	ASSERT(rast.ConMismasSanciones(a).Cardinal() == 3 );
	ASSERT(rast.ConMismasSanciones(a2).Cardinal() == 3 );
	ASSERT(rast.ConMismasSanciones(a3).Cardinal() == 3 );
	//Nat c = rast.conKSanciones(1).Cardinal();
	//ASSERT(c == 3);

	//Nat c2 = rast.conKSanciones(0).Cardinal();
	//ASSERT(c2 == 0 );


}*/
/*
void test_mas_vigilante()
{
// 3 primeras lineas antes de que ingresen los estudiantes
//     1   2   3   4   5
// 1 | A |   | A |   | O
// 2 |   | A |   | O | 
// 3 ...
// Los hippies ingresan en (2,1) y (4,1) los huecos. El Agente en (3,1) se transforma en el mas vigilante	
	Driver campus;
	campus.crearCampus(10,10);

	Posicion o;
	o.x = 4; 
	o.y = 2;

	campus.agregarObstaculo(o);

	Posicion o2;
	o2.x = 5; 
	o2.y = 1;

	campus.agregarObstaculo(o2);


	Dicc<Agente,Posicion> agentes;
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	campus.comenzarRastrillaje(agentes);

	Posicion ph;
	ph.x = 2;
	ph.y = 1;

	Nombre h = "hippie";
	campus.IngresarHippie(h,ph);

	Posicion ph2;
	ph2.x = 4;
	ph2.y = 1;

	Nombre h2 = "hippie2";
	campus.IngresarHippie(h2,ph2);

	ASSERT(campus.cantHippiesAtrapados(a) == 1);
	ASSERT(campus.cantHippiesAtrapados(a2) == 1);
	ASSERT(campus.cantHippiesAtrapados(a3) == 2);

	ASSERT(campus.masVigilante() == a3);

}*/


int main(int argc, char **argv)
{
    RUN_TEST(test_agregar_obstaculos);
	RUN_TEST(test_ingresa_estudiante);
	RUN_TEST(test_Mover_estudiante);
	RUN_TEST(test_Mover_estudiante_fuera);
	RUN_TEST(test_ingresa_hippie);
	RUN_TEST(test_ingresa_hippie_y_estudiante);
	RUN_TEST(test_Mover_hippie_a_estudiante);
	RUN_TEST(test_Mover_hippie_a_ingreso);
	RUN_TEST(test_ingresa_hippie_y_convierte);
	RUN_TEST(test_mueve_estudiante_y_convierte);
	RUN_TEST(test_comenzar_rastrillaje_simple);
	RUN_TEST(test_rastrillaje_Mover_hacia_hippie);
	RUN_TEST(test_captura_hippie_entre_agentes);
	//RUN_TEST(test_captura_estudiante);
	//RUN_TEST(test_mas_vigilante);

	/********************************************************************
	 * TODO: escribir casos de test exhaustivos para todas              *
	 * las funcionalidades de cada módulo.                              *
     * La interacción con el TAD principal se debe hacer exclusivamente *
	 * a través de la interfaz del driver.                              *
	 ********************************************************************/

	return 0;
}
