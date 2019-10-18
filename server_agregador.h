#ifndef SERVER_AGREGADOR_H_
#define SERVER_AGREGADOR_H_
#include <string>
#include <set>
#include "server_comando.h"
#include "server_setBloqueante.h"

class Agregador: public Comando {
private:
	int codigoExito;
	std::string mensajeExito;
	int codigoFracaso;
	std::string mensajeFracaso;
	int codigoNoIniciado;
	std::string mensajeNoInicio;
	std::string aAgregar;
	SetBloqueante &directorio;
public:
	Agregador(int codigoExito, std::string mensajeExito, int codigoFracaso,
			std::string mensajeFracaso, int codigoNoIniciado,
			std::string mensajeNoInicio, std::string aAgregar,
			SetBloqueante &directorio);
	virtual ~Agregador();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
