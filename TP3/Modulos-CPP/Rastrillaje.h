#include "aed2.h"
#include "Campus.h"
#include "DiccHash.h"

class Rastrillaje
{
public:
	Rastrillaje(Campus c, Dicc<Agente, Posicion> d); //ComenzarRastrillaje
	~Rastrillaje();
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

	struct datosK
	{
		Nat K;
		Conj<Agente> grupoK;
		datosK(Nat ka, Conj<Agente> gru) : K(ka), grupoK(gru) {}
	};


	struct datosAg
	{
		Nat Qsanciones;
		Nat premios;
		Posicion posActual;
		Conj<Agente>::Iterador grupoSanciones;
		Lista<datosK>::Iterador verK;

	datosAg(Nat q, Nat p,Posicion pos,Conj<Agente>::Iterador gr, Lista<datosK>::Iterador v) 
	: Qsanciones(q), premios(p), posActual(pos), grupoSanciones(gr), verK(v) {}
	};

	struct TuplaPos
	{
		Nat placa;
		Posicion posi;
		TuplaPos(Nat p, Posicion pos) : placa(p), posi(pos) {}
	};

	struct datosHoE
	{
		Nombre ID;
		Dicc<Nombre,Posicion>::Iterador posActual;
		datosHoE(Nombre id, Dicc<Nombre,Posicion>::Iterador it ): ID(id), posActual(it) {}
	};

	typedef enum {agente,estudiante,hippie,obstaculo,nada} Clases;

	struct datosPos
	{
		bool ocupada;
		Clases queHay;
		Conj<Nombre>::Iterador hayHoE;
		//Dicc<Agente, >::Iterador hayCana; //falta el tipo del significado

		datosPos(bool o, Clases q, Conj<Nombre>::Iterador hoe) : ocupada(o), queHay(q), hayHoE(hoe) {} 
		//en el constructor falta haycana

	};

	Campus campo;
	DiccionarioProm<Agente,datosAg> agentes;
	Arreglo<TuplaPos> posAgentesLog;
	Conj<datosHoE> hippies;
	Conj<datosHoE> estudiantes;
	// DiccString<Nombre,Posicion> posCiviles; //esta comentado porque no esta terminado el modulo
	Dicc<Nombre,Posicion> posRapida;
	Vector<Vector<datosPos> > quienOcupa;
	Conj<Agente>::Iterador masVigilante;
	Lista<datosK> agregoEn1;
	Vector<datosK> buscoEnLog;
	bool hayNuevas;
};