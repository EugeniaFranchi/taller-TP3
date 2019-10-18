#ifndef SERVER_VERIFICADORCONTRASENIA_H_
#define SERVER_VERIFICADORCONTRASENIA_H_
#include <string>

#include "server_comando.h"

class VerificadorContrasenia: public Comando {
private:
	std::string clave;
	std::string aVerificar;
	int codigoExito;
	std::string mensajeExito;
	int codigoFracaso;
	std::string mensajeFracaso;

public:
	VerificadorContrasenia(std::string clave,
			std::string aVerificar, int codigoExito,
			std::string mensajeExito, int codigoFracaso,
			std::string mensajeFracaso);
	virtual ~VerificadorContrasenia();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
