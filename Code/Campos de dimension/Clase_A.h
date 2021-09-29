#pragma once
#include <iostream>
#include <fstream>
#include "Clase_B.h"
#define ObjetosB 10
using namespace std;
class Clase_A
{
public:
	string Nombre;
	int Llave;
	Clase_B ObjB [ObjetosB];
	//Metodos Auxiliares independientes
	Clase_A();
	bool ValidarLlave(int Propuesta);
	void CrearObjeto();
	void llenarAuxiliar();
	void ReiniciarMemoria();
	int CargarRegistro(string Cadena,int Indice);
	void MenuModificar();
	void Menu();
	//Metodos de requeridos por la practica
	void InsertarFinal();
	void InsertarInicio();
	void MostrarRegistro();
	void MostrarTodos();
	bool Eliminar();
	bool Modificar();
	
};

