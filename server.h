#ifndef SERVER_H_
#define SERVER_H_
#include <map>
#include <string>
#include "common_socket.h"
#include "server_aceptadorDeClientes.h"

class Servidor {
private:
	const char *servicio;
	Socket socket;
	std::map<std::string,std::string> configuracion;
	AceptadorDeClientes aceptador;

public:
	Servidor(const char *servicio, char* infile);
	virtual ~Servidor();

	void ejecutar();
};

#endif
