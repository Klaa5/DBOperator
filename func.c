#include "proto.h"
#include <string.h>
#include "DBinfo.h"

int main_menu()
{
	
	int sel = 0;
	
	while ( sel == 0 || (sel-10) <= 6 )	//Operacion para evitar que la eleccion sea diferente a 1,2,3 y 4 
	{
		printf("Accion a hacer...\n");
		
		
		//Acá agregar opciones de menu y devoluciones correspondientes.
		
	}
	
	return sel;
	
}

bool conectar(MYSQL **conexion)
{
	MYSQL *resCon;
	bool conectadoSN = false;
	bool proceder = true;
	*conexion = mysql_init(NULL);	//Se inicializa en 'null' el puntero recibido por referencia.
	char ingreso[100] = " ";	//Almacen único de ingreso
	char *host = NULL, *usuario = NULL, *password = NULL, *database = NULL;
	char eleccion = ' ';

	
	while (conectadoSN == false && proceder == true) 
	{

		if (ingresarM() == 1)
		{

			printf("Ingrese la base de datos a la cual conectar: \n");
			printf("Host:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&host, ingreso);
			printf("Usuario:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&usuario, ingreso);
			printf("Contraseña:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&password, ingreso);
			printf("Nombre de Base de datos:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&database, ingreso);

			resCon = mysql_real_connect(*conexion,host,usuario,password,database,0,NULL,0);
		
		}
		else
		{	//Si no es manual, se ingresa con datos de DBinfo.h
			resCon = mysql_real_connect(*conexion,HOST,USERNAME,PASSWORD,DATABASE,0,NULL,0);
		}

		 
		
		if (resCon != NULL)
		{
			printf("\nBase de datos conectada correctamente.\n");
			conectadoSN = true;
		}
		else
		{
			printf("\nError al conectar con la base de datos!.\n");
			printf("Reintentar? s/n\n");
			scanf(" %c",&eleccion);
			
			if(eleccion == 'n')
			{
				proceder = false;
			}
			
		}
		
	}
	
	//Liberar memoria...
	free(host);
	free(usuario);
	free(password);
	free(database);

	return conectadoSN;
	
}

void seleccion(MYSQL *conexion)
{
	int codError = 0;
	MYSQL_RES *resultado_select;
	MYSQL_FIELD *temp; 
	codError = mysql_query(conexion,"SELECT * FROM Ventas WHERE cod_producto = 1;"); //Esto hace el select y lo deja en espera
	
	if(codError == 0)
	{
		resultado_select = mysql_store_result(conexion);	//Se almacena el resultado del select anterior.
		
		//while (temp = MYSQL_FETCH_FIELD(*resultado_select))	//Mientas haya elementos y fetch no devuelva NULL
		//{
		//	printf("%s", temp.(ACA VA EL CAMPO A MOSTRAR));	//FALTA TERMINAR
		//}
		
		printf("\n");
		
	}
	else
	{
		printf("\nError al consultar la base de datos!\n");
	}
	
}


int ingresarM()
{

	int eleccion = ' ';

	printf("Desea ingresar una base de datos manualmente? s/n\n");
    getchar();  //Por el buffer.
    eleccion = getchar();

	if(eleccion == 's' || eleccion == 'S')
     { 
		return 1;	
     }
	else
	{
		return 0;	
    }
	

}

void asignador_de_memoria(char **cadena, char array[100])
{
	int val = strlen(array);	//Se consigue el tamaño de la cadena.
	 	
    
    *cadena = (char*)malloc((val + 1) * sizeof(char));	//Asigna memoria con malloc.
   
	//Ya con espacios asignados en el puntero, se almacena el dato:
    
    strcpy(*cadena,array);

}