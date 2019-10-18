#ifndef SERVIDOR_SERVER_SETBLOQUEANTE_H_
#define SERVIDOR_SERVER_SETBLOQUEANTE_H_
#include <string>
#include <set>
#include <mutex>

class SetBloqueante {
private:
	std::set<std::string> set;
	std::mutex m;

public:
	SetBloqueante();
	virtual ~SetBloqueante();

	int agregar(std::string elemento);
	int remover(std::string elemento);
	std::set<std::string>::iterator inicio();
	std::set<std::string>::iterator fin();
};

#endif
