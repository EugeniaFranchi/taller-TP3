#include <iostream>
#include "server.h"

int main(int argc, char* argv[]) {
	Servidor servidor(argv[1], argv[2]);
	servidor.ejecutar();
}
