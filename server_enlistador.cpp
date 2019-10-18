#include "server_enlistador.h"
#include <string>
#include <set>

Enlistador::Enlistador(int codigoInicio, std::string inicio,
		int codigoFin, std::string fin, int codigoNoInicio,
		std::string mensajeNoInicio,
		std::string numerador, SetBloqueante &directorio):
		codigoInicio(codigoInicio), inicio(inicio), codigoFin(codigoFin),
		fin(fin), codigoNoInicio(codigoNoInicio), mensajeNoInicio(mensajeNoInicio),
		numerador(numerador), directorio(directorio){
}

Enlistador::~Enlistador() {
}

int Enlistador::ejecutar(bool &usuarioValido, bool &contaseniaValida,
		Socket &socket){
	if(!usuarioValido || !contaseniaValida){
		enviar_mensaje(this->codigoNoInicio, this->mensajeNoInicio, socket);
		return -1;
	}
	enviar_mensaje(this->codigoInicio, this->inicio, socket);
	std::set<std::string>::iterator iterador = this->directorio.inicio();
	for(; iterador != this->directorio.fin(); ++iterador){
		enviar_mensaje(-1, this->numerador + " " + *iterador, socket);
	}
	enviar_mensaje(this->codigoFin, this->fin, socket);
	return 0;
}
