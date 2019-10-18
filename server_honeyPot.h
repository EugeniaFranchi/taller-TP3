#ifndef SERVER_FTPPOT_H_
#define SERVER_FTPPOT_H_
#include <fstream>
#include <map>
#include <set>
#include <string>
#include "server_comando.h"
#include "server_fabricaDeComandos.h"
#include "common_socket.h"
#include "server_thread.h"
#include "server_setBloqueante.h"

typedef Comando* (FabricaDeComandos::*fabricador) (std::string);
class HoneyPot: public Thread {
private:
	std::map<std::string,std::string> &configuracion;
	std::map<std::string,fabricador> fabricas;
	SetBloqueante &directorio;
	bool usuarioValido;
	bool contaseniaValida;
	Socket socket;
	bool cerrado;

public:
	HoneyPot(std::map<std::string,std::string> &configuracion,
			Socket socket, SetBloqueante &directorio);
	virtual ~HoneyPot();

	virtual void run();
	void loggear_cliente();
	void cerrar();
	bool esta_cerrado();
};

#endif
