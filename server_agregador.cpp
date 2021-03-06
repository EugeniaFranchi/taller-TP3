#include "server_agregador.h"
#include <string>

Agregador::Agregador(int codigoExito, std::string mensajeExito,
		int codigoFracaso, std::string mensajeFracaso,
		int codigoNoIniciado, std::string mensajeNoInicio,
		std::string aAgregar, SetBloqueante &directorio):
		codigoExito(codigoExito), mensajeExito(mensajeExito),
		codigoFracaso(codigoFracaso), mensajeFracaso(mensajeFracaso),
		codigoNoIniciado(codigoNoIniciado), mensajeNoInicio(mensajeNoInicio),
		aAgregar(aAgregar), directorio(directorio){
}

Agregador::~Agregador() {
}

int Agregador::ejecutar(bool &usuarioValido, bool &contaseniaValida,
		Socket &socket){
	if(!usuarioValido || !contaseniaValida){
		enviar_mensaje(this->codigoNoIniciado, this->mensajeNoInicio, socket);
		return -1;
	}
	if(this->directorio.agregar(this->aAgregar) != 0){
		enviar_mensaje(this->codigoFracaso, this->mensajeFracaso, socket);
		return 1;
	}
	std::string mensaje = '"' + this->aAgregar +  '"' + ' ' + this->mensajeExito;
	enviar_mensaje(this->codigoExito, mensaje, socket);
	return 0;
}
