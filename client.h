#ifndef CLIENT_H_
#define CLIENT_H_
#include "common_socket.h"

class Cliente {
private:
	Socket socket;

public:
	Cliente(const char* hostname, const char *servicio);
	virtual ~Cliente();

	void ejecutar();
};

#endif
