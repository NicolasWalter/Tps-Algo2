#include "aed2.h"
#include "Campus.h"
#define ITHASH Lista<typename DiccionarioProm<Agente, datosAg>::TElem >::Iterador
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
	void IngresarHippie(Posicion, Nombre);
	void MoverEstudiante(Nombre e, Direccion d);
	void MoverHippie(Nombre h);
	void MoverAgente(Agente a);
	const Conj<Agente>& ConKSanciones(Nat k) const;
	ostream& mostrarRast(std::ostream& os ) const ;
	bool dimeQueHay(Posicion); //Despues podemos borrarla, es para testear no mas
	bool dimeSiEsCapturable(Posicion);
	//Direccion proxPosicionA(Agente);
	Nat dimeCantidadHippies();
	bool ocupadaD(Posicion, Direccion);
	//Direccion vecinoMasCercano(Posicion,Posicion);



	Posicion hippieObjetivo(Posicion p);
	Direccion queCaminoTomar(Posicion, Posicion);
	Posicion estudianteObjetivo(Posicion);



	bool esHippie(Posicion);

		void capturarHippie(Posicion);



private:

	struct datosPos{
		bool ocupada;
		Clases queHay;
		ITHASH hayCana; //falta el tipo del significado
		Conj<datosHoE>::Iterador hayHoE;
		datosPos(bool b, Clases c, ITHASH iter , Conj<datosHoE>::Iterador hoe) : ocupada(b), queHay(c), hayCana(iter), hayHoE(hoe)  {} 
		//en el constructor falta haycana
	};

	Campus campo;
	DiccionarioProm<Agente,datosAg> agentes;
	Arreglo<TuplaPos> posAgentesLog;
	Conj<datosHoE> hippies;
	Conj<datosHoE> estudiantes;
	DiccString<Nombre,Posicion> posCiviles; //esta comentado porque no esta terminado el modulo
	Dicc<Nombre,Posicion> posRapida;
	Vector<Vector<datosPos> > quienOcupa;
	Conj<Agente>::const_Iterador masVigilante;
	Lista<datosK> agregoEn1;
	Vector<datosK> buscoEnLog;
	bool hayNuevas;
	//void AgregarOrdenado(Arreglo<TuplaPos> a, TuplaPos t);
	bool esEstudiante(Posicion);
	//bool esHippie(Posicion);
	bool esAgente(Posicion);
	void estudiantizar(Posicion);
	void hippizar(Posicion);
	bool esCapturable(Posicion);
	bool esHippizable(Posicion);
	bool esEstudiantizable(Posicion);
//	void capturarHippie(Posicion);
	bool todasOcupadas(Posicion);
	void Recompensar(Posicion);
	void Sancionar(Posicion);
	//Direccion vecinoMasCercano(Posicion,Posicion);
	bool seFue(Posicion,Posicion);
	Direccion proxPosicionH(Nombre);
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

Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d) { // VER QUE ONDA LO DE METE EL HASH EN EL CONSTRUCTOR
	DiccionarioProm<Agente,datosAg> dprom(d.CantClaves());
	Lista<datosK> Klista;
	Vector<Vector<datosPos> > map;
	for (Nat i=0; i<c.Filas(); i++){
		Vector<datosPos> filita;
		for(Nat j=0; j<c.Columnas();j++){
			Posicion pos(i,j);
			Conj<datosHoE>::Iterador itN;
			ITHASH itA;
			if(c.Ocupada(pos)){
				datosPos dat1(true,obstaculo,itA,itN);
				filita.AgregarAtras(dat1);
			}else{
				datosPos dat2(false,nada,itA,itN);
				filita.AgregarAtras(dat2);
			}
		}
		map.AgregarAtras(filita);
	}
	Arreglo<TuplaPos> arr(d.CantClaves());
	Dicc<Agente,Posicion>::Iterador iter = d.CrearIt();
	Conj<Agente> vac;
	Conj<Agente> pruebaAg;
	datosK dati(0,vac);
	Lista<datosK>::Iterador itk = Klista.AgregarAtras(dati);
	while(iter.HaySiguiente()){
		pruebaAg.Agregar(iter.SiguienteClave());
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);
		datosAg datN(0,0,iter.SiguienteSignificado(),(itk.Siguiente().grupoK).Agregar(iter.SiguienteClave()),itk);
		Conj<datosHoE>::Iterador itAux;// iterador vacio!
		ITHASH itCanaDatos = dprom.DefinirRapido(iter.SiguienteClave(),datN);
		datosPos nuevoDP(true,agente,itCanaDatos,itAux); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
		map[iter.SiguienteSignificado().x][iter.SiguienteSignificado().y] = nuevoDP;
		iter.Avanzar();
	}
	campo = c;
	agentes = dprom; //PUEDE SER QUE HAGA FALTA UN OPERADOR =
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
	Conj<Agente>::const_Iterador masVig = dprom.Claves(); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
	masVigilante = masVig;
	agregoEn1 = Klista;
	Vector<datosK> pLog;
	Conj<Agente> agentesVacio;
	datosK datInicial(0,pruebaAg);
	pLog.AgregarAtras(datInicial);
	buscoEnLog = pLog;
	hayNuevas = false;
}


/*
Version caballero walter
Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d) : agentes(d.CantClaves()){
	Lista<datosK> Klista;
	Vector<Vector<datosPos> > map;
	for (Nat i=0; i<c.Filas(); i++){
		Vector<datosPos> filita;
		for(Nat j=0; j<c.Columnas();j++){
			Posicion pos(j,i);
			Conj<datosHoE>::Iterador itN;
			ITHASH itA;
			if(c.Ocupada(pos)){
				datosPos dat1(true,obstaculo,itA,itN);
				filita.AgregarAtras(dat1);
			}else{
				datosPos dat2(false,nada,itA,itN);
				filita.AgregarAtras(dat2);
			}
		}
		map.AgregarAtras(filita);
	}
	Arreglo<TuplaPos> arr(d.CantClaves());
	Dicc<Agente,Posicion>::Iterador iter = d.CrearIt();
	Conj<Agente> vac;
	Conj<Agente> pruebaAg;
	datosK dati(0,vac);
	Lista<datosK>::Iterador itk = Klista.AgregarAtras(dati);
	while(iter.HaySiguiente()){
		pruebaAg.Agregar(iter.SiguienteClave());
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);
		datosAg datN(0,0,iter.SiguienteSignificado(),(itk.Siguiente().grupoK).Agregar(iter.SiguienteClave()),itk);
		Conj<datosHoE>::Iterador itAux;// iterador vacio!
		ITHASH itCanaDatos = agentes.DefinirRapido(iter.SiguienteClave(),datN);
		datosPos nuevoDP(true,agente,itCanaDatos,itAux); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
		map[iter.SiguienteSignificado().x][iter.SiguienteSignificado().y] = nuevoDP;
		iter.Avanzar();
	}
	campo = c;
	//agentes = dprom; //PUEDE SER QUE HAGA FALTA UN OPERADOR =
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
	Conj<Agente>::const_Iterador masVig = agentes.Claves(); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!!
	masVigilante = masVig;
	agregoEn1 = Klista;
	Vector<datosK> pLog;
	Conj<Agente> agentesVacio;
	datosK datInicial(0,agentesVacio);
	pLog.AgregarAtras(datInicial);
	buscoEnLog = pLog;
	hayNuevas = false;
}*/

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

const Conj<Agente>& Rastrillaje::ConKSanciones(Nat k) const{

}
/*
				TO DO LIST

	REVISAR AUXILIARES: 
				       RECOMPENSAR(VER Q ONDA LO DE LOS ITERADORES)
					   SANCIONAR(PUEDE SER HORRIBLE)

	POSTAS:(Primero arreglar todo lo que ya pasamos)
			MOVER:
				  ESTUDIANTE
			INGRESAR:
					 ESTUDIANTE	

			ConKSanciones



*/




bool Rastrillaje::esEstudiante(Posicion p){
	return quienOcupa[p.x][p.y].queHay==estudiante;
}

bool Rastrillaje::esHippie(Posicion p){
	return quienOcupa[p.x][p.y].queHay==hippie;
}

bool Rastrillaje::esAgente(Posicion p){
	return quienOcupa[p.x][p.y].queHay==hippie;
}

void Rastrillaje::hippizar(Posicion p){
	Nombre n=quienOcupa[p.x][p.y].hayHoE.Siguiente().ID;
	typename Dicc<Nombre,Posicion>::Iterador it=quienOcupa[p.x][p.y].hayHoE.Siguiente().posActual;
	datosHoE dat(n,it);
	quienOcupa[p.x][p.y].hayHoE.EliminarSiguiente();
	typename Conj<datosHoE>::Iterador it2=hippies.AgregarRapido(dat);
	ITHASH itAuCC;
	datosPos aux(true,hippie,itAuCC,it2);
	quienOcupa[p.x][p.y] = aux; 
}	



void Rastrillaje::estudiantizar(Posicion p){
	Nombre n=quienOcupa[p.x][p.y].hayHoE.Siguiente().ID;
	typename Dicc<Nombre,Posicion>::Iterador it=quienOcupa[p.x][p.y].hayHoE.Siguiente().posActual;
	datosHoE dat(n,it);
	quienOcupa[p.x][p.y].hayHoE.EliminarSiguiente();
	typename Conj<datosHoE>::Iterador it2=estudiantes.AgregarRapido(dat);
	ITHASH itAuCC;
	datosPos aux(true,estudiante,itAuCC,it2);
	quienOcupa[p.x][p.y] = aux; 
}	

bool Rastrillaje::esCapturable(Posicion p){
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
	Nat contador=0;
	Nat i=0;
	bool hayGuardia=false;
	while(it.HaySiguiente()){
		if(quienOcupa[p.x][p.y].ocupada){
			contador++;
		}
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==agente){
			hayGuardia=true;
		}
		i++;
		it.Avanzar();
	}
	return contador==vecinetes.Cardinal() && hayGuardia;

}

bool Rastrillaje::esHippizable(Posicion p){
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
	Nat contador=0;
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==hippie){
			contador++;
		}
		it.Avanzar();
	}
	return contador>=2;

}

bool Rastrillaje::esEstudiantizable(Posicion p){
	typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
	Nat contador=0;
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==estudiante){
			contador++;
		}
		it.Avanzar();
	}
	return contador==4;
}

void Rastrillaje::capturarHippie(Posicion p){
	Nombre n = quienOcupa[p.x][p.y].hayHoE.Siguiente().ID;
	Dicc<Nombre,Posicion>::Iterador it = quienOcupa[p.x][p.y].hayHoE.Siguiente().posActual;
	it.EliminarSiguiente();
	quienOcupa[p.x][p.y].hayHoE.EliminarSiguiente();
	posCiviles.borrar(n);
	ITHASH itA;
	Conj<datosHoE>::Iterador itN;
	datosPos nuevo(false,nada,itA,itN);
	quienOcupa[p.x][p.y] = nuevo;
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador itPos=vecinetes.CrearIt();
	Nat i=0;
	while(i<vecinetes.Cardinal()){
		if(quienOcupa[itPos.Siguiente().x][itPos.Siguiente().y].queHay == agente){
			Recompensar(itPos.Siguiente());
		}
		i++;
		itPos.Avanzar();
	}
}




bool Rastrillaje::todasOcupadas(Posicion p){
	typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
	Nat contador=0;
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].ocupada){
			contador++;
		}
	}
	return contador==4;
}


void Rastrillaje::Recompensar(Posicion p){
	Agente a = quienOcupa[p.x][p.y].hayCana.Siguiente().clave;
	datosAg dat = agentes.Obtener(a);
	agentes.Obtener(a).premios=dat.premios+1;
	if(dat.premios>agentes.Obtener(masVigilante.Siguiente()).premios){
		masVigilante = quienOcupa[p.x][p.y].hayCana.Siguiente().significado.grupoSanciones; //ESTO ES UN ASCO. VER LA MANERA POSTA!
		if(dat.premios == agentes.Obtener(masVigilante.Siguiente()).premios){
			if(a<masVigilante.Siguiente()){
				masVigilante = quienOcupa[p.x][p.y].hayCana.Siguiente().significado.grupoSanciones; //ESTO ES UN ASCO. 
			}
		}
	}
}

void Rastrillaje::Sancionar(Posicion p){
	Agente a = quienOcupa[p.x][p.y].hayCana.Siguiente().clave;
	datosAg dat = agentes.Obtener(a);
	dat.Qsanciones++;
	dat.grupoSanciones.EliminarSiguiente();
	if(dat.verK.HaySiguiente()){
		dat.verK.Avanzar();
		hayNuevas=true;
		if(dat.verK.Siguiente().k == dat.Qsanciones){
			dat.grupoSanciones = dat.verK.Siguiente().grupoK.Agregar(a);
		}else{
			Conj<Agente> nuevo2;
			Conj<Agente>::Iterador iterConj = nuevo2.Agregar(a);
			datosK nuevo(dat.Qsanciones,nuevo2);
			dat.verK.AgregarComoAnterior(nuevo);
			dat.grupoSanciones = iterConj; //Problema de tipos, estoy asignandole a un it de conj un it de lista
		}	
	}else{
		//dat.verK.AgregarComoSiguiente(nuevo);
		hayNuevas=true;
		Conj<Agente> nuevo20;
		Conj<Agente>::Iterador iterConjj = nuevo20.Agregar(a);
		datosK nuevoo(dat.Qsanciones,nuevo20);
		dat.verK.AgregarComoSiguiente(nuevoo);
		dat.grupoSanciones = iterConjj;
	}
}
 

bool Rastrillaje::ocupadaD(Posicion p, Direccion dir){
	if (dir==arriba){
		return quienOcupa[p.x-1][p.y].ocupada;
	}else{
		if(dir==abajo){
			return quienOcupa[p.x+1][p.y].ocupada;
		}else{
			if(dir==izq){
				return quienOcupa[p.x][p.y-1].ocupada;
			}else{
				return quienOcupa[p.x][p.y+1].ocupada;
			}
		}
	}
}



Nat busquedaBin(Arreglo<TuplaPos> v, 	Nat objetivo){
	Nat i=0;
	Nat d=v.Tamanho()-1;
	while(i+1<d){
		Nat m=(i+d)/2;
		if(v[m].placa<objetivo){
			i=m;
		}else{
			d=m;
		}
	}
	if(v[i].placa==objetivo){
		return i;
	}else{
		return d;
	}
}

bool Rastrillaje::seFue(Posicion p, Posicion destino){
	return ((p.y==campo.Filas() && destino.y==campo.Filas()+1) || (p.y==0 && destino.y==-1));
}

void Rastrillaje::IngresarEstudiante(Nombre n, Posicion p){
	if (esHippizable(p)){
		if (esCapturable(p)){
			Conj<Posicion> v = campo.Vecinos(p);
			Conj<Posicion>::Iterador it = v.CrearIt();
			while (it.HaySiguiente()){
				if ((quienOcupa[it.Siguiente().x][it.Siguiente().y]).queHay == agente) {
					Recompensar(it.Siguiente());
				}
				it.Avanzar();
			}
		} else {
			posCiviles.definir(n,p);
			Dicc<Nombre,Posicion>::Iterador iterPos = posRapida.DefinirRapido(n,p);
			ITHASH itA;
			Conj<datosHoE>::Iterador itC;
			datosHoE dat(n,iterPos);
			itC = hippies.AgregarRapido(dat);
			datosPos dP(true,hippie,itA,itC);
			quienOcupa[p.x][p.y] = dP;
			Conj<Posicion> pS = campo.Vecinos(p);
			Conj<Posicion>::Iterador it = pS.CrearIt();
			while (it.HaySiguiente()){
				if (esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				} else {
					if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){
						Conj<Posicion> ag = campo.Vecinos(it.Siguiente());
						Conj<Posicion>::Iterador  itAg = ag.CrearIt();
						while (itAg.HaySiguiente()){
							if(esAgente(itAg.Siguiente())){
								Sancionar(itAg.Siguiente());
							}
							itAg.Avanzar();
						}
					} else {
						if(esHippie(it.Siguiente()) && esCapturable(it.Siguiente())){
							capturarHippie(it.Siguiente());
						}
					}
				}
				it.Avanzar();
			}
		}
	} else {
		posCiviles.definir(n,p);
		Dicc<Nombre,Posicion>::Iterador iterPos = posRapida.DefinirRapido(n,p);
		ITHASH itA;
		Conj<datosHoE>::Iterador itC;
		datosHoE dat(n,iterPos);
		itC = estudiantes.AgregarRapido(dat);
		datosPos dP(true,estudiante,itA,itC);
		quienOcupa[p.x][p.y] = dP;
		Conj<Posicion> pS = campo.Vecinos(p);
		Conj<Posicion>::Iterador it = pS.CrearIt();
		while (it.HaySiguiente()){
			if (esHippie(it.Siguiente()) && esEstudiantizable(it.Siguiente())){
				estudiantizar(it.Siguiente());
			} else {
				if (esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())) {
					Conj<Posicion>::Iterador itAg = campo.Vecinos(it.Siguiente()).CrearIt();
					while (itAg.HaySiguiente()){
						if (esAgente(itAg.Siguiente())){
							Sancionar(itAg.Siguiente());
						}
						itAg.Avanzar();
					}
				} else {
					if (esHippie(it.Siguiente()) && esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				}
			}
			it.Avanzar();
		}
	}
}



void Rastrillaje::IngresarHippie(Posicion p,Nombre h){
	posCiviles.definir(h,p);
	Dicc<Nombre,Posicion>::Iterador iterPos = posRapida.DefinirRapido(h,p);
	datosHoE datazo(h,iterPos);
	Conj<datosHoE>::Iterador itN=hippies.AgregarRapido(datazo);
	ITHASH itA;
	datosPos dat(true,hippie,itA,itN);
	quienOcupa[p.x][p.y]=dat;
	Conj<Posicion>::Iterador it;
	if(esCapturable(p)){
		capturarHippie(p);
	}else{
		while(it.HaySiguiente()){
			if(campo.Ocupada(it.Siguiente()) || quienOcupa[it.Siguiente().x][it.Siguiente().y].ocupada){
				it.Avanzar();
			}else{
				if(esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				}else{
					if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){
						Conj<Posicion>::Iterador itAg = campo.Vecinos(it.Siguiente()).CrearIt();
						while(itAg.HaySiguiente()){
							if(esAgente(itAg.Siguiente())){
								Sancionar(itAg.Siguiente());
							}
							itAg.Avanzar();
						}
					}
				}
			}
			it.Avanzar();
		}
	}
}

void Rastrillaje::MoverAgente(Agente a){
	Nat j=busquedaBin(posAgentesLog,a);
	Posicion actual=posAgentesLog[j].posi;
	if(hippieObjetivo(actual)!=actual){
		Direccion d=queCaminoTomar(actual,hippieObjetivo(actual));
		Posicion prx=campo.ProxPosicion(d,actual);
		agentes.Obtener(a).posActual=prx;
		posAgentesLog[j].posi=prx;
		ITHASH itA=quienOcupa[actual.x][actual.y].hayCana;
		ITHASH itAN;
		Conj<datosHoE>::Iterador itN;
		datosPos dat(false,nada,itAN,itN);
		quienOcupa[actual.x][actual.y]=dat;
		datosPos dat2(true,agente,itA,itN);
		quienOcupa[prx.x][prx.y]=dat2;
		Conj<Posicion> vecinetes=campo.Vecinos(prx);
		Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();// itero sobre los nuevos vecinos del agente
		while(it.HaySiguiente()){
			if((quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==obstaculo) || quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==nada){//Vacia u obstaculo -> nada

			}else{
				if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){// estudiante y capturable -> sanciono agentes
					Conj<Posicion> vecinosAg=campo.Vecinos(it.Siguiente());
					Conj<Posicion>::Iterador itAg=vecinosAg.CrearIt();
					int j=0;
					while(j<vecinosAg.Cardinal()){
						if(esAgente(itAg.Siguiente())){
							Sancionar(itAg.Siguiente());
						}
						j++;
						if(j==vecinosAg.Cardinal()){
						itAg.Avanzar();
						}
					}
				}else{
					if(esHippie(it.Siguiente()) && esCapturable(it.Siguiente())){// hippie y capturable -> lo hipizo (incluye premios)
						Posicion aux=it.Siguiente();
						capturarHippie(aux);
					}
				}
			}
			it.Avanzar();
		}
	}
}
void Rastrillaje::MoverHippie(Nombre h){
	Posicion actual=posCiviles.obtener(h);
	if(estudianteObjetivo(actual)!=actual){
		Direccion d=queCaminoTomar(actual,estudianteObjetivo(actual));
		Posicion prx=campo.ProxPosicion(d,actual);
		posCiviles.definir(h,prx);
		posRapida.Definir(h,prx);
		Conj<datosHoE>::Iterador itR=quienOcupa[actual.x][actual.y].hayHoE;
		Conj<datosHoE>::Iterador itNA;
		ITHASH itA;
		datosPos dat1(true,hippie,itA,itR);
		datosPos dat2(false,nada,itA,itNA);
		quienOcupa[prx.x][prx.y]=dat1;
		quienOcupa[actual.x][actual.y]=dat2;
		Conj<Posicion> vecinetes=campo.Vecinos(prx);
		Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
		while(it.HaySiguiente()){
			if((quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==obstaculo) || quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==nada){

			}else{
				if(esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				}else{
					if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){
						Conj<Posicion>::Iterador itAg=campo.Vecinos(it.Siguiente()).CrearIt();
						while(itAg.HaySiguiente()){
							if(esAgente(itAg.Siguiente())){
								Sancionar(itAg.Siguiente());
							}
							itAg.Avanzar();
						}
					}else{
						if(esHippie(it.Siguiente()) && esCapturable(it.Siguiente())){
							capturarHippie(it.Siguiente());
						}	
					}
				}
			}
			it.Avanzar();	
		}
	}
}	


void Rastrillaje::MoverEstudiante(Nombre s, Direccion d){
	Posicion actual = posCiviles.obtener(s);
	Posicion prx = campo.ProxPosicion(d, actual);
	ITHASH itA;
	Conj<datosHoE>::Iterador itC;
	Conj<datosHoE>::Iterador iterAHOI = quienOcupa[actual.x][actual.y].hayHoE;

	if (seFue(actual, prx)) {
		posCiviles.borrar(s);
//iterAHOI.Siguiente().posActual.EliminarSiguiente();
//iterAHOI.EliminarSiguiente(); POR ALGUNA RAZON NO ANDA
		datosPos dP(true,nada,itA,itC);
		quienOcupa[actual.x][actual.y] = dP;
	} else {
		Conj<datosHoE>::Iterador iterAHOI = quienOcupa[actual.x][actual.y].hayHoE;
		/*iterAHOI.Siguiente().posActual.EliminarSiguiente(); 
		iterAHOI.Siguiente().posActual = posRapida.definirRapido(s,prx);*/
		posCiviles.definir(s,prx);
		posRapida.Definir(s,prx);
		datosPos dP(true,estudiante,itA,iterAHOI);
		datosPos dataP(false,nada,itA,itC);
		quienOcupa[prx.x][prx.y] = dP;
		quienOcupa[actual.x][actual.y] = dataP;
		posCiviles.definir(s,prx);
		Conj<Posicion> vc = campo.Vecinos(prx);
		Conj<Posicion>::Iterador itPos = vc.CrearIt();
		if (esHippizable(prx)){
			hippizar(prx);
			while (itPos.HaySiguiente()){
				if ((quienOcupa[itPos.Siguiente().x][itPos.Siguiente().y].queHay==obstaculo) || quienOcupa[itPos.Siguiente().x][itPos.Siguiente().y].queHay==nada){

				}else {
					if (esEstudiante(itPos.Siguiente()) && esHippizable(itPos.Siguiente())){
						hippizar(itPos.Siguiente());
						if(esCapturable(itPos.Siguiente())){
							capturarHippie(itPos.Siguiente());
						}
					} else {
						if (esEstudiante(itPos.Siguiente()) && esCapturable(itPos.Siguiente())) {
							Conj<Posicion>::Iterador itAg = campo.Vecinos(itPos.Siguiente()).CrearIt();
							while (itAg.HaySiguiente()){
								if (esAgente(itAg.Siguiente())){
									Sancionar(itAg.Siguiente());
								}
								itAg.Avanzar();
							}
						} else {
							if (esHippie(itPos.Siguiente()) && esCapturable(itPos.Siguiente())){
								capturarHippie(itPos.Siguiente());
							}
						}
					}
				}
				itPos.Avanzar();
			}
		} else {
			while (itPos.HaySiguiente()){
				if ((quienOcupa[itPos.Siguiente().x][itPos.Siguiente().y].queHay==obstaculo) || quienOcupa[itPos.Siguiente().x][itPos.Siguiente().y].queHay==nada){
					itPos.Avanzar();
				} else {
					if (esEstudiante(itPos.Siguiente()) && esCapturable(itPos.Siguiente())) {
						Conj<Posicion>::Iterador itAg2 = campo.Vecinos(itPos.Siguiente()).CrearIt();
						while (itAg2.HaySiguiente()){
							if (esAgente(itAg2.Siguiente())){
								Sancionar(itAg2.Siguiente());
							}
							itAg2.Avanzar();
						} 
					} else {
						if (esHippie(itPos.Siguiente()) && esCapturable(itPos.Siguiente())){
							capturarHippie(itPos.Siguiente());
						}
					}
				}
				itPos.Avanzar();
			}
		}
	}
}


ostream& operator<<(ostream& out, const Rastrillaje& a) {
	return a.mostrarRast(out);
}

ostream& Rastrillaje::mostrarRast(std::ostream& os ) const {
	int i=0;
	while(i<campo.Filas()){
		int j=0;
		while(j<campo.Columnas()){
			if(quienOcupa[i][j].ocupada){
				if(quienOcupa[i][j].queHay==obstaculo){
					os<<"X ";
				}else  if(quienOcupa[i][j].queHay==agente){
					os<<"A ";
				}else if(quienOcupa[i][j].queHay==estudiante){
					os<<"E ";
				}else {
					os<<"H ";
				}
			}else{
					os<<"- ";					
			}
			j++;
		}
		os<<" "<<endl;
		i++;
	}
}

bool Rastrillaje::dimeQueHay(Posicion p){
	return quienOcupa[p.x][p.y].ocupada;
}

bool Rastrillaje::dimeSiEsCapturable(Posicion p){
	return esCapturable(p);
}

Nat Rastrillaje::dimeCantidadHippies(){
	return hippies.Cardinal();
}


//  FUNCIONES NUEVAS PARA MOVER 


Posicion Rastrillaje::hippieObjetivo(Posicion p){

	Conj<datosHoE>::Iterador it = hippies.CrearIt();
	if(it.HaySiguiente()){
		Dicc<Nombre,Posicion>::Iterador itdicca = it.Siguiente().posActual;
		Posicion minimo=itdicca.SiguienteSignificado();
		while(it.HaySiguiente()){
			Dicc<Nombre,Posicion>::Iterador itdicc = it.Siguiente().posActual;
			Posicion dondeHippie=itdicc.SiguienteSignificado();
			if(campo.distancia(p,dondeHippie)<campo.distancia(p,minimo) && !quienOcupa[dondeHippie.x][dondeHippie.y].ocupada){
				minimo=dondeHippie;
			}
			it.Avanzar();
		}
		return minimo;
	}else{
		if(campo.EsIngreso(p)){
			return p;
		}
		if(p.x<campo.Filas()/2){
			return Posicion(p.x-1,p.y);
		}else{
			return Posicion(p.x+1,p.y);
		}
	}

}

Posicion Rastrillaje::estudianteObjetivo(Posicion p){

	Conj<datosHoE>::Iterador it = estudiantes.CrearIt();
	if(it.HaySiguiente()){
		Dicc<Nombre,Posicion>::Iterador itdicca = it.Siguiente().posActual;
		Posicion minimo=itdicca.SiguienteSignificado();
		while(it.HaySiguiente()){
			Dicc<Nombre,Posicion>::Iterador itdicc = it.Siguiente().posActual;
			Posicion dondeHippie=itdicc.SiguienteSignificado();
			if(campo.distancia(p,dondeHippie)<campo.distancia(p,minimo) && !quienOcupa[dondeHippie.x][dondeHippie.y].ocupada){
				minimo=dondeHippie;
			}
			it.Avanzar();
		}
		return minimo;
	}else{
		if(campo.EsIngreso(p)){
			return p;
		}
		if(p.x<campo.Filas()/2){
			return Posicion(p.x-1,p.y);
		}else{
			return Posicion(p.x+1,p.y);
		}
	}

}

Direccion Rastrillaje::queCaminoTomar(Posicion d, Posicion h){
	if(d.x>h.x && !ocupadaD(d,arriba)){
		return arriba;
	}else if(d.x<h.x && !ocupadaD(d,abajo)){
		return abajo;
	}else if(d.y<h.y && !ocupadaD(d,der)){
		return der;
	}else{
		return izq;
	}
}


/*
Direccion Rastrillaje::proxPosicionH(Nombre h){
	typename Conj<datosHoE>::const_Iterador it=estudiantes.CrearIt();
	Posicion menorD = posRapida.Significado(h);
	Posicion p=menorD;
	if(! it.HaySiguiente()){
		if(menorD.y <= (campo.Filas()/2)){
			if(!ocupadaD(p,abajo)){
				return abajo;
			}else{
				if(!ocupadaD(p,der)){
					return der;
				}else{
					if(!ocupadaD(p,izq)){
						return izq;
					}else{
						return arriba;
					}
				}
			}
		}else{
			if(!ocupadaD(p,arriba)){
				return arriba;
			}else{
				if(!ocupadaD(p,der)){
					return der;
				}else{
					if(!ocupadaD(p,izq)){
						return izq;
					}else{
						return abajo;
					}
				}
			}

		}
	}else{
		Dicc<Nombre,Posicion>::Iterador nuevo=(it.Siguiente().posActual);
		menorD=nuevo.SiguienteSignificado();
		//Posicion nueva3=(it.Siguiente().posActual).SiguienteSignificado();
		Posicion otraPos;
		while(it.HaySiguiente()){
			Dicc<Nombre,Posicion>::Iterador aux=it.Siguiente().posActual;
			otraPos=aux.SiguienteSignificado();
			if(campo.distancia(p,otraPos)<campo.distancia(p,menorD)){
				menorD=otraPos;
			}
		}
		return vecinoMasCercano(p,menorD);
	}
}

Direccion Rastrillaje::proxPosicionA(Agente a){
	typename Conj<datosHoE>::const_Iterador it=hippies.CrearIt();
	Posicion menorD = agentes.Obtener(a).posActual;
	Posicion p=menorD;
	if(! it.HaySiguiente()){
		if(menorD.x > (campo.Filas()/2)){
				if(!ocupadaD(p,abajo)){
					return abajo;
				}else{
					if(!ocupadaD(p,der)){
						return der;
					}else{
						if(!ocupadaD(p,izq)){
							return izq;
						}else{
							return arriba;
						}
					}
				}
			}else{
				if(!ocupadaD(p,arriba)){
					return arriba;
				}else{
					if(!ocupadaD(p,der)){
						return der;
					}else{
						if(!ocupadaD(p,izq)){
							return izq;
						}else{
							return abajo;
						}
					}
				}

			}
	}else{
		Dicc<Nombre,Posicion>::Iterador nuevo=(it.Siguiente().posActual);
		menorD=nuevo.SiguienteSignificado();
		Posicion otraPos;
		while(it.HaySiguiente()){
			Dicc<Nombre,Posicion>::Iterador aux=it.Siguiente().posActual;
			otraPos=aux.SiguienteSignificado();			
			if(campo.distancia(p,otraPos) < campo.distancia(p,menorD)){
				menorD=otraPos;
			}
			it.Avanzar();
		}
		Direccion res= vecinoMasCercano(p,menorD);
		if(!ocupadaD(p,res)){
			return res;
		}else{
			if(!ocupadaD(p,arriba)){
					return arriba;
				}else{
					if(!ocupadaD(p,der)){
						return der;
					}else{
						if(!ocupadaD(p,izq)){
							return izq;
						}else{
							return abajo;
						}
					}
				}
		}
	}
	
}
*/


/*Direccion Rastrillaje::vecinoMasCercano(Posicion p, Posicion p2){
	//typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
	Direccion res;
	Posicion destino=it.Siguiente();
	Nat i=0;
	while(i<campo.Vecinos(p).Cardinal()){
		if(! quienOcupa[it.Siguiente().x][it.Siguiente().y].ocupada){
			if(campo.distancia(p,it.Siguiente())<campo.distancia(p,destino)){
				destino=it.Siguiente();
			}
		}
		i++;
		it.Avanzar();
	}

	if(destino.x<p.x){
		return arriba;
	}else if(destino.x>p.x){
		return abajo;
	}else if(destino.y<p.y){
		return der;
	}else{
		return izq;
	}
	

}*/