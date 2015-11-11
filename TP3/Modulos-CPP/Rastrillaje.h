#include "aed2.h"
#include "Campus.h"
class Rastrillaje
{
public:
	Rastrillaje(Campus c, Dicc<Agente, Posicion> d); //ComenzarRastrillaje
	//~Rastrillaje();
	Campus ObsCampus() const; // el nombre "Campus()" tira error, debe ser porque es el constructor de la clase campus.
	Conj<Nombre> Estudiantes() const; // tengo dudas con estos const, creo que esta bien. (no modifica this)
	Conj<Nombre> Hippies() const;
	Conj<Agente> Agentes() const;
	Posicion PosEstudianteYHippie(Nombre id) const;
	Posicion PosAgente(Agente a) const;
	Nat CantSanciones(Agente a) const;
	Nat CantHippiesAtrapados(Agente a) const;
	void IngresarEstudiante(Nombre e, Posicion p);
	void IngresarHippie(Nombre h, Posicion p);
	void MoverEstudiante(Nombre e, Direccion d);
	void MoverHippie(Nombre h);
	void MoverAgente(Agente a);
	Agente MasVigilante() const;
	Conj<Agente> ConKSanciones(Nat k) const;
	Conj<Agente> ConMismasSanciones(Agente a) const;

private:
	Campus campo;
	DiccionarioProm<Agente,datosAg> agentes;
	Arreglo<TuplaPos> posAgentesLog;
	Conj<datosHoE> hippies;
	Conj<datosHoE> estudiantes;
	//DiccString<Nombre,Posicion> posCiviles; //esta comentado porque no esta terminado el modulo
	Dicc<Nombre,Posicion> posRapida;
	Vector<Vector<datosPos> > quienOcupa;
	Conj<Agente>::Iterador masVigilante;
	Lista<datosK> agregoEn1;
	Vector<datosK> buscoEnLog;
	bool hayNuevas;
};

Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d){

}