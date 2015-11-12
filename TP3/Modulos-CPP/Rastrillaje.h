#include "aed2.h"
#include "Campus.h"
class Rastrillaje
{
public:
	Rastrillaje(Campus c, Dicc<Agente, Posicion> d); //ComenzarRastrillaje
	//~Rastrillaje();
	Campus ObsCampus() const; // el nombre "Campus()" tira error, debe ser porque es el constructor de la clase campus.
	typename Conj<datosHoE>::const_Iterador Estudiantes() const; 
	typename Conj<datosHoE>::const_Iterador Hippies() const;
	typename Conj<Agente>::const_Iterador Agentes() const;
	Posicion PosEstudianteYHippie(Nombre id);
	Posicion PosAgente(Agente a);
	Nat CantSanciones(Agente a);
	Nat CantHippiesAtrapados(Agente a);
	Agente MasVigilante() const;
	Conj<Agente>::Iterador ConMismasSanciones(Agente a); //VER COMO HACER PARA QUE DEVUELVA CONJ<AGENTE>
	void IngresarEstudiante(Nombre e, Posicion p);
	void IngresarHippie(Nombre h, Posicion p);
	void MoverEstudiante(Nombre e, Direccion d);
	void MoverHippie(Nombre h);
	void MoverAgente(Agente a);
	Conj<Agente> ConKSanciones(Nat k) const;

private:
	Campus campo;
	DiccionarioProm<Agente,datosAg> agentes;
	Arreglo<TuplaPos> posAgentesLog;
	Conj<datosHoE> hippies;
	Conj<datosHoE> estudiantes;
	DiccString<Nombre,Posicion> posCiviles; //esta comentado porque no esta terminado el modulo
	Dicc<Nombre,Posicion> posRapida;
	Vector<Vector<datosPos> > quienOcupa;
	Conj<Agente>::Iterador masVigilante;
	Lista<datosK> agregoEn1;
	Vector<datosK> buscoEnLog;
	bool hayNuevas;
};

Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d){

}

Campus Rastrillaje::ObsCampus() const{
	return campo;
}

typename Conj<datosHoE>::const_Iterador Rastrillaje::Estudiantes() const{ //tendria que devolver cosas del tipo NOMBRE, arreglar.
	typename Conj<datosHoE>::const_Iterador iter = estudiantes.CrearIt();
	return iter;
}

typename Conj<datosHoE>::const_Iterador Rastrillaje::Hippies() const{	//tendria que devolver cosas del tipo NOMBRE, arreglar.
	typename Conj<datosHoE>::const_Iterador iter = hippies.CrearIt();
	return iter;
}

typename Conj<Agente>::const_Iterador Rastrillaje::Agentes() const{
	return agentes.Claves();
}

Posicion Rastrillaje::PosEstudianteYHippie(Nombre id){
	return posCiviles.obtener(id);
}

Posicion Rastrillaje::PosAgente(Agente a){
	return agentes.Obtener(a).posActual;
}

Nat Rastrillaje::CantSanciones(Agente a){
	return agentes.Obtener(a).Qsanciones;
}

Nat Rastrillaje::CantHippiesAtrapados(Agente a){
	return agentes.Obtener(a).premios;
}

Agente Rastrillaje::MasVigilante() const{
	return masVigilante.Siguiente();
}

Conj<Agente>::Iterador Rastrillaje::ConMismasSanciones(Agente a){ //VER COMO HACER PARA QUE DEVUELVA CONJ<AGENTE>
	return (agentes.Obtener(a).grupoSanciones);
}

