#ifndef PROTO_H
#define PROTO_H

#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "DBinfo.h"
#include "func.c"
#include <mysql/mysql.h>
#include <string.h>

bool conectar(MYSQL **conexion);
void seleccion(MYSQL *conexion);
int main_menu();
int ingresarM();
void asignador_de_memoria(char **cadena, char array[100]);

#endif