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
	//void AgregarOrdenado(Arreglo<TuplaPos> a, TuplaPos t);
};


//REVISAR SI SE DECLARA ASI O SE TIENE QUE DECLARAR COMO FUNCION DE LA CLASE (Descomentar la declaracion en private y agregar Rastrillaje::)
void AgregarOrdenado(Arreglo<TuplaPos> &a, TuplaPos t){
	Nat i=0;
	Nat n=a.Tamanho();
	while(i<n && a.Definido(i) && a[i].placa<t.placa){
		i++;
	}
	
	TuplaPos aux1=t;
    TuplaPos aux2;

	while(i<n && a.Definido(i)){
		aux2=a[i];
		//a[i]=aux1;
		a.Definir(i,aux1);
		aux1=aux2;
		i++;
	}
	if(! a.Definido(i)){
		a.Definir(i,aux1);
	}
}

Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d){
	DiccionarioProm<Agente,datosAg> dprom(d.CantClaves());
	Lista<datosK> Klista;
	Vector<Vector<datosPos> > map;
	for (Nat i=1; i<c.Filas(); i++){
		Vector<datosPos> filita;
		for(Nat j=1; i<c.Columnas();j++){
			Posicion pos(j,i);
			Conj<Nombre>::Iterador itN;
			Dicc<Agente,datosAg>::Iterador itA;
			if(c.Ocupada(pos)){
				datosPos dat1(false,obstaculo,itN,itA);
				filita.AgregarAtras(dat1);
			}else{
				datosPos dat2(false,nada,itN,itA);
				filita.AgregarAtras(dat2);
			}
		}
		map.AgregarAtras(filita);
	}
	Arreglo<TuplaPos> arr(d.CantClaves());
	Dicc<Agente,Posicion>::Iterador iter = d.CrearIt();
	Conj<Agente> vac;
	datosK dati(0,vac);
	Lista<datosK>::Iterador itk = Klista.AgregarAtras(dati);
	while(iter.HaySiguiente()){
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);//FALTA LA LINEA DE AGREGAR ORDENADO!!!!!!!!!!!!!
		datosAg datN(0,0,iter.SiguienteSignificado(),(itk.Siguiente().grupoK).Agregar(iter.SiguienteClave()),itk);
		
		//datosPos nuevoDP(true,agente,dprom.Definir) // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
		//map[iter.SiguienteSignificado().x][iter.SiguienteSignificado().y] = nuevoDP;
		iter.Avanzar();
	}
	campo = c;
	agentes = dprom;
	posAgentesLog = arr;
	Conj<datosHoE> hip;
	hippies = hip;
	Conj<datosHoE> est;
	estudiantes = est;
	DiccString<Nombre,Posicion> diccS;
	posCiviles = diccS;
	Dicc<Nombre,Posicion> diccL;
	posRapida = diccL;
	quienOcupa = map;
	//Conj<Agente>::Iterador masVig = dprom.CrearIt(); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
	//masVigilante = masVig;
	agregoEn1 = Klista;
	Vector<datosK> pLog;
	buscoEnLog = pLog;
	hayNuevas = false;
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



