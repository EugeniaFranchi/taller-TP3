#ifndef SERVER_ENLISTADOR_H_
#define SERVER_ENLISTADOR_H_
#include <string>
#include <set>

#include "server_comando.h"
#include "server_setBloqueante.h"

class Enlistador: public Comando {
private:
	int codigoInicio;
	std::string inicio;
	int codigoFin;
	std::string fin;
	int codigoNoInicio;
	std::string mensajeNoInicio;
	std::string numerador;
	SetBloqueante &directorio;

public:
	Enlistador(int codigoInicio, std::string inicio,
			int codigoFin, std::string fin, int codigoNoInicio,
			std::string mensajeNoInicio,
			std::string numerador, SetBloqueante &directorio);
	virtual ~Enlistador();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
