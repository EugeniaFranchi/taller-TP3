#ifndef SERVER_REMOVEDOR_H_
#define SERVER_REMOVEDOR_H_
#include <string>
#include <set>
#include "server_comando.h"
#include "server_setBloqueante.h"

class Removedor: public Comando {
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
	Removedor(int codigoExito, std::string mensajeExito, int codigoFracaso,
			std::string mensajeFracaso, int codigoNoIniciado,
			std::string mensajeNoInicio, std::string aAgregar,
			SetBloqueante &directorio);
	virtual ~Removedor();

	virtual int ejecutar(bool &usuarioValido, bool &contaseniaValida,
			Socket &socket);
};

#endif
