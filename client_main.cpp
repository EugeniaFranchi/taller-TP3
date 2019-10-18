#include <iostream>
#include "client.h"

int main(int argc, char* argv[]) {
	Cliente cliente(argv[1], argv[2]);
	cliente.ejecutar();
}
