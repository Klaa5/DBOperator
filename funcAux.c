#include "proto.h"
#include "stdlib.h"
#include "stdbool.h"
#include <string.h>


int main_menu()
{
	
	int sel = 0;
	
	printf("   Menu\n ====\n 1-Ingreso\n 2-Elimino\n 3-Modifico\n 4-Consulto\n 5-Listo\n 6-Fin\n");
	scanf("%d",&sel);
	
	return sel;
	
}


int ingresarM()
{
	char eleccion;
	
	printf("Desea ingresar una base de datos manualmente (s/n): ");
	scanf(" %c", &eleccion); // Leer un carácter, ignorando espacios y saltos de línea
	
	if (eleccion == 's' || eleccion == 'y')
	{ 
		return 1; // El usuario desea ingresar manualmente
	}
	else
	{
		return 0; // El usuario no desea ingresar manualmente
	}
}

void asignador_de_memoria(char **cadena, char array[100])
{
	int val = strlen(array);	//Se consigue el tamaño de la cadena.
	
	
	*cadena = (char*)malloc((val + 1) * sizeof(char));	//Asigna memoria con malloc.
	
	//Ya con espacios asignados en el puntero, se almacena el dato:
	
	strcpy(*cadena, array);
	
}
