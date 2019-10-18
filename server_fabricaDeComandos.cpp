#include "server_fabricaDeComandos.h"

#include <iostream>

#include "server_agregador.h"
#include "server_enlistador.h"
#include "server_mensajero.h"
#include "server_removedor.h"
#include "server_verificadorContrasenia.h"
#include "server_verificadorUsuario.h"
#include <map>
#include <string>

#define CODIGOPASSREQUIRED 331
#define CODIGOLOGINSUCCESS 230
#define CODIGOLOGINFAILED 530
#define CODIGOCLIENTNOTLOGGED 530
#define CODIGOSYSTEMINFO 215
#define CODIGOCOMMANDS 214
#define CODIGOCURRENTDIRECTORYMSG 257
#define CODIGOLISTBEGIN 150
#define CODIGOLISTEND 226
#define CODIGOMKDSUCCESS 257
#define CODIGOMKDFAILED 550
#define CODIGORMDSUCCESS 250
#define CODIGORMDFAILED 550
#define CODIGOUNKNOWNCOMMAND 530

FabricaDeComandos::FabricaDeComandos(std::map<std::string,
		std::string> &configuracion, SetBloqueante &directorio)
		: configuracion(configuracion), directorio(directorio){
}

FabricaDeComandos::~FabricaDeComandos() {
}

Comando* FabricaDeComandos::construirVerificadorUsuario(std::string auxiliar){
	return new VerificadorUsuario(this->configuracion.at("user"),
			CODIGOPASSREQUIRED, this->configuracion.at("passRequired"),
			auxiliar);
}

Comando* FabricaDeComandos::construirVerificadorContrasenia(
		std::string auxiliar){
	return new VerificadorContrasenia( this->configuracion.at("password"),
			auxiliar,
			CODIGOLOGINSUCCESS,
			this->configuracion.at("loginSuccess"),
			CODIGOLOGINFAILED,
			this->configuracion.at("loginFailed"));
}

Comando* FabricaDeComandos::construirMensajeroSyst(std::string auxiliar){
	return new Mensajero(CODIGOSYSTEMINFO,
			this->configuracion.at("systemInfo"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"));
}

Comando* FabricaDeComandos::construirMensajeroHelp(std::string auxiliar){
	return new Mensajero(CODIGOCOMMANDS,
			this->configuracion.at("commands"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"));
}

Comando* FabricaDeComandos::construirMensajeroPwd(std::string auxiliar){
	return new Mensajero(CODIGOCURRENTDIRECTORYMSG,
			this->configuracion.at("currentDirectoryMsg"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"));
}

Comando* FabricaDeComandos::construirEnlistador(std::string auxiliar){
	return new Enlistador(CODIGOLISTBEGIN,
			this->configuracion.at("listBegin"),
			CODIGOLISTEND,
			this->configuracion.at("listEnd"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"),
			"drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34",
			this->directorio);
}

Comando* FabricaDeComandos::construirAgregador(std::string auxiliar){
	return new Agregador(CODIGOMKDSUCCESS,
			this->configuracion.at("mkdSuccess"),
			CODIGOMKDFAILED,
			this->configuracion.at("mkdFailed"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"),
			auxiliar,
			this->directorio);
}

Comando* FabricaDeComandos::construirRemovedor(std::string auxiliar){
	return new Removedor(CODIGORMDSUCCESS,
			this->configuracion.at("rmdSuccess"),
			CODIGORMDFAILED,
			this->configuracion.at("rmdFailed"),
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"),
			auxiliar,
			this->directorio);
}

Comando* FabricaDeComandos::construirUnknownCommand(std::string auxiliar){
	return new Mensajero(CODIGOUNKNOWNCOMMAND,
			"Unknown command.",
			CODIGOCLIENTNOTLOGGED,
			this->configuracion.at("clientNotLogged"));
}
