#include "server_aceptadorDeClientes.h"
#include "server_setBloqueante.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include "server_honeyPot.h"

/*******************************************
 *          FUNCIONES AUXILIARES
 ******************************************/
static void eliminar_hilos_muertos(std::vector<Thread*> &servidoresFTP){
	std::vector<Thread*> aux;
	std::vector<Thread*>::iterator iterador = servidoresFTP.begin();
	for (; iterador != servidoresFTP.end(); ++iterador)
	if (!((HoneyPot*) *iterador)->esta_cerrado()){
		aux.push_back(*iterador);
	}else{
		(*iterador)->join();
		delete (*iterador);
	}
	servidoresFTP.swap(aux);
}

static void cerrar_hilos(std::vector<Thread*> &servidoresFTP){
    std::vector<Thread*>::iterator iterador = servidoresFTP.begin();
    for (; iterador != servidoresFTP.end(); ++iterador){
    	((HoneyPot*) *iterador)->cerrar();
    	(*iterador)->join();
    	delete (*iterador);
    }
}
/*******************************************
 * 				PRIMITIVAS				   *
 *******************************************/
AceptadorDeClientes::AceptadorDeClientes(Socket &socket,
		std::map<std::string,std::string> &configuracion):
		socket(socket), configuracion(configuracion){
}

AceptadorDeClientes::~AceptadorDeClientes() {
}

void AceptadorDeClientes::run(){
	SetBloqueante directorio;
	std::vector<Thread*> servidoresFTP;
	try{
		int resultado = this->socket.enlazar_y_escuchar();
		if (resultado == 1){
			return;
		}
		for (int i = 0; true; ++i){
			servidoresFTP.push_back(new HoneyPot(this->configuracion,
					this->socket.aceptar(), directorio));
			servidoresFTP[servidoresFTP.size() - 1]->start();
			eliminar_hilos_muertos(servidoresFTP);
		}
	}catch(std::exception &e){
		cerrar_hilos(servidoresFTP);
	}
}
