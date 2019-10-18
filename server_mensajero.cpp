#include "server_mensajero.h"
#include <string>

Mensajero::Mensajero(int codigo, std::string mensaje,
		int codigoNoInicio, std::string mensajeNoInicio):
		codigo(codigo), mensaje(mensaje), codigoNoInicio(codigoNoInicio),
		mensajeNoInicio(mensajeNoInicio) {
}

Mensajero::~Mensajero() {
}

int Mensajero::ejecutar(bool &usuarioValido, bool &contaseniaValida,
		Socket &socket){
	if(!usuarioValido || !contaseniaValida){
		enviar_mensaje(this->codigoNoInicio, this->mensajeNoInicio, socket);
		return -1;
	}
	enviar_mensaje(this->codigo, this->mensaje, socket);
	return 0;
}
