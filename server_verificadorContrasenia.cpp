#include "server_verificadorContrasenia.h"
#include <string>
#include <iostream>

VerificadorContrasenia::VerificadorContrasenia(std::string clave,
		std::string aVerificar, int codigoExito,
		std::string mensajeExito, int codigoFracaso,
		std::string mensajeFracaso): clave(clave), aVerificar(aVerificar),
		codigoExito(codigoExito), mensajeExito(mensajeExito),
		codigoFracaso(codigoFracaso), mensajeFracaso(mensajeFracaso){
}

VerificadorContrasenia::~VerificadorContrasenia() {
}

int VerificadorContrasenia::ejecutar(bool &usuarioValido,
		bool &contaseniaValida, Socket &socket){
	contaseniaValida = (this->clave == this->aVerificar);
	if (usuarioValido && contaseniaValida){
		enviar_mensaje(this->codigoExito, this->mensajeExito, socket);
	}else{
		enviar_mensaje(this->codigoFracaso, this->mensajeFracaso, socket);
	}
	return 0;
}
