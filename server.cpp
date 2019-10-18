#define _POSIX_C_SOURCE 200112L
#include "server.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <vector>
#include <map>

/*******************************************
 *          FUNCIONES AUXILIARES
 ******************************************/
static std::map<std::string,std::string> crear_configuracion(char* infile){
	std::map<std::string,std::string> configuracion;
	std::ifstream entrada(infile);
	while (entrada.good()){
		std::string clave;
		std::getline(entrada, clave, '=');
		std::string valor;
		std::getline(entrada, valor);
		configuracion[clave] = valor;
	}
	return configuracion;
}
/*******************************************
 * 				PRIMITIVAS				   *
 *******************************************/

Servidor::Servidor(const char *servicio, char* infile): servicio(servicio),
		socket(Socket(NULL, servicio)), configuracion(crear_configuracion(infile)),
		aceptador(socket, this->configuracion){
}

Servidor::~Servidor() {
}

void Servidor::ejecutar(){
	std::string linea;
	this->aceptador.start();
	std::getline(std::cin, linea);
	while(linea != "q"){
		linea.clear();
		std::getline(std::cin, linea);
	}
	this->socket.cerrar();
	this->aceptador.join();
}
