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
	Posicion PosEstudianteYHippie(Nombre id) const;
	Posicion PosAgente(Agente a);
	Nat CantSanciones(Agente a);
	Nat CantHippiesAtrapados(Agente a);
	Agente MasVigilante() const;
	Conj<Agente> ConMismasSanciones(Agente a) ; //VER COMO HACER PARA QUE DEVUELVA CONJ<AGENTE>
	void IngresarEstudiante(Nombre e, Posicion p);
	void IngresarHippie(Posicion, Nombre);
	void MoverEstudiante(Nombre e, Direccion d);
	void MoverHippie(Nombre h);
	void MoverAgente(Agente a);
	const Conj<Agente>& ConKSanciones(Nat k) const;
	ostream& mostrarRast(std::ostream& os ) const ;


	//Gallegadas para testear
	bool dimeSiEsEstudiante(Posicion);
	Agente dimeQueAgenteEs(Posicion);
	bool dimeQueHay(Posicion); 
	bool dimeSiEsCapturable(Posicion);
	bool dimeSiEsHippizable(Posicion);
	Nat dimeCantidadHippies();


	//COSAS Para el drive
	void ComenzarRastrillaje(Campus, Dicc<Agente, Posicion>); 
	Rastrillaje(); 
	Nat cantHippies() const;
	Nat cantEstudiantes() const;
	Nat cantAgentes() const;
	Nombre iesimoEstudiante(Nat) const;
	Nombre iesimoHippie(Nat) const;
	bool dimeSiOcupada(Posicion) const; //ocupada de rast

	void Sancionar(Posicion);


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
	DiccString<Nombre,Posicion> posCiviles; 
	Dicc<Nombre,Posicion> posRapida;
	Vector<Vector<datosPos> > quienOcupa;
	Agente masVigilanteP;
	Lista<datosK> agregoEn1;
	Vector<datosK> buscoEnLog;
	bool hayNuevas;


	//Auxiliar
	Conj<Agente> conjVacio; //va a ser util en con Ksanciones

	
	//funciones
	bool esEstudiante(Posicion);
	bool esHippie(Posicion);
	bool esAgente(Posicion);
	void estudiantizar(Posicion);
	void hippizar(Posicion);
	bool esCapturable(Posicion);
	bool esHippizable(Posicion);
	bool esEstudiantizable(Posicion);
	void capturarHippie(Posicion);
	bool todasOcupadas(Posicion);
	void Recompensar(Posicion);
	bool seFue(Posicion,Posicion);


	//PUBLICO O PRIVADO?
	Posicion hippieObjetivo(Posicion p);
	Direccion queCaminoTomar(Posicion, Posicion);
	Posicion estudianteObjetivo(Posicion);
	bool ocupadaD(Posicion, Direccion);

	

};

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

Nat busquedaBinK(Vector<datosK> v, 	Nat objetivo){
	Nat i=0;
	Nat d=v.Longitud()-1;
	while(i+1<d){
		Nat m=(i+d)/2;
		if(v[m].k<objetivo){
			i=m;
		}else{
			d=m;
		}
	}
	if(v[i].k==objetivo){
		return i;
	}else{
		return d;
	}
	return 4;
}

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
Rastrillaje::Rastrillaje(){
	
}

void Rastrillaje::ComenzarRastrillaje(Campus c, Dicc<Agente, Posicion> d){
DiccionarioProm<Agente,datosAg> dprom(d.CantClaves());
	Lista<datosK> Klista;
	Vector<Vector<datosPos> > map;
	for (Nat i=1; i<=c.Filas(); i++){
		Vector<datosPos> filita;
		for(Nat j=1; j<=c.Columnas();j++){
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
	conjVacio = vac;
	Conj<Agente> pruebaAg;
	//datosK dati(0,vac);
	Dicc<Agente,Posicion>::Iterador gadorcha = d.CrearIt();
	while(gadorcha.HaySiguiente()){
		vac.Agregar(gadorcha.SiguienteClave());
		gadorcha.Avanzar();
	}
	datosK datGadorcha(0,vac);
	agregoEn1 = Klista;
	Lista<datosK>::Iterador itKGadorcha = agregoEn1.AgregarAtras(datGadorcha);
	//agregoEn1 = Klista;




	//Lista<datosK>::Iterador itk = Klista.AgregarAtras(dati);//iterador que mira a la lista con el nodo (0,vac) ya agregado
	while(iter.HaySiguiente()){
		pruebaAg.Agregar(iter.SiguienteClave());
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);
		//Conj<Agente>::Iterador iteee=vac.Agregar(iter.SiguienteClave());//meto en vac el agente al que mira iter
		Conj<Agente>::Iterador iteGadorcha=vac.CrearIt();
		datosAg datN(0,0,iter.SiguienteClave(),iter.SiguienteSignificado(),iteGadorcha,itKGadorcha);//0 premios y sanc, wachem, pos, iterador a vac, iterador a klista
		Conj<datosHoE>::Iterador itAux;// iterador vacio!
		ITHASH itCanaDatos = dprom.DefinirRapido(iter.SiguienteClave(),datN);//meto al agente con sus datos en el hash
		datosPos nuevoDP(true,agente,itCanaDatos,itAux); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!! <--- comentario viejo?
		map[iter.SiguienteSignificado().y -1][iter.SiguienteSignificado().x -1] = nuevoDP;

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
	
	Dicc<Agente,Posicion>::Iterador iterMV = d.CrearIt();
	Conj<Agente> nuevoVacio;
	if(iterMV.HaySiguiente()){
		Agente menorPlaca=iterMV.SiguienteClave();
		while(iterMV.HaySiguiente()){
			if(iterMV.SiguienteClave() < menorPlaca){
				menorPlaca=iterMV.SiguienteClave();
			}
			iterMV.Avanzar();
		}
		masVigilanteP=menorPlaca;
	}

	Vector<datosK> pLog;
	Conj<Agente> agentesVacio;
	datosK datInicial(0,pruebaAg);
	pLog.AgregarAtras(datInicial);
	buscoEnLog = pLog;
	hayNuevas = false;	

}
Rastrillaje::Rastrillaje(Campus c, Dicc<Agente, Posicion> d) { // VER QUE ONDA LO DE METE EL HASH EN EL CONSTRUCTOR
DiccionarioProm<Agente,datosAg> dprom(d.CantClaves());
	Lista<datosK> Klista;
	Vector<Vector<datosPos> > map;
	for (Nat i=1; i<=c.Filas(); i++){
		Vector<datosPos> filita;
		for(Nat j=1; j<=c.Columnas();j++){
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
	conjVacio=vac;

	Conj<Agente> pruebaAg;
	//datosK dati(0,vac);
	Dicc<Agente,Posicion>::Iterador gadorcha = d.CrearIt();
	while(gadorcha.HaySiguiente()){
		vac.Agregar(gadorcha.SiguienteClave());
		gadorcha.Avanzar();
	}
	datosK datGadorcha(0,vac);
	agregoEn1 = Klista;
	Lista<datosK>::Iterador itKGadorcha =agregoEn1.AgregarAtras(datGadorcha);
	//agregoEn1 = Klista;




	//Lista<datosK>::Iterador itk = Klista.AgregarAtras(dati);//iterador que mira a la lista con el nodo (0,vac) ya agregado
	while(iter.HaySiguiente()){
		pruebaAg.Agregar(iter.SiguienteClave());
		TuplaPos nCana(iter.SiguienteClave(),iter.SiguienteSignificado());
		AgregarOrdenado(arr,nCana);
		//Conj<Agente>::Iterador iteee=vac.Agregar(iter.SiguienteClave());//meto en vac el agente al que mira iter
		Conj<Agente>::Iterador iteGadorcha=vac.CrearIt();
		datosAg datN(0,0,iter.SiguienteClave(),iter.SiguienteSignificado(),iteGadorcha,itKGadorcha);//0 premios y sanc, wachem, pos, iterador a vac, iterador a klista
		Conj<datosHoE>::Iterador itAux;// iterador vacio!
		ITHASH itCanaDatos = dprom.DefinirRapido(iter.SiguienteClave(),datN);//meto al agente con sus datos en el hash
		datosPos nuevoDP(true,agente,itCanaDatos,itAux); // FALTA UN DEFINIR EN DICCPROM QUE TE DEVUELVA UN ITERADOR!!!!!!!!! <--- comentario viejo?
		map[iter.SiguienteSignificado().y -1][iter.SiguienteSignificado().x -1] = nuevoDP;

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
	
	Dicc<Agente,Posicion>::Iterador iterMV = d.CrearIt();
	Conj<Agente> nuevoVacio;
	if(iterMV.HaySiguiente()){
		Agente menorPlaca=iterMV.SiguienteClave();
		while(iterMV.HaySiguiente()){
			if(iterMV.SiguienteClave() < menorPlaca){
				menorPlaca=iterMV.SiguienteClave();
			}
			iterMV.Avanzar();
		}
		masVigilanteP=menorPlaca;
	}

	Vector<datosK> pLog;
	Conj<Agente> agentesVacio;
	datosK datInicial(0,pruebaAg);
	pLog.AgregarAtras(datInicial);
	buscoEnLog = pLog;
	hayNuevas = false;	

}


Campus Rastrillaje::ObsCampus() const{
	return campo;
}

typename Conj<datosHoE>::const_Iterador Rastrillaje::Estudiantes() const{ //tendria que devolver cosas del tipo NOMBRE, arreglar? O flasheada vieja?
	typename Conj<datosHoE>::const_Iterador iter = estudiantes.CrearIt();
	return iter;
}

typename Conj<datosHoE>::const_Iterador Rastrillaje::Hippies() const{	//tendria que devolver cosas del tipo NOMBRE, arreglar? O flasheada vieja?
	typename Conj<datosHoE>::const_Iterador iter = hippies.CrearIt();
	return iter;
}

typename Conj<Agente>::const_Iterador Rastrillaje::Agentes() const{
	return agentes.Claves();
}

Posicion Rastrillaje::PosEstudianteYHippie(Nombre id) const{
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
	return masVigilanteP;
}

Conj<Agente> Rastrillaje::ConMismasSanciones(Agente a){ //VER COMO HACER PARA QUE DEVUELVA CONJ<AGENTE>
	return agentes.Obtener(a).verK.Siguiente().grupoK;
	//return res;
}

const Conj<Agente>& Rastrillaje::ConKSanciones(Nat q) const{
	Nat posibleIndex= busquedaBinK(buscoEnLog,q);
	if(buscoEnLog[posibleIndex].k == q){
		return buscoEnLog[posibleIndex].grupoK;
	}else{
		return conjVacio;
	}
}





//AUXILIARES USADAS AL MOVER/INGRESAR
bool Rastrillaje::esEstudiante(Posicion p){
	return quienOcupa[p.y -1][p.x -1].queHay==estudiante;
}

bool Rastrillaje::esHippie(Posicion p){
	return quienOcupa[p.y -1][p.x -1].queHay==hippie;
}

bool Rastrillaje::esAgente(Posicion p){
	return quienOcupa[p.y -1][p.x -1].queHay==agente;
}

void Rastrillaje::hippizar(Posicion p){
	Nombre n=quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().ID;
	typename Dicc<Nombre,Posicion>::Iterador it=quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().posActual;
	datosHoE dat(n,it);
	quienOcupa[p.y -1][p.x -1].hayHoE.EliminarSiguiente();
	typename Conj<datosHoE>::Iterador it2=hippies.AgregarRapido(dat);
	ITHASH itAuCC;
	datosPos aux(true,hippie,itAuCC,it2);
	quienOcupa[p.y -1][p.x -1] = aux; 
}	



void Rastrillaje::estudiantizar(Posicion p){
	Nombre n=quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().ID;
	typename Dicc<Nombre,Posicion>::Iterador it=quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().posActual;
	datosHoE dat(n,it);
	quienOcupa[p.y -1][p.x -1].hayHoE.EliminarSiguiente();
	typename Conj<datosHoE>::Iterador it2=estudiantes.AgregarRapido(dat);
	ITHASH itAuCC;
	datosPos aux(true,estudiante,itAuCC,it2);
	quienOcupa[p.y -1][p.x -1] = aux; 
}	

bool Rastrillaje::esCapturable(Posicion p){
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
	Nat contador=0;
	Nat i=0;
	bool hayGuardia=false;
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].ocupada){
			contador++;
		}
		if(quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==agente){
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
		if(quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==hippie){
			contador++;
		}
		it.Avanzar();
	}
	return contador>=2;

}

bool Rastrillaje::esEstudiantizable(Posicion p){
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
	Nat contador=0;
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==estudiante){
			contador++;
		}
		it.Avanzar();
	}
	return contador==vecinetes.Cardinal();
}

void Rastrillaje::capturarHippie(Posicion p){
	Nombre n = quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().ID;
	Dicc<Nombre,Posicion>::Iterador it = quienOcupa[p.y -1][p.x -1].hayHoE.Siguiente().posActual;
	it.EliminarSiguiente();
	quienOcupa[p.y -1][p.x -1].hayHoE.EliminarSiguiente();
	posCiviles.borrar(n);
	ITHASH itA;
	Conj<datosHoE>::Iterador itN;
	datosPos nuevo(false,nada,itA,itN);
	quienOcupa[p.y -1][p.x -1] = nuevo;
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador itPos=vecinetes.CrearIt();
	Nat i=0;
	while(i<vecinetes.Cardinal()){
		if(quienOcupa[itPos.Siguiente().y -1][itPos.Siguiente().x -1].queHay == agente){
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
		if(quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].ocupada){
			contador++;
		}
	}
	return contador==4;
}


/*void Rastrillaje::Recompensar(Posicion p){
	ITHASH canita=quienOcupa[p.y -1][p.x -1].hayCana;
	Agente a = canita.Siguiente().significado.wachem;
	datosAg dat = agentes.Obtener(a);
	datosAg viejoGorra=agentes.Obtener(masVigilante.Siguiente());
	agentes.Obtener(a).premios=dat.premios+1;
	if(dat.premios+1>viejoGorra.premios){
		Conj<Agente> vacioNuevo;
		vacioNuevo.Agregar(a);
		Conj<Agente>::const_Iterador nMV= vacioNuevo.CrearIt();
		masVigilante = nMV; 
	}else{
		if(dat.premios+1 == viejoGorra.premios){
			if(a<viejoGorra.wachem){
				Conj<Agente> vacioNuevo;
				vacioNuevo.Agregar(a);
				Conj<Agente>::const_Iterador nMV= vacioNuevo.CrearIt();
				masVigilante = nMV; 
			}
		}
	}	
}*/

void Rastrillaje::Recompensar(Posicion p){
	ITHASH canita=quienOcupa[p.y -1][p.x -1].hayCana;
	Agente a = canita.Siguiente().significado.wachem;
	datosAg dat = agentes.Obtener(a);
	datosAg viejoGorra=agentes.Obtener(masVigilanteP);
	agentes.Obtener(a).premios=dat.premios+1;
	if(dat.premios+1>viejoGorra.premios){
		masVigilanteP = a; 
	}else{
		if(dat.premios+1 == viejoGorra.premios){
			if(a<viejoGorra.wachem){
				masVigilanteP=a; 
			}
		}
	}	
}

void Rastrillaje::Sancionar(Posicion p){
	ITHASH canita = quienOcupa[p.y -1][p.x -1].hayCana;
	Agente a = canita.Siguiente().significado.wachem;//Debe explotar aca
	datosAg dat = agentes.Obtener(a);
	agentes.Obtener(a).Qsanciones = dat.Qsanciones+1;
	//Agente gadorcha=dat.grupoSanciones.Siguiente();
	dat.verK.Siguiente().grupoK.Eliminar(a);
	dat.verK.Avanzar();
	hayNuevas=true;
	if(dat.verK.HaySiguiente()){
		if(dat.verK.Siguiente().k == dat.Qsanciones+1){
			dat.grupoSanciones = dat.verK.Siguiente().grupoK.Agregar(a);
			dat.verK.Avanzar();
		}else{
			Conj<Agente> nuevo2;
			Conj<Agente>::Iterador iterConj = nuevo2.Agregar(a);
			datosK nuevo(dat.Qsanciones+1,nuevo2);
			dat.verK.AgregarComoSiguiente(nuevo);
			dat.grupoSanciones = iterConj; 
			dat.verK.Avanzar();
		}	
	}else{
		//dat.verK.AgregarComoSiguiente(nuevo);
		Conj<Agente> nuevo20;
		Conj<Agente>::Iterador iterConjj = nuevo20.Agregar(a);
		datosK nuevoo(dat.Qsanciones+1,nuevo20);
		dat.verK.AgregarComoSiguiente(nuevoo);
		dat.grupoSanciones = iterConjj;
		//dat.verK.Avanzar();
	}
}
 

bool Rastrillaje::ocupadaD(Posicion p, Direccion dir){
	if (dir==arriba){
		return quienOcupa[p.y-1 -1][p.x-1].ocupada;
	}else{
		if(dir==abajo){
			return quienOcupa[p.y+1 -1][p.x-1].ocupada;
		}else{
			if(dir==izq){
				return quienOcupa[p.y -1][p.x-1 -1].ocupada;
			}else{
				return quienOcupa[p.y -1][p.x+1 -1].ocupada;
			}
		}
	}
}





bool Rastrillaje::seFue(Posicion p, Posicion destino){
	return ((p.y==campo.Filas() && destino.y==campo.Filas()+1) || (p.y==1 && destino.y==0));
}







//INGESARES Y MOvERES
void Rastrillaje::IngresarEstudiante(Nombre n, Posicion p){
	if (esHippizable(p)){
		if (esCapturable(p)){
			Conj<Posicion> v = campo.Vecinos(p);
			Conj<Posicion>::Iterador it = v.CrearIt();
			while (it.HaySiguiente()){
				if ((quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1]).queHay == agente) {
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
			quienOcupa[p.y -1][p.x -1] = dP;
			Conj<Posicion> pS = campo.Vecinos(p);
			Conj<Posicion>::Iterador it = pS.CrearIt();
			while (it.HaySiguiente()){

				// DE ACA 
				if (esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				// A ACA

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
		quienOcupa[p.y -1][p.x -1] = dP;
		Conj<Posicion> pS = campo.Vecinos(p);
		Conj<Posicion>::Iterador it = pS.CrearIt();
		if (esCapturable(p)) {
					Conj<Posicion> vecinosDeP =campo.Vecinos(p);
					Conj<Posicion>::Iterador itAg2 = vecinosDeP.CrearIt();
					while (itAg2.HaySiguiente()){
						if (esAgente(itAg2.Siguiente())){
							Sancionar(itAg2.Siguiente());
						}
						itAg2.Avanzar();
					}
		}
		while (it.HaySiguiente()){
			if (esHippie(it.Siguiente()) && esEstudiantizable(it.Siguiente())){
				estudiantizar(it.Siguiente());
			} else {
				if (esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())) {
					Conj<Posicion> auxx=campo.Vecinos(it.Siguiente());
					Conj<Posicion>::Iterador itAg = auxx.CrearIt();
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
	ITHASH itA;
	if(esEstudiantizable(p)){
		Conj<datosHoE>::Iterador itN=estudiantes.AgregarRapido(datazo);
		datosPos datee(true,estudiante,itA,itN);
		quienOcupa[p.y -1][p.x -1]=datee;
	}else{
		Conj<datosHoE>::Iterador itN=hippies.AgregarRapido(datazo);
		datosPos dat(true,hippie,itA,itN);
		quienOcupa[p.y -1][p.x -1]=dat;
	}
	Conj<Posicion> vecinetes=campo.Vecinos(p);
	Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();

	if(esCapturable(p)){
		capturarHippie(p);
	}else{
		while(it.HaySiguiente()){
			if((quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==obstaculo) || quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==nada){
			}else{
				if(esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				}else{
					if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){
						Conj<Posicion> vecinetes=campo.Vecinos(it.Siguiente());
						Conj<Posicion>::const_Iterador itAg=vecinetes.CrearIt();
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
		ITHASH itA=quienOcupa[actual.y -1][actual.x -1].hayCana;
		ITHASH itAN;
		Conj<datosHoE>::Iterador itN;
		datosPos dat(false,nada,itAN,itN);
		quienOcupa[actual.y -1][actual.x -1]=dat;
		datosPos dat2(true,agente,itA,itN);
		quienOcupa[prx.y-1][prx.x-1]=dat2;
		Conj<Posicion> vecinetes=campo.Vecinos(prx);
		Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();// itero sobre los nuevos vecinos del agente
		while(it.HaySiguiente()){
			if((quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==obstaculo) || quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==nada){//Vacia u obstaculo -> nada

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
		Conj<datosHoE>::Iterador itR=quienOcupa[actual.y -1][actual.x -1].hayHoE;
		Conj<datosHoE>::Iterador itNA;
		ITHASH itA;
		datosPos dat1(true,hippie,itA,itR);
		datosPos dat2(false,nada,itA,itNA);
		quienOcupa[prx.y-1][prx.x-1]=dat1;
		quienOcupa[actual.y -1][actual.x -1]=dat2;
		Conj<Posicion> vecinetes=campo.Vecinos(prx);
		Conj<Posicion>::const_Iterador it=vecinetes.CrearIt();
		while(it.HaySiguiente()){
			if((quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==obstaculo) || quienOcupa[it.Siguiente().y -1][it.Siguiente().x -1].queHay==nada){

			}else{
				if(esEstudiante(it.Siguiente()) && esHippizable(it.Siguiente())){
					hippizar(it.Siguiente());
					if(esCapturable(it.Siguiente())){
						capturarHippie(it.Siguiente());
					}
				}else{
					if(esEstudiante(it.Siguiente()) && esCapturable(it.Siguiente())){
						Conj<Posicion> agAux=campo.Vecinos(it.Siguiente());
						Conj<Posicion>::Iterador itAg=agAux.CrearIt();
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
	Conj<datosHoE>::Iterador iterAHOI = quienOcupa[actual.y -1][actual.x -1].hayHoE;

	if (seFue(actual, prx)) {
		posCiviles.borrar(s);
        iterAHOI.EliminarSiguiente();
//iterAHOI.EliminarSiguiente(); POR ALGUNA RAZON NO ANDA
		datosPos dP(false,nada,itA,itC);
		quienOcupa[actual.y -1][actual.x -1] = dP;
	} else {
		Conj<datosHoE>::Iterador iterAHOI = quienOcupa[actual.y -1][actual.x -1].hayHoE;
		/*iterAHOI.Siguiente().posActual.EliminarSiguiente(); 
		iterAHOI.Siguiente().posActual = posRapida.definirRapido(s,prx);*/
		posCiviles.definir(s,prx);
		posRapida.Definir(s,prx);
		datosPos dP(true,estudiante,itA,iterAHOI);
		datosPos dataP(false,nada,itA,itC);
		quienOcupa[prx.y -1][prx.x -1] = dP;
		quienOcupa[actual.y -1][actual.x -1] = dataP;
		posCiviles.definir(s,prx);
		Conj<Posicion> vc = campo.Vecinos(prx);
		Conj<Posicion>::Iterador itPos = vc.CrearIt();
		if (esHippizable(prx)){
			hippizar(prx);
			while (itPos.HaySiguiente()){
				if ((quienOcupa[itPos.Siguiente().y -1][itPos.Siguiente().x -1].queHay==obstaculo) || quienOcupa[itPos.Siguiente().y -1][itPos.Siguiente().x -1].queHay==nada){

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
				if ((quienOcupa[itPos.Siguiente().y -1][itPos.Siguiente().x -1].queHay==obstaculo) || quienOcupa[itPos.Siguiente().y -1][itPos.Siguiente().x -1].queHay==nada){
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
						if (esHippie(itPos.Siguiente()) && esEstudiantizable(itPos.Siguiente())){
								estudiantizar(itPos.Siguiente());
							}
					}
				}
				itPos.Avanzar();
			}
		}
	}
}






// OPERADOR << Y MOSTRAR

ostream& operator<<(ostream& out, const Rastrillaje& a) {
	return a.mostrarRast(out);
}

ostream& Rastrillaje::mostrarRast(std::ostream& os ) const {
	int i=1;
	while(i<=campo.Filas()){
		int j=1;
		while(j<=campo.Columnas()){
			if(quienOcupa[i-1][j-1].ocupada){
				if(quienOcupa[i-1][j-1].queHay==obstaculo){
					os<<"X ";
				}else  if(quienOcupa[i-1][j-1].queHay==agente){
					os<<"A ";
				}else if(quienOcupa[i-1][j-1].queHay==estudiante){
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


// PUBLICAS PARA TESTEAR

bool Rastrillaje::dimeQueHay(Posicion p){
	return quienOcupa[p.y -1][p.x -1].ocupada;
}

bool Rastrillaje::dimeSiEsEstudiante(Posicion p){
	return esEstudiante(p);
}

bool Rastrillaje::dimeSiEsCapturable(Posicion p){
	return esCapturable(p);
}

bool Rastrillaje::dimeSiEsHippizable(Posicion p){
	return esHippizable(p);
}

Nat Rastrillaje::dimeCantidadHippies(){
	return hippies.Cardinal();
}

Agente Rastrillaje::dimeQueAgenteEs(Posicion p){
		return quienOcupa[p.y -1][p.x -1].hayCana.Siguiente().significado.wachem;

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
			if(campo.distancia(p,dondeHippie)<campo.distancia(p,minimo) && !quienOcupa[dondeHippie.y -1][dondeHippie.x -1].ocupada){
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
			if(campo.distancia(p,dondeHippie)<campo.distancia(p,minimo) && !quienOcupa[dondeHippie.y -1][dondeHippie.x -1].ocupada){
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
			return Posicion(p.x,p.y-1);
		}else{
			return Posicion(p.x,p.y+1);
		}
	}

}

Direccion Rastrillaje::queCaminoTomar(Posicion d, Posicion h){
	if(d.y>h.y && !ocupadaD(d,arriba)){
		return arriba;
	}else if(d.y<h.y && !ocupadaD(d,abajo)){
		return abajo;
	}else if(d.x<h.x && !ocupadaD(d,der)){
		return der;
	}else{
		return izq;
	}
}


//Giladas Driver

Nombre Rastrillaje::iesimoEstudiante(Nat i) const{
	Conj<datosHoE>::const_Iterador it = estudiantes.CrearIt();
	Nat j=0;
	while(j < i){
		it.Avanzar();
		j++;
	}
	return it.Siguiente().ID;
}

Nombre Rastrillaje::iesimoHippie(Nat i) const {
    // TODO
	Conj<datosHoE>::const_Iterador it = hippies.CrearIt();
	Nat j=0;
	while(j < i){
		it.Avanzar();
		j++;
	}
	return it.Siguiente().ID;
}


//otros

bool Rastrillaje::dimeSiOcupada(Posicion p) const{
	return quienOcupa[p.y -1][p.x -1].ocupada;
}

Nat Rastrillaje::cantEstudiantes() const{
	return estudiantes.Cardinal();
}

Nat Rastrillaje::cantHippies() const{
	return hippies.Cardinal();
}

Nat Rastrillaje::cantAgentes() const{
	return agentes.ClavesPublic().Cardinal();
}