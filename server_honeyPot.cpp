#include "server_honeyPot.h"

#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#define COMANDOUNKOWN "UNKNOWN"
/*****************************************
 * 		FUNCIONES AUXILIARES			 *
 *****************************************/
static std::map<std::string,fabricador> crear_fabricas(){
	std::map<std::string,fabricador> fabricas;
	fabricas["USER"] = &FabricaDeComandos::construirVerificadorUsuario;
	fabricas["PASS"] = &FabricaDeComandos::construirVerificadorContrasenia;
	fabricas["SYST"] = &FabricaDeComandos::construirMensajeroSyst;
	fabricas["HELP"] = &FabricaDeComandos::construirMensajeroHelp;
	fabricas["PWD"] = &FabricaDeComandos::construirMensajeroPwd;
	fabricas["LIST"] = &FabricaDeComandos::construirEnlistador;
	fabricas["MKD"] = &FabricaDeComandos::construirAgregador;
	fabricas["RMD"] = &FabricaDeComandos::construirRemovedor;
	fabricas[COMANDOUNKOWN] = &FabricaDeComandos::construirUnknownCommand;
	return fabricas;
}

static Comando* fabricar_comando(FabricaDeComandos &fabrica,
		std::map<std::string,fabricador> &fabricas,
		std::string argumento1, std::string argumento2){
	std::map<std::string,fabricador>::iterator iterador =
			fabricas.find(argumento1);
	if (iterador == fabricas.end()) {
		iterador = fabricas.find(COMANDOUNKOWN);
	}
	return (fabrica.*(iterador->second))(argumento2);
}

static Comando* crear_comando_correspondiente(std::string &linea,
		FabricaDeComandos &fabrica,
		std::map<std::string,fabricador> &fabricas){
	size_t pos = linea.find(' ');
	if (pos != std::string::npos){
		std::string argumento1;
		std::string argumento2;
		argumento1 = linea.substr(0,pos);
		argumento2 = linea.substr(pos + 1, linea.size());
		return fabricar_comando(fabrica, fabricas, argumento1, argumento2);
	}else{
		return fabricar_comando(fabrica, fabricas, linea, "");
	}
}

static void enviar_bienvenida(std::map<std::string,std::string> &configuracion,
		Socket &socket){
	std::string saludo = "220 " + configuracion.at("newClient") + "\n";
	socket.enviar(saludo.c_str(), saludo.size());
}

static void enviar_despedida(std::map<std::string,std::string> &configuracion,
		Socket &socket){
	std::string salida = "221 " + configuracion.at("quitSuccess") + '\n';
	socket.enviar(salida.c_str(), salida.size());
}
/*****************************************
 * 				PRIMITIVAS				 *
 *****************************************/
HoneyPot::HoneyPot(std::map<std::string,std::string> &configuracion,
		Socket socket, SetBloqueante &directorio):
		configuracion(configuracion), fabricas(crear_fabricas()),
		directorio(directorio), usuarioValido(false),
		contaseniaValida(false), socket(std::move(socket)), cerrado(false){
}

HoneyPot::~HoneyPot() {
	this->cerrar();
}

void HoneyPot::run(){
	try{
		FabricaDeComandos fabrica(this->configuracion, this->directorio);
		enviar_bienvenida(this->configuracion, this->socket);
		std::string linea;
		while (this->socket.recibir(linea) == 0){
			std::string lineaComando = linea.substr(0,linea.size()-1);
			if (lineaComando == "QUIT"){
				break;
			}
			Comando* comando = crear_comando_correspondiente(lineaComando,
					fabrica, this->fabricas);
			comando->ejecutar(this->usuarioValido, this->contaseniaValida, this->socket);
			delete comando;
			linea.clear();
		}
		enviar_despedida(this->configuracion, this->socket);
	}catch (std::exception &e){}
}

void HoneyPot::cerrar(){
	if (!this->cerrado){
		this->socket.cerrar();
		this->cerrado = true;
	}
}

bool HoneyPot::esta_cerrado(){
	return this->cerrado;
}
