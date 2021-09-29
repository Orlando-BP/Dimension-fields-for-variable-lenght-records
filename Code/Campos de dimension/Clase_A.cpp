#include "Clase_A.h"

Clase_A::Clase_A()
{
	Nombre = "";
	Llave = -1;
}

bool Clase_A::ValidarLlave(int Propuesta)
{
	string Documento;
	ifstream Archivo("Auxiliar.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	int TamDocumento = Documento.length();
	int Indice = -1;
	while (Indice < TamDocumento - 1) {
		Indice = CargarRegistro(Documento, Indice);
		if (Llave == Propuesta) {
			return false;//No se puede usar llave propuesta
		}
	}
	return true;//se puede usar llave propuesta
}

void Clase_A::CrearObjeto()
{
	ReiniciarMemoria();
	llenarAuxiliar();
	int Objb,propuesta;
	bool Unica = false;
	while(Unica==false){
	cout << "Ingresa la llave del objeto de clase A (debe ser nueva)" << endl;
	cin >> propuesta;
	Unica = ValidarLlave(propuesta);
	}
	ReiniciarMemoria();
	cout << "Ingresa el nombre del objeto de clase A a crear" << endl;
	cin >> Nombre;
	Llave = propuesta;
	cout << "Cuantos objetos Clase B tendra? max 10" << endl;
	cin >> Objb;
	for (int i = 0; i < Objb; i++) {
		cout << "Objeto B numero: "<< i+1 << endl;
		ObjB[i].Modificar();
	}
}

void Clase_A::llenarAuxiliar()
{
	string Documento;
	ifstream Archivo("principal.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	ofstream ArchivoAUX("Auxiliar.bin", ios::binary);
	ArchivoAUX << Documento;
	ArchivoAUX.close();
}

void Clase_A::ReiniciarMemoria()
{
	Nombre = "";
	Llave = -1;
	Clase_B Nuevo;
	for (int i = 0; i < 10; i++) {
		ObjB[i] = Nuevo;
	}
}

int Clase_A::CargarRegistro(string Cadena, int Indice)
{
	ReiniciarMemoria();
	Indice++;
	Llave = Cadena[Indice] - 48;
	Indice++;
	int TamNombre = Cadena[Indice] - 48;
	Indice++;
	for (int i = 0; i < TamNombre; i++) {
		Nombre += ".";
	}
	for (int i = 0; i < TamNombre; i++) {
		Nombre[i] = Cadena[Indice];
		Indice++;
	}
	int NumeroB = Cadena[Indice] - 48;
	for (int i = 0; i < NumeroB; i++) {
		Indice++;
		TamNombre = Cadena[Indice] - 48;
		Indice++;
		for (int j = 0; j < TamNombre; j++) {
			ObjB[i].Cadena += ".";
		}
		for (int j = 0; j < TamNombre; j++) {
			ObjB[i].Cadena[j] = Cadena[Indice];
			Indice++;
		}
		ObjB[i].Booleano = true;
	}
	return Indice;
}

void Clase_A::MenuModificar()
{
	char opcion;
	bool salir = true;
	do {
		cout << "Se encontro el registro a Modificar" << endl;
		cout << "Que deseas modificar? " << endl;
		cout << "1.-Nombre" << endl;
		cout << "2.-Llave" << endl;
		cout << "Ingresa una opcion:" << endl;
		cin >> opcion;
		switch (opcion)
		{
		case '1': {
			salir = false;
			cout << "Ingresa el nuevo nombre" << endl;
			cin >> Nombre;
			break;
		}
		case '2': {
			salir = false;
			int propuesta;
			cout << "Ingresa la llave del objeto de clase A (debe ser nueva)" << endl;
			cin >> propuesta;
			Llave = propuesta;
			break;
		}
		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	} while (salir);

}

void Clase_A::Menu()
{
	bool continuar = true;
	char Opcion;
	do {
		cout << "Menu" << endl;
		cout << "1.-Agregar" << endl;
		cout << "2.-Eliminar" << endl;
		cout << "3.-Modificar" << endl;
		cout << "4.-Mostrar Registro" << endl;
		cout << "5.-Mostrar Registros" << endl;
		cout << "6.-Salir" << endl;
		cout << "Ingresa una Opcion: ";
		cin >> Opcion;
		switch (Opcion)
		{
		case '1': {
			system("CLS");
			cout << "Selecciona en que lugar del archivo quieres agregar un registro:" << endl;
			cout << "1.-Inicio" << endl;
			cout << "2.-Final" << endl;
			cout << "Ingresa una opcion: ";
			cin >> Opcion;
			switch (Opcion)
			{
			case '1': {
				system("CLS");
				InsertarInicio();
				break;
			}
			case '2': {
				system("CLS");
				InsertarFinal();
				break;
			}
			default:
				cout << "Opcion no valida, intenta de nuevo." << endl;
				break;
			}
			break;
		}
		case '2': {
			system("CLS");
			Eliminar();
			break;
		}
		case '3': {
			system("CLS");
			Modificar();
			break;
		}
		case '4': {
			system("CLS");
			MostrarRegistro();
			break;
		}
		case '5': {
			system("CLS");
			MostrarTodos();
			break;
		}
		case '6': {
			cout << "Nos vemos..." << endl;
			continuar = false;
			break;
		}
		default:
			cout << "Opcion no valida, intenta de nuevo." << endl;
			break;
		}
	} while (continuar);
}

void Clase_A::InsertarFinal()
{
	llenarAuxiliar();
	string Documento;
	ifstream ArchivoAUX("Auxiliar.bin", ios::binary);
	ArchivoAUX >> Documento;
	ArchivoAUX.close();
	CrearObjeto();
	ofstream Archivo("principal.bin", ios::binary);
	Archivo << Documento;
	int Tamnombre = Nombre.length();
	int CantB = 0;
	Archivo << Llave;
	Archivo << Tamnombre;
	Archivo << Nombre;
	for (int i = 0; i < 10; i++) {
		if (ObjB[i].Validador()) {
			CantB++;
		}
	}
	Archivo << CantB;
	for (int i = 0; i < 10; i++) {
		ObjB[i].Guardar(Archivo);
	}
	Archivo.close();
}

void Clase_A::InsertarInicio()
{
	llenarAuxiliar();
	string Documento;
	ifstream ArchivoAUX("Auxiliar.bin", ios::binary);
	ArchivoAUX >> Documento;
	ArchivoAUX.close();
	CrearObjeto();
	ofstream Archivo("principal.bin", ios::binary);
	int Tamnombre = Nombre.length();
	int CantB = 0;
	Archivo << Llave;
	Archivo << Tamnombre;
	Archivo << Nombre;
	for (int i = 0; i < 10; i++) {
		if (ObjB[i].Validador()) {
			CantB++;
		}
	}
	Archivo << CantB;
	for (int i = 0; i < 10; i++) {
		ObjB[i].Guardar(Archivo);
	}
	Archivo << Documento;
	Archivo.close();
}

void Clase_A::MostrarRegistro()
{
	string Documento;
	ifstream Archivo("principal.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	int TamDocumento = Documento.length();
	int Indice = -1;
	int LlaveMostrar;
	cout << "Ingresa la Llave del registro a mostrar: " << endl;
	cin >> LlaveMostrar;
	while (Indice < TamDocumento - 1) {
		Indice = CargarRegistro(Documento, Indice);
		if(Llave==LlaveMostrar){
			cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-." << endl;
			cout << "Registro con Llave# " << Llave << endl;
			cout << "Nombre: " << Nombre << endl;
			for (int i = 0; i < ObjetosB; i++) {
				if (ObjB[i].Booleano) {
					cout << "ObjetoB# " << i + 1 << " Nombre: " << ObjB[i].Cadena << endl;
				}
			}
			cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-." << endl;
		}
	}
}

void Clase_A::MostrarTodos()
{
	string Documento;
	ifstream Archivo("principal.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	int TamDocumento = Documento.length();
	int Indice = -1;
	cout << "Mostrando Registros" << endl;
	while (Indice < TamDocumento-1) {
		cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-." << endl;
		Indice = CargarRegistro(Documento, Indice);
		cout << "Registro con Llave# "<< Llave << endl;
		cout << "Nombre: "<<Nombre << endl;
		for (int i = 0; i < ObjetosB; i++) {
			if (ObjB[i].Booleano) {
				cout << "ObjetoB# "<<i+1<<" Nombre: "<<ObjB[i].Cadena << endl;
			}
		}

	}
	cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-." << endl;
}

bool Clase_A::Eliminar()
{
	string Documento;
	ifstream Archivo("principal.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	int TamDocumento = Documento.length();
	int Indice = -1;
	int LlaveEliminar;
	bool Eliminado = false;
	cout << "Ingresa la Llave del registro a eliminar: " << endl;
	cin >> LlaveEliminar;
	ofstream ArchivoNew("principal.bin", ios::binary);
	while (Indice < TamDocumento - 1) {
		Indice = CargarRegistro(Documento, Indice);
		if (Llave != LlaveEliminar) {
			int Tamnombre = Nombre.length();
			int CantB = 0;
			ArchivoNew << Llave;
			ArchivoNew << Tamnombre;
			ArchivoNew << Nombre;
			for (int i = 0; i < 10; i++) {
				if (ObjB[i].Validador()) {
					CantB++;
				}
			}
			ArchivoNew << CantB;
			for (int i = 0; i < 10; i++) {
				ObjB[i].Guardar(ArchivoNew);
			}
		}
		else
			Eliminado = true;
	}
	return Eliminado;
}

bool Clase_A::Modificar()
{
	string Documento;
	ifstream Archivo("principal.bin", ios::binary);
	Archivo >> Documento;
	Archivo.close();
	int TamDocumento = Documento.length();
	int Indice = -1;
	int LlaveMod;
	bool Modificado = false;
	cout << "Ingresa la Llave del registro a Modificar: " << endl;
	cin >> LlaveMod;
	ofstream ArchivoNew("principal.bin", ios::binary);
	while (Indice < TamDocumento - 1) {
		Indice = CargarRegistro(Documento, Indice);
		if (Llave != LlaveMod) {
			int Tamnombre = Nombre.length();
			int CantB = 0;
			ArchivoNew << Llave;
			ArchivoNew << Tamnombre;
			ArchivoNew << Nombre;
			for (int i = 0; i < 10; i++) {
				if (ObjB[i].Validador()) {
					CantB++;
				}
			}
			ArchivoNew << CantB;
			for (int i = 0; i < 10; i++) {
				ObjB[i].Guardar(ArchivoNew);
			}
		}
		else{
			Modificado = true;
			MenuModificar();
			int Tamnombre = Nombre.length();
			int CantB = 0;
			ArchivoNew << Llave;
			ArchivoNew << Tamnombre;
			ArchivoNew << Nombre;
			for (int i = 0; i < 10; i++) {
				if (ObjB[i].Validador()) {
					CantB++;
				}
			}
			ArchivoNew << CantB;
			for (int i = 0; i < 10; i++) {
				ObjB[i].Guardar(ArchivoNew);
			}
		}
	}
	return Modificado;
}
