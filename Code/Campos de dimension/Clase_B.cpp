#include "Clase_B.h"

Clase_B::Clase_B()
{
	Cadena = "";
	Booleano = false;
}

void Clase_B::Modificar()
{
	cout << "Ingresa el nombre del objeto de clase B" << endl;
	cin >> Cadena;
	Booleano = true;
}

bool Clase_B::Validador()
{
	if (Booleano)
		return true;
	return false;
}

void Clase_B::Guardar(ofstream &Archivo)
{
	if (Booleano) {
		int Tamcadena = Cadena.length();
		Archivo << Tamcadena;
		Archivo << Cadena;
		Archivo << Booleano;
	}
}

void Clase_B::Leer(ifstream &Archivo)
{
}
