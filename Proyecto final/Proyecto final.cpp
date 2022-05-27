// Proyecto final.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mysql.h>

using namespace std;
MYSQL* db;

void setConexion() 
{
    db = mysql_init(0);
    db = mysql_real_connect(db, "localhost", "root", "root", "proyecto_final", 3306, NULL, 0);

    if (!db)
    {
        cout << "No se pudo conectar con la base de datos.\n";
        system("pause");
    }
}

void actualizarPersona()
{
    MYSQL_RES* res;
    MYSQL_ROW row;

    mysql_query(db, "SELECT * FROM persona");
    res = mysql_store_result(db);

    int num_fields = mysql_num_fields(res);
    // Fetch all rows from the result
    while ((row = mysql_fetch_row(res)))
    {
        cout << "Codigo: " << row[0] << endl;
        cout << "Nombre: " << row[1] << endl;
        cout << "Apellido: " << row[1] << endl;
        cout << "Direccion: " << row[1] << endl;
        cout << "Correo: " << row[1] << endl;
        cout << "Contraseña: " << row[1] << endl;
        cout << "Teléfono: " << row[1] << endl<<endl;
    }

    string codigo;
    cout << "Ingrese el codigo de la persona a actualizar: ";
    cin >> codigo;

    string nombre, apellido, direccion, correo, contrasenia, telefono;
    cout << "Ingrese el nombre: ";
    cin >> nombre;
    cout << "Ingrese el apellido: ";
    cin >> apellido;
    cout << "Ingrese la dirección: ";
    cin >> direccion;
    cout << "Ingrese el correo: ";
    cin >> correo;
    cout << "Ingrese el contraseña: ";
    cin >> contrasenia;
    cout << "Ingrese el número de teléfono: ";
    cin >> telefono;

    string query = "UPDATE persona SET ";
    query += "nombre = '" + nombre + "', ";
    query += "apellido = '" + apellido + "', ";
    query += "direccion = '" + direccion + "', ";
    query += "correo = '" + correo + "', ";
    query += "contrasenia = '" + contrasenia + "', ";
    query += "telefonso = '" + telefono + "' ";
    query += "WHERE id = '" + codigo + "'";


    if (!mysql_query(db, query.c_str()))
    {
        const char* error = mysql_error(db);
        cout << "Error al actualizar el registro." << error << endl;
    }
    else
    {
        if (mysql_affected_rows(db) > 0)
        {
            cout << "Registro actualizado correctamente." << endl;
        }
        else
        {
            cout << "Nada que actualizar." << endl;
        }
    }

}

void mostrarMenu() 
{
    int opcion;
    cout << "----- Bienvenido ------"<<endl;
    cout << "1. Actualizar persona."<<endl;
    cout << "Seleccione la opcion: ";

    cin >> opcion;
    cout << endl;
    if (opcion == 1)
    {
        actualizarPersona();
    } 
    else 
    {
        cout << "Opcion no encontrada" << endl << endl;
        mostrarMenu();
    }

}

int main()
{
    setConexion();
    mostrarMenu();

    system("pause");
    return 0;
}