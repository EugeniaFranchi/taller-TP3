#include "server_comando.h"
#include <string>

Comando::Comando() {
}

Comando::~Comando() {
}

void Comando::enviar_mensaje(int codigo, std::string mensaje, Socket &socket){
	std::string linea = "";
	if (codigo >= 0){
		linea = linea + std::to_string(codigo) + ' ';
	}
	linea = linea + mensaje + '\n';
	socket.enviar(linea.c_str(), linea.size());
}
