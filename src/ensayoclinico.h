/*
 * ensayoclinico.h
 *
 *  Autor: Juan A. Rico (jarico@unex.es)
 *  Fecha: 15 abril 2023
 */

#ifndef ENSAYO_CLINICO_H_
#define ENSAYO_CLINICO_H_

#include <iostream>
#include <string>

#include "Paciente.h"
#include "BSTree.h"
#include "KeyValue.h"
// Si necesitas alguna ED o clase adicional, puedes incluirla aqui
#include "ListaDPI.h"

using namespace std;

class EnsayoClinico {

private:
	string nombre; // Inicializa con tu NOMBRE Y APELLIDOS en el constructor

	BSTree<KeyValue<string, Paciente*>> *arbolPacientes;
	ListaDPI<string> *listaDNIPacientes;
	ListaDPI<Paciente*> *lPacientes;

	// PRE: ---
	// DES: carga los paciente desde un fichero al vector "vP"
	// COM: O(n)
	void cargarPacientesAVector(Paciente *vP[]);

	// PRE: ---
	// DES: crea un arbol binario con los pacientes de "vP"
	// COM: O(log n)
	void crearArbolPacientes(Paciente *vP[], int ini, int fin);

	// PRE: ---
	// DES: muestra por consola los datos del "arbol"
	// COM: O(n)
	void mostrarEnOrden(BSTree<KeyValue<string, Paciente*> > *arbol);

	// PRE: ---
	// DES: devuelve la profundidad del "arbol"
	// COM: O(n)
	int calcularProfundidad(BSTree<KeyValue<string, Paciente*> > *arbol);

	// PRE: ---
	// DES: devuelve el subarbol con los DNIs que empiezan por "s_dni"
	// COM: O(n)
	void buscarSubArbolDni(BSTree<KeyValue<string, Paciente*>> *arbol,
			string s_dni, BSTree<KeyValue<string, Paciente*>> *&subArbol);

	// PRE: ---
	// DES: Muestra pacientes cuyo DNI empieza por subcadena "s_dni"
	// COM: O(n)
	void mostrarPorDni(BSTree<KeyValue<string, Paciente*>> *arbol,
			string s_dni);

	// PRE: ---
	// DES: Muestra pacientes cuyo apellido contiene subcadena "s_apellido"
	// COM: O(n)
	void mostrarPorApellidos(BSTree<KeyValue<string, Paciente*>> *arbol,
			string s_apellido);
	Paciente* buscarPacienteR(string DNI,
			BSTree<KeyValue<string, Paciente*>> *arbol);

	// PRE: ---
	// DES: retorna el paciente asociado a ese DNI
	// COM: O(n)
	bool buscarPacienteLista(string DNI, ListaDPI<string> *lista);

	// PRE: lPacientes inicializados correctamente
	// DES: inserta en lPacientes los pacientes ordenados por la puntuacion
	// COM: O(n)
	void insertarMayoresR(BSTree<KeyValue<string, Paciente*>> *arbol);

	// PRE: lPacientes y arbolPacientes inicializados correctamente
	// DES: inserta en lPacientes los pacientes ordenados por la puntuacion
	// COM: O(n)
	void insertarOrdenadosLPacientes(Paciente *p);

public:

	// PRE: ---
	// DES: Constructor por defecto
	// COM: O(n)
	EnsayoClinico();

	// PRE: ---
	// DES: devuelve this->nombre
	// COM: O(1)
	string getNombre();

	// PRE: ---
	// DES: carga la puntuacion de cada paciente desde un fichero arbolPacientes
	//      o los agrega a listaDNIPacientes si estos no existen en el arbol
	// COM: O(n)
	void anotar();

	// PRE: ---
	// DES: muestra por consola el numero de niveles del arbol
	// COM: O(n)
	int numNiveles();

	// PRE: ---
	// DES: muestra todos los errores al anotar la puntuación del ensayo
	// COM: O(n)
	void mostrarErrores();

	// PRE: ---
	// DES: Muestra "cuantos" pacientes con mayor puntuacion
	// COM: O(n)
	void mostrarMayores(int cuantos);

	// PRE: ---
	// DES: inserta en lPacientes los pacientes ordenados por la puntuacion
	// COM: O(n)
	void insertarMayores();

	// PRE: ---
	// DES: Muestra pacientes cuyo apellido contiene subcadena "s_apellido"
	// COM: O(n)
	void mostrarPorApellido(string s_apellido);

	// PRE: ---
	// DES: Muestra pacientes cuyo DNI empieza por subcadena "s_dni"
	// COM: O(n)
	void mostrarPorDNI(string s_dni);

	// PRE: arbolPacientes inicializados correctamente
	// DES: retorna el paciente asociado a ese DNI
	// COM: O(n)
	Paciente* buscarPaciente(string DNI);

	// PRE: listaDNIPacientes y arbolPacientes inicializados correctamente
	// DES: devuelve true/false si existe o no un paciente en listaDNIPacientes
	// COM: O(n)
	bool buscarPacienteLista(string DNI);

	// PRE: ---
	// DES: Destructor
	// COM: O(n)
	~EnsayoClinico();
};

#endif /* ENSAYO_CLINICO_H_ */
