#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_
#include <sys/types.h>
#include <string>
#include <mutex>

class Socket {
private:
	int fd;
	struct addrinfo *direccion;

public:
	Socket(const char *hostname, const char *servicio);
	Socket(Socket&& otro);
	virtual ~Socket();
	int enlazar_y_escuchar();
	Socket aceptar();
	int enviar(const char* buffer, ssize_t largo);
	int recibir(std::string &linea);
	void conectar();
	void cerrar();
private:
	explicit Socket(int fd);
};

#endif
