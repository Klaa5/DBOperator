#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "proto.h"
#include "DBinfo.h"
#include <mysql/mysql.h>

int main(int argc, char *argv[]) 
{
	int seleccion = 0;
	bool infoConexion = false;
	MYSQL *conexion;
	int clave;
	//Se inicia la conexión y se comprueba si el user pudo hacerlo.
	infoConexion = conectar(&conexion);	//Funcion conectar recibiento parametro "conexion" como referencia
	
	if (infoConexion == true) 
	{
		do 
		{
			seleccion = main_menu(); //Menú de acciones
			
			switch(seleccion)
			{
				case 1:		ingresoDatos(conexion);						break;
				
				case 2: 	elimino(conexion);							break;
				
				case 3:		modificar(conexion);						break;
				
				case 4:			
							printf("ingrese campo clave: ");
							scanf("%d",&clave);
							consulto(conexion,clave);					break;
				
				case 5:		Listar(conexion);							break;
				
				case 6:		return 0;									break;
				
				default:	printf("Ninguna opcion seleccionada.\n");	break;
			}
			
			seleccion = 0;
			
		} while (seleccion != 6);
	} 
	
	
	return 0;
}
