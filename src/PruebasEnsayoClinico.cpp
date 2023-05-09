/*
 * PruebasEnsayoClinico.cpp
 *
 *  Created on: 4 may 2023
 *      Author: Isaac Romanillos
 */

#include "PruebasEnsayoClinico.h"
#include "ensayoclinico.h"

void probarConstructorEnsayoClinico() {
	cout << "Inicio probarConstructorEnsayoClinico" << endl;
	EnsayoClinico *ec = new EnsayoClinico();
	if (ec->numNiveles() != 8)
		cerr << "Error en el constructor por defecto" << endl;

	if (ec->getNombre() != "Isaac Romanillos Deza")
		cerr << "Error getNombre" << endl;

	delete ec;
	cout << "Fin probarConstructorEnsayoClinico" << endl;
}

void probarAnotar() {
	cout << "Inicio probarAnotar" << endl;
	EnsayoClinico *ec = new EnsayoClinico();
	ec->anotar();

	if (ec->numNiveles() != 8 || !ec->buscarPacienteLista("99217882B")
			|| ec->buscarPaciente("07464970V") == nullptr) {
		cerr << "Error en el metodo anotar" << endl;
	}

	delete ec;
	cout << "Fin probarAnotar" << endl;
}

void probarNumNiveles() {
	cout << "Inicio probarNumNiveles" << endl;
	EnsayoClinico *ec = new EnsayoClinico();

	if (ec->numNiveles() != 8) {
		cerr << "Error en el metodo NumNiveles" << endl;
	}

	delete ec;
	cout << "Fin probarNumNiveles" << endl;
}

void probarInsertarMayores() {
	cout << "Inicio probarInsertarMayores" << endl;
	EnsayoClinico *ec = new EnsayoClinico();

	ec->anotar();
	ec->mostrarMayores(0);

	if (ec->numNiveles() != 8 || ec->buscarPaciente("07464970V") == nullptr) {
		cerr << "Error en el metodo InsertarMayores" << endl;
	}

	delete ec;
	cout << "Fin probarInsertarMayores" << endl;
}

void probarBuscarPaciente() {
	cout << "Inicio probarBuscarPaciente" << endl;
	EnsayoClinico *ec = new EnsayoClinico();

	if (ec->buscarPaciente("07464970V") == nullptr)
		cerr << "Error en el metodo BuscarPaciente" << endl;

	delete ec;
	cout << "Fin probarBuscarPaciente" << endl;
}

void probarBuscarPacienteLista() {
	cout << "Inicio probarBuscarPacienteLista" << endl;
	EnsayoClinico *ec = new EnsayoClinico();
	ec->anotar();

	if (!ec->buscarPacienteLista("99217882B"))
		cerr << "Error en el metodo BuscarPacienteLista" << endl;

	delete ec;
	cout << "Fin probarBuscarPacienteLista" << endl;
}

void pruebasEnsayoClinico() {
	cout << "------------------------------------------------------" << endl;
	cout << "Inicio de las pruebas de la clase EnsayoClinico" << endl;
	cout << "------------------------------------------------------" << endl;
	probarConstructorEnsayoClinico();
	probarAnotar();
	probarAnotar();
	probarNumNiveles();
	probarInsertarMayores();
	probarBuscarPaciente();
	probarBuscarPacienteLista();
	cout << "------------------------------------------------------" << endl;
	cout << "Fin de las pruebas de la clase EnsayoClinico" << endl;
	cout << "------------------------------------------------------" << endl;
}
