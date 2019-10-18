#ifndef SERVIDOR_SERVER_ACEPTADORDECLIENTES_H_
#define SERVIDOR_SERVER_ACEPTADORDECLIENTES_H_
#include "common_socket.h"
#include "server_thread.h"
#include <map>
#include <string>

class AceptadorDeClientes: public Thread {
private:
	Socket &socket;
	std::map<std::string,std::string> &configuracion;

public:
	AceptadorDeClientes(Socket &socket,
			std::map<std::string,std::string> &configuracion);
	virtual ~AceptadorDeClientes();

	virtual void run();
};

#endif
