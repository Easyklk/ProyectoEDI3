/*
 * Paciente.cpp
 *
 *  Created on: 6 feb 2023
 *      Author: Isaac Romanillos
 */

#include "Paciente.h"
#include <iostream>

Paciente::Paciente() {
	this->nombre = "";
	this->apellidos = "";
	this->DNI = "";
	this->genero = Indefinido;
	this->edad = 0;
	this->puntuacion = 0;
}
Paciente::Paciente(string DNI, int puntuacion) {
	this->nombre = "";
	this->apellidos = "";
	this->DNI = DNI;
	this->genero = Indefinido;
	this->edad = 0;
	this->puntuacion = puntuacion;
}
Paciente::Paciente(string nombre, string apellidos, string DNI, Genero genero,
		int edad) {
	this->nombre = nombre;
	this->apellidos = apellidos;
	this->DNI = DNI;
	this->genero = genero;
	this->edad = edad;
	this->puntuacion = 0;
}

Paciente::Paciente(const Paciente &orig) {
	this->nombre = orig.nombre;
	this->apellidos = orig.apellidos;
	this->DNI = orig.DNI;
	this->genero = orig.genero;
	this->edad = orig.edad;
	this->puntuacion = orig.puntuacion;
}

void Paciente::setNombre(string nombre) {
	this->nombre = nombre;
}

void Paciente::setApellidos(string apellidos) {
	this->apellidos = apellidos;
}

void Paciente::setDNI(string dni) {
	this->DNI = dni;
}

void Paciente::setGenero(Genero genero) {
	this->genero = genero;
}

string Paciente::getNombre() {
	return this->nombre;
}

string Paciente::getApellidos() {
	return this->apellidos;
}

string Paciente::getDNI() {
	return this->DNI;
}

int Paciente::getGenero() {
	return this->genero;
}
void Paciente::setEdad(int edad) {
	this->edad = edad;
}

int Paciente::getEdad() {
	return this->edad;
}

int Paciente::getPuntuacion() {
	return this->puntuacion;
}

void Paciente::setPuntuacion(int puntuacion) {
	this->puntuacion = puntuacion;
}

bool Paciente::operator <(const Paciente &paciente) {
	return (this->DNI < paciente.DNI);
}

bool Paciente::operator ==(const Paciente &paciente) {
	return (this->DNI == paciente.DNI);
}

bool Paciente::operator >(const Paciente &paciente) {
	return (this->DNI > paciente.DNI);
}

void Paciente::mostrar() {
	cout << "Paciente{ Nombre: " << nombre << ", Apellidos: " << apellidos
			<< ", DNI: " << DNI << ", Genero: " << genero << ", Puntuación: "
			<< puntuacion << " }";

}

string Paciente::toString() {
	string generoString = "";
	if (this->genero == 0) {
		generoString = "Masculino";
	} else if (this->genero == 1) {
		generoString = "Femenino";
	} else {
		generoString = "Indefinido";
	}
	return ("Paciente{ Nombre: " + this->nombre + ", Apellidos: "
			+ this->apellidos + ", DNI: " + to_string(edad) + ", Genero: "
			+ generoString) + ", Puntuación: " + to_string(puntuacion) + " }";
}

Paciente::~Paciente() {
}

