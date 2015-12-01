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
	bool esEstudiante(Posicion);
	bool esHippie(Posicion);
	bool esAgente(Posicion);
	void estudiantizar(Posicion);
	bool esCapturable(Posicion);
	bool esHippizable(Posicion);
	bool esEstudiantizable(Posicion);
	bool todasOcupadas(Posicion);
	void Recompensar(Posicion);
	void Sancionar(Posicion);
	bool ocupadaD(Posicion, Direccion);
	Direccion vecinoMasCercano(Posicion,Posicion);
	bool seFue(Posicion,Posicion);
	Direccion proxPosicionH(Nombre);
	Direccion proxPosicionA(Agente);




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



/*
				TO DO LIST

	VER QUE ONDA ESTUDIANTIZAR Y HIPPIZAR

	AUXILIARES: 
				CAPTURAR HIPPIE(Quilombo de tipos)
				RECOMPENSAR(Otro quilombo de tipos)
				SANCIONAR(Otro problema de tipos)

	POSTAS:(Primero las auxiliares)
			MOVER:
				  HIPPIE
				  ESTUDIANTE
				  AGENTE
			INGRESAR:
					 HIPPIE
					 ESTUDIANTE	

			ConKSanciones?



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

void Rastrillaje::estudiantizar(Posicion p){
	/*
	
	quienOcupa x y me devuelve algo de tipo datosPos, si yo le pido hayHoE tengo un iterador a conj(Nombre), siguiente() de eso ya me da un Nombre, no puedo pedirle ID como dice el tp.
	Ademas el datosHoE que quiero crear tiene un iterador a Dicc(Nombre,Pos), como lo creo si lo que me da quienOcupa es iterador a conj(Nombre) ????
	(El tp flashea)

	Nombre n1=quienOcupa[p.x][p.y].hayHoE.Siguiente();
	Posicion p1=quienOcupa[p.x][p.y].hayHoE;
	datosHoE dat(n1,p1);

	eliminarSiguiente(quienOcupa[p.x][p.y].hayHoE);
	typename Conj<Nombre>::const_Iterador it= estudiantes.AgregarRapido(dat);
*/

}	



bool Rastrillaje::esCapturable(Posicion p){
	typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
	Nat contador=0;
	bool hayGuardia=false;
	while(it.HaySiguiente()){
		if(quienOcupa[p.x][p.y].ocupada){
			contador++;
		}
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].queHay==agente){
			hayGuardia=true;
		}
		it.Avanzar();
	}
	return contador==4 && hayGuardia;

}

bool Rastrillaje::esHippizable(Posicion p){
	typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
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
/*
void Rastrillaje::capturarHippie(Posicion p){
	Nombre n=quienOcupa[p.x][p.y].hayHoE.Siguiente();

}

Mismo quilombo que estudiantizar


*/
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
	Agente a=quienOcupa[p.x][p.y].hayCana.SiguienteClave();
	datosAg dat=agentes.Obtener(a);
	dat.premios++;
	if(dat.premios>agentes.Obtener(masVigilante.Siguiente()).premios){
		//masVigilante=quienOcupa[p.x][p.y].hayCana; hayCana da iterador a dicc, masVigilante es it a conj, dice que no hay operador = que tome esos parametros
	}else{
		if(dat.premios==agentes.Obtener(masVigilante.Siguiente()).premios){
			if(a<masVigilante.Siguiente()){
				//masVigilante=quienOcupa[p.x][p.y].hayCana; hayCana da iterador a dicc, masVigilante es it a conj, dice que no hay operador = que tome esos parametros
			}
		}
	}
}

void Rastrillaje::Sancionar(Posicion p){
	Agente a=quienOcupa[p.x][p.y].hayCana.SiguienteClave();
	datosAg dat=agentes.Obtener(a);
	dat.Qsanciones++;
	dat.grupoSanciones.EliminarSiguiente();
	dat.verK.Avanzar();
	hayNuevas=true;
	if(dat.verK.Siguiente().k==dat.Qsanciones){
		dat.grupoSanciones=dat.verK.Siguiente().grupoK.Agregar(a);
	}else{
		Conj<Agente> nuevo2;
		nuevo2.Agregar(a);
		datosK nuevo(dat.Qsanciones,nuevo2);
		//dat.grupoSanciones=dat.verK.AgregarComoAnterior(nuevo); Problema de tipos, estoy asignandole a un it de conj un it de lista
	}

}


bool Rastrillaje::ocupadaD(Posicion p, Direccion dir){
	if (dir==arriba){
		return quienOcupa[p.x][p.y +1].ocupada;
	}else{
		if(dir==abajo){
			return quienOcupa[p.x][p.y -1].ocupada;
		}else{
			if(dir==izq){
				return quienOcupa[p.x -1][p.y].ocupada;
			}else{
				return quienOcupa[p.x +1][p.y].ocupada;
			}
		}
	}
}

Direccion Rastrillaje::vecinoMasCercano(Posicion p, Posicion p2){
	typename Conj<Posicion>::const_Iterador it=campo.Vecinos(p).CrearIt();
	Posicion destino=it.Siguiente();
	while(it.HaySiguiente()){
		if(quienOcupa[it.Siguiente().x][it.Siguiente().y].ocupada){
			if(campo.distancia(p,it.Siguiente())<campo.distancia(p,destino)){
				destino=it.Siguiente();
			}
		}
		it.Avanzar();
	}
	if(destino.x!=p.x){
		if(destino.y>p.y){
			return arriba;
		}else{
			return abajo;
		}
		if(destino.x>p.x){
			return der;
		}else{
			return izq;
		}
	}

}

Nat busquedaBin(Vector<datosK> v, 	Nat objetivo){
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
}

bool Rastrillaje::seFue(Posicion p, Posicion destino){
	return ((p.y==campo.Filas() && destino.y==campo.Filas()+1) || (p.y==0 && destino.y==-1));
}


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
