#include "Driver.h"

namespace aed2 {

Driver::Driver() 
{
    // TODO
}

Driver::~Driver()
{
    // TODO
}


/// Generadores del Campus

void Driver::crearCampus(Nat ancho, Nat alto)
{
    // TODO
	camp=Campus(alto,ancho);
}

void Driver::agregarObstaculo(Posicion p)
{
    // TODO
	camp.AgregarObstaculo(p);
}


/// Observadores del Campus\

Nat Driver::filas() const
{
    // TODO
	return camp.Filas();
}

Nat Driver::columnas() const
{
    // TODO
	return camp.Columnas();
}

bool Driver::ocupada(Posicion p) const
{
    // TODO
	return camp.Ocupada(p);
}


/// Generadores de CampusSeguro
void  Driver::comenzarRastrillaje(const Dicc<Agente,Posicion>& d) {
    // TODO
	rast.ComenzarRastrillaje(camp,d);	
	//rast=rast2;
}

void Driver::ingresarEstudiante(Nombre n, Posicion p)
{
    // TODO
	rast.IngresarEstudiante(n,p);
}

void Driver::ingresarHippie(Nombre n, Posicion p)
{
    // TODO
	rast.IngresarHippie(p,n);
}

void Driver::moverEstudiante(Nombre n, Direccion d)
{
    // TODO
    rast.MoverEstudiante(n,d);
}

void Driver::moverHippie(Nombre n)
{
    // TODO
	rast.MoverHippie(n);
}

void Driver::moverAgente(Agente pl)
{
    // TODO
	rast.MoverAgente(pl);	
}


/// Observadores de CampusSeguro

Nombre Driver::iesimoEstudiante(Nat i) const{
    // TODO
	return rast.iesimoEstudiante(i);
}

Nombre Driver::iesimoHippie(Nat i) const{
    // TODO
	return rast.iesimoHippie(i);
}

Nat Driver::iesimoAgente(Nat i) const
{
	/*Lista<typename DiccionarioProm<Agente, datosAg>::TElem >::Iterador it = rast.agentes.CrearIt();
	Nat j=0;
	while(j<i){
		it.
	}*/	assert(false);
}

Nat Driver::cantEstudiantes() const {
    // TODO
	return rast.cantEstudiantes();
}

Nat Driver::cantHippies() const
{    // TODO
	return rast.cantHippies();	
}

Nat Driver::cantAgentes() const
{
    // TODO
	return rast.cantAgentes();
}

Posicion Driver::posEstudianteYHippie(Nombre n) const
{
	return rast.PosEstudianteYHippie(n);
}

Posicion Driver::posAgente(Agente pl) const
{
	return rast.PosAgente(pl);
}

Nat Driver::cantSanciones(Agente pl) const
{
    // TODO
	return rast.CantSanciones(pl);
}

Nat Driver::cantHippiesAtrapados(Agente pl) const
{
    // TODO
	return rast.CantHippiesAtrapados(pl);
}


/// Otras operaciones de CampusSeguro

Agente Driver::masVigilante() const
{
    // TODO
	return rast.MasVigilante();
}

const Conj<Agente> Driver::conMismasSanciones(Agente a) const
{
   
	return rast.ConMismasSanciones(a);
}

const Conj<Agente> Driver::conKSanciones(Nat k)
{
    // TODO
	return rast.ConKSanciones(k);
}


} // namespace aed2
