#ifndef SERVER_MENSAJERO_H_
#define SERVER_MENSAJERO_H_
#include <string>
#include "server_comando.h"

class Mensajero: public Comando {
private:
	int codigo;
	std::string mensaje;
	int codigoNoInicio;
	std::string mensajeNoInicio;

public:
	Mensajero(int codigo,
			std::string mensaje,
			int codigoNoInicio,
			std::string mensajeNoInicio);
	virtual ~Mensajero();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
