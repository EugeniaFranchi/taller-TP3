#ifndef SERVER_VERIFICADORUSUARIO_H_
#define SERVER_VERIFICADORUSUARIO_H_
#include <string>

#include "server_comando.h"

class VerificadorUsuario: public Comando {
private:
	std::string clave;
	int codigo;
	std::string mensaje;
	std::string aVerificar;

public:
	VerificadorUsuario(std::string clave, int codigo,
			std::string mensaje, std::string aVerificar);
	virtual ~VerificadorUsuario();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
