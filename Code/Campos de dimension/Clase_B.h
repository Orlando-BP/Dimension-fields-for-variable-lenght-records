#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Clase_B
{
public:
	string Cadena;
	bool Booleano;

	Clase_B();
	void Modificar();
	bool Validador();
	void Guardar(ofstream &Archivo);
	void Leer(ifstream &Archivo);
};

