#ifndef SERVER_FABRICADECOMANDOS_H_
#define SERVER_FABRICADECOMANDOS_H_
#include <map>
#include <set>
#include <string>
#include "server_comando.h"
#include "server_setBloqueante.h"

class FabricaDeComandos {
private:
	std::map<std::string,std::string> &configuracion;
	SetBloqueante &directorio;

public:
	FabricaDeComandos(std::map<std::string,std::string> &configuracion,
			SetBloqueante &directorio);
	virtual ~FabricaDeComandos();

	Comando* construirVerificadorUsuario(std::string auxiliar);
	Comando* construirVerificadorContrasenia(std::string auxiliar);
	Comando* construirMensajeroSyst(std::string auxiliar);
	Comando* construirMensajeroHelp(std::string auxiliar);
	Comando* construirMensajeroPwd(std::string auxiliar);
	Comando* construirEnlistador(std::string auxiliar);
	Comando* construirAgregador(std::string auxiliar);
	Comando* construirRemovedor(std::string auxiliar);
	Comando* construirUnknownCommand(std::string auxiliar);
};

#endif
