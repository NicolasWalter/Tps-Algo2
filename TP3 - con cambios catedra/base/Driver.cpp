#include "Driver.h"

namespace aed2 {

Driver::Driver() 
{
    // TODO
	assert(false);
}

Driver::~Driver()
{
    // TODO
	assert(false);
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
	return camp.columnas();
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
}

void Driver::ingresarEstudiante(Nombre n, Posicion p)
{
    // TODO
	rast.IngresarEstudiante(n,p);
}

void Driver::ingresarHippie(Nombre n, Posicion p)
{
    // TODO
	rast.IngresarHippie(n,p);
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

Nombre Driver::iesimoEstudiante(Nat i) const
{
    // TODO
	Conj<datosHoE>::Iterador it = rast.estudiantes.CrearIt();
	Nat j=0;
	while(j < i){
		it.Avanzar();
		j++;
	}
	return it.Siguiente().ID;}

Nombre Driver::iesimoHippie(Nat i) const
{
    // TODO
	Conj<datosHoE>::Iterador it = rast.hippies.CrearIt();
	Nat j=0;
	while(j < i){
		it.Avanzar();
		j++;
	}
	return it.Siguiente().ID;}

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
	return rast.estudiantes.Cardinal();
}

Nat Driver::cantHippies() const
{    // TODO
	return rast.hippies.Cardinal();	
}

Nat Driver::cantAgentes() const
{
    // TODO
	assert(false);
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

const Driver::Conj<Agente> conMismasSanciones(Agente a) const
{
    // TODO
	return rast.ConMismasSanciones(a);
}

const Driver::Conj<Agente> conKSanciones(Nat k)
{
    // TODO
	assert(false);
}


} // namespace aed2

