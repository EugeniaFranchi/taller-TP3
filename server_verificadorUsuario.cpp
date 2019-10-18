#include "server_verificadorUsuario.h"
#include <string>
#include <iostream>

VerificadorUsuario::VerificadorUsuario(std::string clave, int codigo,
		std::string mensaje, std::string aVerificar):
		clave(clave), codigo(codigo), mensaje(mensaje), aVerificar(aVerificar){
}

VerificadorUsuario::~VerificadorUsuario() {
}

int VerificadorUsuario::ejecutar(bool &usuarioValido, bool &contaseniaValida,
		Socket &socket){
	usuarioValido = (this->clave == this->aVerificar);
	enviar_mensaje(this->codigo, this->mensaje, socket);
	return 0;
}
