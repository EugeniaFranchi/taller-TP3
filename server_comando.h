#ifndef SERVER_COMANDO_H_
#define SERVER_COMANDO_H_
#include "common_socket.h"
#include <string>

class Comando {
public:
	Comando();
	virtual ~Comando();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket) = 0;
protected:
	virtual void enviar_mensaje(int codigo, std::string mensaje, Socket &socket);
};

#endif
