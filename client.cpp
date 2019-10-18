#define _POSIX_C_SOURCE 200112L
#include "client.h"
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>

#define CODIGOFINLISTA "226"
#define CODIGONOLOGGEADO "530"
#define ERRORSOCKET "El socket servidor fue cerrado\n."
#define ERRORSOCKETRECIBIR "Hubo un error al recibir mensajes.\n"
/*****************************************
 * 		FUNCIONES AUXILIARES			 *
 *****************************************/
static std::string recibir_e_imprimir_mensaje_servidor(Socket &socket){
	std::string linea;
	try{
		socket.recibir(linea);
	} catch (std::exception &e){
		std::cerr << ERRORSOCKETRECIBIR;
		return NULL;
	}
	std::cout << linea;
	return linea;
}

static void recibir_lista(std::string recibido, Socket &socket){
	std::string codigo = recibido.substr(0,3);
	while(codigo != CODIGOFINLISTA && codigo != CODIGONOLOGGEADO){
		recibido = recibir_e_imprimir_mensaje_servidor(socket);
		codigo = recibido.substr(0,3);
	}
}
/*****************************************
 * 				PRIMITIVAS				 *
 *****************************************/
Cliente::Cliente(const char* hostname, const char *servicio):
		socket(hostname, servicio){
	this->socket.conectar();
}

Cliente::~Cliente() {
}

void Cliente::ejecutar(){
	try{
		std::string linea;
		recibir_e_imprimir_mensaje_servidor(this->socket);
		while (std::getline(std::cin, linea)){
			this->socket.enviar((linea + '\n').c_str(), linea.size() + 1);
			std::string recibido = recibir_e_imprimir_mensaje_servidor(this->socket);
			if(linea == "QUIT"){
				break;
			}
			if(linea == "LIST"){
				recibir_lista(recibido, this->socket);
			}
		}
	}catch(std::exception &e){
		std::cerr << ERRORSOCKET;
	}
}
