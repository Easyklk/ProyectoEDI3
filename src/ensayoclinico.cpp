/*
 * ensayoclinico.cpp
 *
 *  Created on: 28 abr 2023
 *      Author: Isaac Romanillos
 */
#include "ensayoclinico.h"
#include "Paciente.h"
#include <iostream>
#include <fstream>

EnsayoClinico::EnsayoClinico() {
	this->nombre = "Isaac Romanillos Deza";
	this->arbolPacientes = new BSTree<KeyValue<string, Paciente*>>();
	this->listaDNIPacientes = new ListaDPI<string>();
	this->lPacientes = new ListaDPI<Paciente*>();
	Paciente *vP[199];
	this->cargarPacientesAVector(vP);
	this->crearArbolPacientes(vP, 0, 199);
//	this->mostrarEnOrden(this->arbolPacientes);
}

void EnsayoClinico::mostrarEnOrden(
		BSTree<KeyValue<string, Paciente*> > *arbol) {
	if (!arbol->estaVacio()) {
		if (arbol->getIzq() != nullptr)
			mostrarEnOrden(arbol->getIzq());

		arbol->getDato().getValue()->mostrar();
		cout << "\n";

		if (arbol->getDer() != nullptr)
			mostrarEnOrden(arbol->getDer());
	}
}

int EnsayoClinico::calcularProfundidad(
		BSTree<KeyValue<string, Paciente*> > *arbol) {
	int prof = 0;
	int prof_izq = 0;
	int prof_der = 0;
	if (!arbol->estaVacio()) {
		if (arbol->getIzq() != nullptr)
			prof_izq = calcularProfundidad(arbol->getIzq());
		if (arbol->getDer() != nullptr)
			prof_der = calcularProfundidad(arbol->getDer());
		prof = max(prof_izq, prof_der) + 1;
	}
	return prof;
}

void EnsayoClinico::cargarPacientesAVector(Paciente *vP[]) {
	ifstream ifs;
	int i = 0;
	ifs.open("pacientes_ordenados.csv");
	if (ifs.fail()) {
		cerr << "ERROR: fichero no encontrado." << endl;
	} else {
		while (!ifs.eof()) {
			string DNI;
			getline(ifs, DNI, ';');
			if (!ifs.eof()) {
				string nombre;
				getline(ifs, nombre, ';');
				string apellidos;
				getline(ifs, apellidos, ';');
				string genero;
				getline(ifs, genero, ';');
				string edad;
				getline(ifs, edad, '\n');
				vP[i] = new Paciente(nombre, apellidos, DNI,
						Genero(stoi(genero)), stoi(edad));
				i++;
			}
		}
		ifs.close();
	}
}

void EnsayoClinico::crearArbolPacientes(Paciente *vP[], int ini, int fin) {

	int medio;
	if (ini != fin) {
		medio = ((fin + ini) / 2);
		KeyValue<string, Paciente*> kv(vP[medio]->getDNI(), vP[medio]);
		this->arbolPacientes->insertar(kv);
		crearArbolPacientes(vP, ini, medio);
		crearArbolPacientes(vP, medio + 1, fin);
	}
}

string EnsayoClinico::getNombre() {
	return this->nombre;
}

void EnsayoClinico::anotar() {
	ifstream ifs;
	Paciente *p;
	ifs.open("ensayo.csv");
	if (ifs.fail()) {
		cerr << "ERROR: fichero no encontrado." << endl;
	} else {
		while (!ifs.eof()) {
			string DNI;
			getline(ifs, DNI, ';');
			if (!ifs.eof()) {
				string puntuacion;
				getline(ifs, puntuacion, '\n');
				if (this->arbolPacientes->existe(DNI)) {
					p = buscarPaciente(DNI);
					p->setPuntuacion(p->getPuntuacion() + stoi(puntuacion));
				} else {
					if (!this->buscarPacienteLista(DNI)) {
						this->listaDNIPacientes->insertar(DNI);
					}
				}
			}
		}
	}
	ifs.close();
}

int EnsayoClinico::numNiveles() {
	return this->calcularProfundidad(this->arbolPacientes);
}

void EnsayoClinico::mostrarErrores() {
	this->listaDNIPacientes->moverPrimero();
	if (!this->listaDNIPacientes->estaVacia()) {
		while (!this->listaDNIPacientes->alFinal()) {
			cout << this->listaDNIPacientes->consultar() << endl;
			this->listaDNIPacientes->avanzar();
		}
	}
}

void EnsayoClinico::insertarMayores() {
	this->insertarMayoresR(this->arbolPacientes);
}

void EnsayoClinico::insertarMayoresR(
		BSTree<KeyValue<string, Paciente*> > *arbol) {
	if (!arbol->estaVacio()) {
		if (arbol->getIzq() != nullptr)
			insertarMayoresR(arbol->getIzq());

		this->insertarOrdenadosLPacientes(arbol->getDato().getValue());

		if (arbol->getDer() != nullptr)
			insertarMayoresR(arbol->getDer());
	}
}

void EnsayoClinico::insertarOrdenadosLPacientes(Paciente *p) {
	bool enc = false;
	this->lPacientes->moverPrimero();
	while (!this->lPacientes->alFinal() && !enc) {
		if (this->lPacientes->consultar()->getPuntuacion() < p->getPuntuacion())
			enc = true;
		else
			this->lPacientes->avanzar();
	}
	this->lPacientes->insertar(p);
}

void EnsayoClinico::mostrarMayores(int cuantos) {
	this->insertarMayores();
	this->lPacientes->moverPrimero();
	int i = 1;
	if (!this->lPacientes->estaVacia()) {
		while (!this->lPacientes->alFinal() && i <= cuantos) {
			this->lPacientes->consultar()->mostrar();
			cout << endl;
			this->lPacientes->avanzar();
			i++;
		}
	}
}

void EnsayoClinico::mostrarPorApellidos(
		BSTree<KeyValue<string, Paciente*> > *arbol, string s_apellido) {
	string apellido;
	KeyValue<string, Paciente*> kv;
	Paciente *p = nullptr;
	if (!arbol->estaVacio()) {
		if (arbol->getIzq() != nullptr)
			mostrarPorApellidos(arbol->getIzq(), s_apellido);

		kv = arbol->getDato();
		p = kv.getValue();
		if (p->getApellidos().find(s_apellido) != std::string::npos) {
			p->mostrar();
			cout << endl;
		}
		if (arbol->getDer() != nullptr)
			mostrarPorApellidos(arbol->getDer(), s_apellido);
	}
}

void EnsayoClinico::mostrarPorApellido(string s_apellido) {
	this->mostrarPorApellidos(arbolPacientes, s_apellido);
}

void EnsayoClinico::buscarSubArbolDni(
		BSTree<KeyValue<string, Paciente*> > *arbol, string s_dni,
		BSTree<KeyValue<string, Paciente*> > *&subArbol) {
	string DNI;
	KeyValue<string, Paciente*> kv;
	kv = arbol->getDato();
	DNI = kv.getKey();
	if (arbol->existe(DNI)) {
		if (kv.getKey().find(DNI) == 0) {
			subArbol = arbol;
		} else {
			if (arbol->getIzq() != nullptr)
				buscarSubArbolDni(arbol->getIzq(), s_dni, subArbol);

			else if (arbol->getDer() != nullptr)
				buscarSubArbolDni(arbol->getDer(), s_dni, subArbol);

		}
	}
}

void EnsayoClinico::mostrarPorDni(BSTree<KeyValue<string, Paciente*> > *arbol,
		string s_dni) {
	BSTree<KeyValue<string, Paciente*> > *subArbol = new BSTree<
			KeyValue<string, Paciente*> >();
	buscarSubArbolDni(arbol, s_dni, subArbol);
	KeyValue<string, Paciente*> kv;
	Paciente *p = nullptr;
	if (!subArbol->estaVacio()) {
		if (subArbol->getIzq() != nullptr)
			mostrarPorDni(subArbol->getIzq(), s_dni);

		kv = subArbol->getDato();
		if (kv.getKey().find(s_dni) == 0) {
			p = kv.getValue();
			p->mostrar();
			cout << endl;
		}

		if (subArbol->getDer() != nullptr)
			mostrarPorDni(arbol->getDer(), s_dni);
	}
}

void EnsayoClinico::mostrarPorDNI(string s_dni) {
	mostrarPorDni(this->arbolPacientes, s_dni);
}

Paciente* EnsayoClinico::buscarPacienteR(string DNI,
		BSTree<KeyValue<string, Paciente*> > *arbol) {
	KeyValue<string, Paciente*> kv;
	Paciente *p = nullptr;
	if (!arbol->estaVacio()) {
		kv = arbol->getDato();
		if (kv.getKey() == DNI) {
			p = kv.getValue();
		} else {
			if (DNI < kv.getKey()) {
				if (arbol->getDato().getValue() != nullptr)
					p = buscarPacienteR(DNI, arbol->getIzq());
			} else {
				if (arbol->getDato().getValue() != nullptr)
					p = buscarPacienteR(DNI, arbol->getDer());
			}
		}
	}
	return p;
}

Paciente* EnsayoClinico::buscarPaciente(string DNI) {
	Paciente *p = nullptr;
	p = buscarPacienteR(DNI, this->arbolPacientes);
	return p;
}

bool EnsayoClinico::buscarPacienteLista(string DNI, ListaDPI<string> *lista) {
	bool enc = false;
	if (!lista->estaVacia()) {
		while (!lista->alFinal() && !enc) {
			if (lista->consultar() == DNI)
				enc = true;
			else
				lista->avanzar();
		}
	}
	return enc;
}

bool EnsayoClinico::buscarPacienteLista(string DNI) {
	bool enc = false;
	if (!this->listaDNIPacientes->estaVacia()) {
		this->listaDNIPacientes->moverPrimero();
		enc = this->buscarPacienteLista(DNI, this->listaDNIPacientes);
	}
	return enc;
}

EnsayoClinico::~EnsayoClinico() {
	KeyValue<string, Paciente*> kv;
	Paciente *p;
	while (!this->arbolPacientes->estaVacio()) {
		kv = this->arbolPacientes->getDato();
		p = kv.getValue();
		this->arbolPacientes->eliminar(kv);
		delete p;
	}
	delete this->arbolPacientes;

//	this->lPacientes->moverPrimero();
//	while (!this->lPacientes->estaVacia()) {
//		this->lPacientes->consultar()->mostrar();
//		this->lPacientes->eliminar();
//	}

	delete this->lPacientes;

	delete this->listaDNIPacientes;

}
