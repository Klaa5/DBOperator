#ifndef PROTO_H
#define PROTO_H

#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "DBinfo.h"
#include <mysql/mysql.h>
#include <string.h>

//Principales
bool conectar(MYSQL **conexion);
void consulto(MYSQL *conexion, int clave);
void elimino(MYSQL *conexion);
void Listar(MYSQL *conexion);
void modificar(MYSQL *conexion);
void ingresoDatos(MYSQL *conexion);
//AUX
int main_menu();
int ingresarM();
void asignador_de_memoria(char **cadena, char array[100]);

#endif
