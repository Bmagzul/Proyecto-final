// Proyecto final.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>
#include<stdio.h>
#include<conio.h>

using namespace std;
class baseDatos
{
	private:
		char servidor[10] = "localhost";
		char usuario[5] = "root";
		char contrasenia[5] = "root";
		char nombreBase[15] = "proyecto_final";
		int puerto = 3306;

	public:
		MYSQL* db;

		baseDatos()
		{
			conectar();
		}

		void conectar()
		{
			db = mysql_init(0);
			db = mysql_real_connect(db, servidor, usuario, contrasenia, nombreBase, puerto, NULL, 0);

			if (!db)
			{
				cout << "No se pudo conectar con la base de datos.\n";
				system("pause");
			}
		}

		void desconectar()
		{
			mysql_close(db);
		}

		MYSQL_RES* consulta(string query)
		{
			mysql_query(db, query.c_str());

			return mysql_store_result(db);
		}
};

class clsPersona
{
	public:
		int id;
		string nombre;
		string apellido;
		string direccion;
		string correo;
		string contrasenia;
		string telefono;
};

class persona : public baseDatos
{
	private:
		string tabla = "persona";
		string llave = "id";

	public:
		clsPersona registro = clsPersona();

		vector<clsPersona> buscar(string condicion = "")
		{
			vector<clsPersona> res;
			string query		= "SELECT * FROM " + tabla + " " + condicion;
			MYSQL_RES* lista	= consulta(query);

			MYSQL_ROW row;

			while ((row = mysql_fetch_row(lista)))
			{
				clsPersona tmp = clsPersona();
				tmp.id			= (int)row[0];
				tmp.nombre		= row[1];
				tmp.apellido	= row[2];
				tmp.direccion	= row[3];
				tmp.correo		= row[4];
				tmp.contrasenia = row[5];
				tmp.telefono	= row[6];

				res.push_back(tmp);
			}

			return res;
		}

		bool guardar() {
			string query = "";

			if (registro.id)
			{
				query = "UPDATE "+ tabla+ " SET ";
				query += "nombre = '" + registro.nombre + "', ";
				query += "apellido = '" + registro.apellido + "', ";
				query += "direccion = '" + registro.direccion + "', ";
				query += "correo = '" + registro.correo + "', ";
				query += "contrasenia = '" + registro.contrasenia + "', ";
				query += "telefono = '" + registro.telefono + "' ";
				query += "WHERE id = " + to_string(registro.id);
			}
			else
			{
				query = "INSERT INTO " + tabla + " VALUES(null, ";
				query += "'" + registro.nombre + "', ";
				query += "'" + registro.apellido + "', ";
				query += "'" + registro.direccion + "', ";
				query += "'" + registro.correo + "', ";
				query += "'" + registro.contrasenia + "', ";
				query += "'" + registro.telefono + "'";
				query += ")";
			}

			consulta(query);

			return true;
		}

		void capturarDatos(bool pedirCodigo=false)
		{
			if (pedirCodigo)
			{
				cout << endl << "Ingrese el codigo a actualizar." << endl;
				cin >> registro.id;
			}

			cout << "Ingrese el nombre: ";
			cin.ignore();
			getline(cin, registro.nombre);

			cout << "Ingrese el apellido: ";
			cin.ignore();
			getline(cin, registro.apellido);

			cout << "Ingrese la direccion: ";
			cin.ignore();
			getline(cin, registro.direccion);

			cout << "Ingrese el correo: ";
			cin.ignore();
			getline(cin, registro.correo);

			cout << "Ingrese el contrasenia: ";
			cin.ignore();
			getline(cin, registro.contrasenia);

			cout << "Ingrese el numero de telefono: ";
			cin.ignore();
			getline(cin, registro.telefono);
		}
};


void menuPersona()
{
	bool regresar = false;
	int opcion;

	persona objPersona = persona();

	system("cls");

	while (!regresar)
	{
		cout << "----  Datos de personas --- " << endl;
		cout << "1. Registrar persona" << endl;
		cout << "2. Actualizar persona" << endl;
		cout << "3. Regresar al menu anterior" << endl;
		cout << "Seleccione una opcion: " << endl;
		cin >> opcion;

		switch (opcion)
		{
			case 1:
				objPersona.capturarDatos();

				if (objPersona.guardar())
				{
					cout << endl<<"Persona guardada correctamente." << endl;
				}
				else {
					cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
				}
				
				break;
			case 2:
				
				objPersona.capturarDatos(true);

				if (objPersona.guardar())
				{
					cout << endl << "Persona actualizada correctamente." << endl;
				}
				else {
					cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
				}

				break;
			case 3:
				regresar = true;
			default:
				cout << "Opcion no encontrada."<<endl;
				break;
		}
	}
}


class clsDatosFinancieros
{
public:
	int id;
	int persona_id;
	string nombre_banco;
	string numero_cuenta;
	string tipo_cuenta;
	string numero_tarjeta;
	string tipo_tarjeta;
};

class datosFinancieros : public baseDatos
{
private:
	string tabla = "datos_financieros";
	string llave = "id";

public:
	clsDatosFinancieros registro = clsDatosFinancieros();

	vector<clsDatosFinancieros> buscar(string condicion = "")
	{
		vector<clsDatosFinancieros> res;
		string query = "SELECT * FROM " + tabla + " " + condicion;
		MYSQL_RES* lista = consulta(query);

		MYSQL_ROW row;

		while ((row = mysql_fetch_row(lista)))
		{
			clsDatosFinancieros tmp = clsDatosFinancieros();
			tmp.id				= (int)row[0];
			tmp.persona_id		= (int)row[1];
			tmp.nombre_banco	= row[2];
			tmp.numero_cuenta	= row[3];
			tmp.tipo_cuenta		= row[4];
			tmp.numero_tarjeta	= row[5];
			tmp.tipo_tarjeta	= row[6];

			res.push_back(tmp);
		}

		return res;
	}

	bool guardar() {
		string query = "";

		if (registro.id)
		{
			query = "UPDATE " + tabla + " SET ";
			query += "persona_id = " + to_string(registro.persona_id) + ", ";
			query += "nombre_banco = '" + registro.nombre_banco + "', ";
			query += "numero_cuenta = '" + registro.numero_cuenta + "', ";
			query += "tipo_cuenta = '" + registro.tipo_cuenta + "', ";
			query += "numero_tarjeta = '" + registro.numero_tarjeta + "', ";
			query += "tipo_tarjeta = '" + registro.tipo_tarjeta + "' ";
			query += "WHERE id = " + to_string(registro.id);
		}
		else
		{
			query = "INSERT INTO " + tabla + " VALUES(null, ";
			query += to_string(registro.persona_id) + ", ";
			query += "'" + registro.nombre_banco + "', ";
			query += "'" + registro.numero_cuenta + "', ";
			query += "'" + registro.tipo_cuenta + "', ";
			query += "'" + registro.numero_tarjeta + "', ";
			query += "'" + registro.tipo_tarjeta + "'";
			query += ")";
		}
		cout << query << endl;

		consulta(query);

		return true;
	}


	void capturarDatos(bool pedirCodigo = false)
	{
		if (pedirCodigo)
		{
			cout << endl << "Ingrese el codigo a actualizar." << endl;
			cin >> registro.id;
		}

		cout << "Ingrese el codigo de la persona: ";
		cin>> registro.persona_id;

		cout << "Ingrese el nombre del banco: ";
		cin.ignore();
		getline(cin, registro.nombre_banco);

		cout << "Ingrese el numero de cuenta: ";
		cin.ignore();
		getline(cin, registro.numero_cuenta);

		cout << "Ingrese el tipo de cuenta: ";
		cin.ignore();
		getline(cin, registro.tipo_cuenta);

		cout << "Ingrese el numero de tarjeta: ";
		cin.ignore();
		getline(cin, registro.numero_tarjeta);

		cout << "Ingrese el tipo de tarjeta: ";
		cin.ignore();
		getline(cin, registro.tipo_tarjeta);
	}
};


void menuDatosFinancieros()
{
	bool regresar = false;
	int opcion;

	datosFinancieros objDFinancieros = datosFinancieros();

	system("cls");

	while (!regresar)
	{
		cout << "----  Datos financieros --- " << endl;
		cout << "1. Registrar datos" << endl;
		cout << "2. Actualizar datos" << endl;
		cout << "3. Regresar al menu anterior" << endl;
		cout << "Seleccione una opcion: " << endl;
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			objDFinancieros.capturarDatos();

			if (objDFinancieros.guardar())
			{
				cout << endl << "Datos financieros guardados correctamente." << endl;
			}
			else {
				cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
			}

			break;
		case 2:

			objDFinancieros.capturarDatos(true);

			if (objDFinancieros.guardar())
			{
				cout << endl << "Datos financieros actualizados correctamente." << endl;
			}
			else {
				cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
			}

			break;
		case 3:
			regresar = true;
		default:
			cout << "Opcion no encontrada." << endl;
			break;
		}
	}
}

class clsCuentaVirtual
{
public:
	int id;
	int datos_financieros_id;
	string usuario;
	string contrasenia;
};

class cuentaVirtual : public baseDatos
{
private:
	string tabla = "cuenta_virtual";
	string llave = "id";

public:
	clsCuentaVirtual registro = clsCuentaVirtual();

	vector<clsCuentaVirtual> buscar(string condicion = "")
	{
		vector<clsCuentaVirtual> res;
		string query = "SELECT * FROM " + tabla + " " + condicion;
		MYSQL_RES* lista = consulta(query);

		MYSQL_ROW row;

		while ((row = mysql_fetch_row(lista)))
		{
			clsCuentaVirtual tmp = clsCuentaVirtual();
			tmp.id = (int)row[0];
			tmp.datos_financieros_id = (int)row[1];
			tmp.usuario = row[2];
			tmp.contrasenia= row[3];

			res.push_back(tmp);
		}

		return res;
	}

	bool guardar() {
		string query = "";

		if (registro.id)
		{
			query = "UPDATE " + tabla + " SET ";
			query += "datos_financieros_id = " + to_string(registro.datos_financieros_id) + ", ";
			query += "usuario = '" + registro.usuario + "', ";
			query += "contrasenia= '" + registro.contrasenia + "' ";
			query += "WHERE id = " + to_string(registro.id);
		}
		else
		{
			query = "INSERT INTO " + tabla + " VALUES(null, ";
			query += to_string(registro.datos_financieros_id) + ", ";
			query += "'" + registro.usuario + "', ";
			query += "'" + registro.contrasenia + "' ";
			query += ")";
		}

		consulta(query);

		return true;
	}


	void capturarDatos(bool pedirCodigo = false)
	{
		if (pedirCodigo)
		{
			cout << endl << "Ingrese el codigo a actualizar." << endl;
			cin >> registro.id;
		}

		cout << "Ingrese el codigo de los datos financieros: ";
		cin >> registro.datos_financieros_id;

		cout << "Ingrese el usuario: ";
		cin.ignore();
		getline(cin, registro.usuario);

		cout << "Ingrese la contrasenia: ";
		cin.ignore();
		getline(cin, registro.contrasenia);

	}
};


void menuCuentaVirtual()
{
	bool regresar = false;
	int opcion;

	cuentaVirtual objCuentaVirtual = cuentaVirtual();

	system("cls");

	while (!regresar)
	{
		cout << "----  Cuentas virtuales --- " << endl;
		cout << "1. Registrar cuenta virtual" << endl;
		cout << "2. Actualizar cuenta virtual" << endl;
		cout << "3. Regresar al menu anterior" << endl;
		cout << "Seleccione una opcion: " << endl;
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			objCuentaVirtual.capturarDatos();

			if (objCuentaVirtual.guardar())
			{
				cout << endl << "Cuenta virtual creada correctamente." << endl;
			}
			else {
				cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
			}

			break;
		case 2:

			objCuentaVirtual.capturarDatos(true);

			if (objCuentaVirtual.guardar())
			{
				cout << endl << "Cuenta virtual actualizada correctamente." << endl;
			}
			else {
				cout << endl << "Ocurrio un error, vuelva a intentarlo." << endl;
			}

			break;
		case 3:
			regresar = true;
		default:
			cout << "Opcion no encontrada." << endl;
			break;
		}
	}
}

class objBusquedas {
	public:
		int codigoPersona;
		string nombre;
		string apellido;
		string direccion;
		string correo;
		string contrasenia;
		string telefono;
		int codigoDatosFinancieros;
		string nombreBanco;
		string numeroCuenta;
		string tipoCuenta;
		string numeroTarjeta;
		string tipoTarjeta;
		int codigoBanca;
		string usuario;
		string contrasenia2;
};

class busquedas : public baseDatos
{
	private:
		
		MYSQL_RES* resultado;
		vector<objBusquedas> result;

	public:
		string condicion = "";

		vector<objBusquedas> getResult()
		{
			return result;
		}

		void buscar() {
			result.clear();

			string query = "";
			query += "SELECT ";
			query += "c.id as codigo_persona, c.nombre, c.apellido, c.direccion, c.correo, c.contrasenia, ";
			query += "c.telefono, b.id as codigo_datos_financieros, b.nombre_banco, b.numero_cuenta, ";
			query += "b.tipo_cuenta, b.numero_tarjeta, b.tipo_tarjeta, ";
			query += "c.id as codigo_banca,a.usuario, a.contrasenia ";
			query += "FROM cuenta_virtual a ";
			query += "JOIN datos_financieros b on b.id = a.datos_financieros_id ";
			query += "JOIN persona c on c.id = b.persona_id ";

			if (condicion != "")
			{
				query += condicion;
			}
			cout << endl << query << endl;
			resultado = consulta(query);

			procesarResulatado();

		}

		void procesarResulatado()
		{
			MYSQL_ROW row;

			while ((row = mysql_fetch_row(resultado)))
			{
				objBusquedas tmp = objBusquedas();
				tmp.codigoPersona = (int)row[0];
				tmp.nombre		= row[1];
				tmp.apellido	= row[2];
				tmp.direccion	= row[3];
				tmp.correo		= row[4];
				tmp.contrasenia = row[5];
				tmp.telefono	= row[6];

				tmp.codigoDatosFinancieros = (int)row[7];
				tmp.nombreBanco		= row[8];
				tmp.numeroCuenta	= row[9];
				tmp.tipoCuenta		= row[10];
				tmp.numeroTarjeta	= row[11];
				tmp.tipoTarjeta		= row[12];

				tmp.codigoBanca = (int)row[13];
				tmp.usuario		 = row[14];
				tmp.contrasenia2  = row[15];

				result.push_back(tmp);
			}
		}

		void mostrarResultado() {
			int cantidad = result.size();

			for (int i = 0; i < cantidad; i++) 
			{
				objBusquedas reg = result[i];
				cout << endl << "- Datos personales: " << endl;
				cout << "Codigo: " <<  reg.codigoPersona << endl;
				cout << "Nombre: " << reg.nombre << endl;
				cout << "Apellido: " << reg.apellido << endl;
				cout << "Direccion: " << reg.direccion << endl;
				cout << "Correo: " << reg.correo << endl;
				cout << "Contrasenia: " << reg.contrasenia << endl;
				cout << "Telefono: " << reg.telefono << endl;

				cout << endl << "- Datos financieros: " << endl;
				cout << "Codigo financiero: " << reg.codigoDatosFinancieros << endl;
				cout << "Nombre del banco: " << reg.nombreBanco << endl;
				cout << "Numero de cuenta: " << reg.numeroCuenta << endl;
				cout << "Tipo de cuenta: " << reg.tipoCuenta << endl;
				cout << "Numero tarjeta: " << reg.numeroTarjeta << endl;
				cout << "Tipo tarjeta: " << reg.tipoTarjeta << endl;

				cout << endl << "- Banca virtual: " << endl;
				cout << "Codigo de banca virtual: " << reg.codigoBanca << endl;
				cout << "Usuario: " << reg.usuario << endl;
				cout << "Contrasenia: " << reg.contrasenia2 << endl;

			}
		}
};

void menuBusquedas()
{
	bool regresar = false;
	int opcion;

	busquedas buscador = busquedas();
	bool mostrar = false;
	string termino = "";
	
	while (!regresar)
	{
		system("cls");
		mostrar = true;
		termino = "";

		cout << "----  Busquedas --- " << endl;
		cout << "1. Busqueda general" << endl;
		cout << "2. Busqueda por nombre persona" << endl;
		cout << "4. Busqueda por usuario" << endl;
		cout << "3. Busqueda por tipo de cuenta" << endl;
		cout << "5. Regresar al menu anterior" << endl;
		cout << "Seleccione una opcion: " << endl;
		cin >> opcion;


		switch (opcion)
		{
		case 1:
			buscador.condicion = "";
			break;
		case 2:
			cout << "Ingrese el nombre de la persona a buscar: ";
			cin.ignore();
			getline(cin, termino);

			buscador.condicion = "WHERE (c.nombre LIKE '%"+termino+"%')";
			break;
		case 3:
			cout << "Ingrese el usuario a buscar: ";
			cin.ignore();
			getline(cin, termino);

			buscador.condicion = "WHERE (a.usuario LIKE '%" + termino + "%')";
			break;
		case 4:
			cout << "Ingrese el tipo de cuenta a buscar: ";
			cin.ignore();
			getline(cin, termino);

			buscador.condicion = "WHERE (b.tipo_cuenta LIKE '%" + termino + "%')";
			break;
		case 5:
			regresar = true;
			mostrar = false;
			break;
		default:
			mostrar = false;
			cout << "Opcion no encontrada." << endl;
			break;
		}

		if (mostrar)
		{
			buscador.buscar();
			buscador.mostrarResultado();
		}
		cout << endl << "Presione una tecla para continuar."<<endl;
		_getch();
	}
}

void mostrarMenu() 
{
	int opcion;
	cout << "----- Bienvenido ------"<<endl;
	cout << "1. Persona."<<endl;
	cout << "2. Datos financieros." << endl;
	cout << "3. Cuenta virtual." << endl;
	cout << "4. Busquedas." << endl;
	cout << "Seleccione la opcion: ";

	cin >> opcion;
	cout << endl;
	if (opcion == 1)
	{
		menuPersona();
	}
	else if (opcion == 2)
	{
		menuDatosFinancieros();
	}
	else if (opcion == 3)
	{
		menuCuentaVirtual();
	}
	else if (opcion == 4)
	{
		menuBusquedas();
	}
	else 
	{
		cout << "Opcion no encontrada" << endl << endl;
		mostrarMenu();
	}
}

int main()
{
	mostrarMenu();

	system("pause");
	return 0;
}