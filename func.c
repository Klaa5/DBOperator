#include "proto.h"
#include "DBinfo.h"
#include <mysql/mysql.h>
#include "stdlib.h"
#include "stdbool.h"
#include <string.h>


bool conectar(MYSQL **conexion)
{
	MYSQL *resCon;
	bool conectadoSN = false;
	bool proceder = true;
	char ingreso[100] = " ";					//Almacen único de ingreso
	char *host = NULL, *usuario = NULL, *password = NULL, *database = NULL;
	char eleccion = ' ';
	
	*conexion = mysql_init(NULL);				//Se inicializa en 'null' el puntero recibido por referencia.
	
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
			printf("Contrasenia:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&password, ingreso);
			printf("Nombre de Base de datos:\n");
			scanf("%s",ingreso);
			asignador_de_memoria(&database, ingreso);
			
			resCon = mysql_real_connect(*conexion,host,usuario,password,database,PORT,NULL,0);
			
		}
		else
		{	//Si no es manual, se ingresa con datos de DBinfo.h
			resCon = mysql_real_connect(*conexion,HOST,USERNAME,PASSWORD,DATABASE,PORT,NULL,0);
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
void ingresoDatos(MYSQL *conexion)
{
	
	char titulo[30];
	char descripcion[100];
	char clasificacion[30];
	
	printf("Ingrese el Titulo: ");
	scanf("%s", titulo);
	while (getchar() != '\n');

	printf("Ingrese la descripción: ");
	scanf("%s", descripcion);
	while (getchar() != '\n');
	
	printf("Ingrese la clasificación: ");
	scanf("%s", clasificacion);
	while (getchar() != '\n');
	
	char consulta[300];
	snprintf(consulta, sizeof(consulta), "INSERT INTO juegos (titulo, descripcion,clasificacion) VALUES ('%s', '%s', '%s')", titulo, descripcion, clasificacion);
	
	if (mysql_query(conexion, consulta)) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(conexion));
	} 
	else 
	{
		printf("Datos insertados correctamente.\n");
	}
}
void elimino(MYSQL *conexion)
{
	char ingreso[50] = "";
	char consulta[100] = "DELETE FROM juegos WHERE id=";
	
	printf("Ingrese campo clave a eliminar: \n");
	scanf("%s",ingreso);
	
	strcat(consulta, ingreso);
	
	if (mysql_query(conexion, consulta)) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(conexion));
	} 
	else 
	{
		printf("Datos eliminados correctamente.\n");
	}
}
void modificarRegistro(MYSQL *conexion, const char *campoClave, const char *valorClave, const char *nuevoValor) 
{//const char *nuevoValor: el nuevo valor que se asignará al campo no clave del registro.
	char consulta[200]; 
	snprintf(consulta, sizeof(consulta), "UPDATE tabla SET campo_no_clave = '%s' WHERE %s = '%s'", nuevoValor, campoClave, valorClave);
	
	if (mysql_query(conexion, consulta)) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(conexion));
		return;
	}
	
	printf("Registro actualizado correctamente.\n");
}
void modificar(MYSQL *conexion) 
{
	int campoClave;
	char nuevoValor1[30];
	char nuevoValor2[100];
	char nuevoValor3[30];
	char consulta[200];
	
	printf("Ingrese el valor del campo clave: ");
	scanf("%d", &campoClave);
	getchar(); // Para consumir el salto de línea que queda en el buffer
	
	snprintf(consulta, sizeof(consulta), "SELECT id FROM juegos WHERE id = %d", campoClave);
	
	if (mysql_query(conexion, consulta)) 
	{
		fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(conexion));
		return;
	}
	
	MYSQL_RES *resultado = mysql_store_result(conexion);
	if (resultado == NULL) 
	{
		fprintf(stderr, "Error al almacenar el resultado: %s\n", mysql_error(conexion));
		return;
	}
	
	int numFilas = mysql_num_rows(resultado);
	if (numFilas > 0) 
	{
		printf("El registro con ID %d existe en la tabla.\n", campoClave);
		
		printf("Ingrese el nuevo titulo: ");
		fgets(nuevoValor1, sizeof(nuevoValor1), stdin);
		nuevoValor1[strcspn(nuevoValor1, "\n")] = 0; 
		
		printf("Ingrese la nueva descripcion: ");
		fgets(nuevoValor2, sizeof(nuevoValor2), stdin);
		nuevoValor2[strcspn(nuevoValor2, "\n")] = 0; 
		
		printf("Ingrese la nueva clasificacion: ");
		fgets(nuevoValor3, sizeof(nuevoValor3), stdin);
		nuevoValor3[strcspn(nuevoValor3, "\n")] = 0; 
		
		char consulta2[300]; 
		snprintf(consulta2, sizeof(consulta2),"UPDATE juegos SET titulo = '%s', descripcion = '%s', clasificacion = '%s' WHERE id = %d",nuevoValor1, nuevoValor2, nuevoValor3, campoClave);
		
		if (mysql_query(conexion, consulta2)) 
		{
			fprintf(stderr, "Error al actualizar el registro: %s\n", mysql_error(conexion));
		} 
		else 
		{
			printf("Registro actualizado correctamente.\n");
		}
	} 
	else 
	{
		printf("No se encontro ningun registro con ID %d en la tabla.\n", campoClave);
	}
}

void consulto(MYSQL *conexion, int clave)
{
	int codError = 0, filas = 0, ct = 0;
	MYSQL_RES *resultado_select;
	MYSQL_ROW datos;
	char cons[100]; // Aumenté el tamaño para asegurar espacio suficiente
	
	// Construir la consulta SQL
	sprintf(cons, "SELECT * FROM juegos WHERE id = %d", clave);
	
	codError = mysql_query(conexion, cons);
	
	if (codError == 0)
	{
		resultado_select = mysql_store_result(conexion);
		
		filas = mysql_num_rows(resultado_select);
		
		if (filas == 0)
		{
			printf("No existen datos con ID %d\n", clave);
			return;
		}
		
		printf("ID\tTitulo\t\tDescripcion\tClasificacion\n");
		
		while ((datos = mysql_fetch_row(resultado_select)) != NULL)
		{
			printf("%s\t%s\t%s\t%s\n", datos[0], datos[1], datos[2], datos[3]);
			ct++;
		}
		
		mysql_free_result(resultado_select);
		printf("\n");
	}
	else
	{
		printf("Error al consultar la base de datos: %s\n", mysql_error(conexion));
	}
}

void Listar(MYSQL *conexion) 
{
	int codError = 0, filas = 0, ct = 0;
	MYSQL_RES *resultado_select;
	MYSQL_ROW datos;
	
	codError = mysql_query(conexion,"SELECT * FROM juegos;"); //Esto hace el select, lo deja en espera o obtiene codigo de error.
	
	if(codError == 0)	//Si da otra cosa diferente a 0 hubo un error.
	{
		resultado_select = mysql_store_result(conexion);	//Se almacena el resultado del select anterior.
		
		filas = mysql_num_rows(resultado_select);			//Obtengo cantidad de filas y las guardo.
		
		printf("ID\tTitulo\tDescripcion\tClasificacion\n");	//Línea título.
		
		while (ct < filas && datos != NULL)									//Mientas el contador no llegue al final...
		{
			datos = mysql_fetch_row(resultado_select);		//Se hace fetch de la fila de datos.
			//printf("%d\t", datos[0]);
			printf("%s\t %s\t %s\t %s\n",datos[0],datos[1],datos[2],datos[3]);
			ct++;
		}
		
		mysql_free_result(resultado_select);			 //Liberando memoria.
		
		printf("\n");
		
	}
	else
	{
		printf("\nError al consultar la base de datos!\n");
		
	}
}






