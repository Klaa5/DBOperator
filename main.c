#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "proto.h"
#include "DBinfo.h"
#include <mysql/mysql.h>


int main() 
{
	int seleccion = 0;
	bool infoConexion = false;
	MYSQL *conexion;
	
	//Se inicia la conexión y se comprueba si el user pudo hacerlo.
	infoConexion = conectar(&conexion);	//Funcion conectar recibiento parametro "conexion" como referencia
	
	main_menu(); //Menú de acciones
	
	switch(seleccion)
	{
		case 1:													break;

		case 2: 												break;

		case 3:													break;

		case 4:													break;
	
		default:	printf("Ninguna opción seleccionada.\n"); break;
	}
	
	
	
	return 0;
}