#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <exception>
#include <stdexcept>
#include <string>

#define ERRORGETADDRINFO "Error en getaddrinfo."
#define ERRORBIND "Error en bind."
#define ERRORLISTEN "Error en listen."
#define ERRORCREACION "Error al crear el socket."
#define ERRORACCEPT "Error en accept."
#define ERRORENVIAR "Error al enviar."
#define ERRORRECIBIR "Error al recibir."
#define ERRORCONNECT "Error en connect."
/*******************************************
 *          FUNCIONES AUXILIARES
 ******************************************/

void preparar_hints(struct addrinfo *hints){
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}

struct addrinfo *obtener_ptr(const char *hostname, const char *servicio){
	struct addrinfo *ptr;
	struct addrinfo hints;
	preparar_hints(&hints);
	int s = getaddrinfo(hostname, servicio, &hints, &ptr);
	if (s != 0){
		throw std::runtime_error(ERRORGETADDRINFO);
	}
	return ptr;
}

int enlazar(struct addrinfo *direccion, int fd){
	struct addrinfo *aux = direccion;
	bool estaEnlazado = false;
	for (; aux != NULL && estaEnlazado == false; aux = aux->ai_next){
		int s = bind(fd, aux->ai_addr, aux->ai_addrlen);
		if (s == -1){
			throw std::runtime_error(ERRORBIND);
		}
		estaEnlazado = (s != -1);
	}
	return 0;
}

int escuchar(int fd){
	int s = listen(fd, 1);
	if (s == -1){
		throw std::runtime_error(ERRORLISTEN);
	}
	return 0;
}

/*******************************************
 *          PRIMITIVAS SOCKET
 ******************************************/

Socket::Socket(const char *hostname, const char *servicio) {
	int fd = 0;
	struct addrinfo * addr;
	struct addrinfo *ptr = obtener_ptr(hostname, servicio);
	if (ptr == NULL){
		throw std::runtime_error(ERRORCREACION);
	}

	for (addr = ptr; addr != NULL; addr = addr->ai_next){
		fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		if (fd == -1){
			freeaddrinfo(ptr);
			throw std::runtime_error(ERRORCREACION);
		}
	}
	this->fd = fd;
	this->direccion = ptr;

	int val = 1;
	int s = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (s == -1){
		throw std::runtime_error(ERRORCREACION);
	}
}

Socket::Socket(int fd): fd(fd), direccion(nullptr){
}

Socket::Socket(Socket&& otro): fd(otro.fd),
		direccion(otro.direccion){
	otro.direccion = nullptr;
	otro.fd = 0;
}

int Socket::enlazar_y_escuchar(){
	int s1 = enlazar(this->direccion, this->fd);
	if (s1){
		return 1;
	}
	int s2 = escuchar(this->fd);
	if (s2){
		return 1;
	}
	return 0;
}

Socket Socket::aceptar(){
	int cliente = accept(this->fd, NULL, NULL);
	if (cliente < 0){
		throw std::runtime_error(ERRORACCEPT);
	}
	return std::move(Socket(cliente));
}

int Socket::enviar(const char* buffer, ssize_t largo){
	ssize_t largoEnviados = 0;
	while (largoEnviados < largo) {
		ssize_t s = send(this->fd,
				&buffer[largoEnviados],
				largo - largoEnviados,
				MSG_NOSIGNAL);
		if (s <= 0){
			throw std::runtime_error(ERRORENVIAR);
		}
		largoEnviados += s;
	}
	return 0;
}

int Socket::recibir(std::string &linea){
	char buffer[1];
	memset(buffer, 0, 1);
	while (buffer[0] != '\n'){
		ssize_t s = recv(this->fd,
				&buffer[0],
				1,
				0);
		if (s == -1){
			throw std::runtime_error(ERRORRECIBIR);
		}
		if (s == 0){
			throw std::runtime_error(ERRORRECIBIR);
		}
		linea += buffer;
	}
	return 0;
}

void Socket::conectar(){
	struct addrinfo *aux = this->direccion;
	bool estaConectado = false;
	for (; aux != NULL && estaConectado == false; aux = aux->ai_next){
		int s = connect(this->fd,
				this->direccion->ai_addr,
				this->direccion->ai_addrlen);
		if (s == -1) {
			close(this->fd);
			throw std::runtime_error(ERRORCONNECT);
		}
		estaConectado = (s != -1);
	}
}

void Socket::cerrar(){
	if (this->fd > 0){
		shutdown(this->fd, SHUT_RDWR);
		close(this->fd);
	}
}

Socket::~Socket() {
	this->cerrar();
	if (this->direccion != nullptr){
		freeaddrinfo(this->direccion);
	}
}

