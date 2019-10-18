#include "server_setBloqueante.h"
#include <string>
#include <set>

SetBloqueante::SetBloqueante(){
}

SetBloqueante::~SetBloqueante() {
}

int SetBloqueante::agregar(std::string elemento){
	std::unique_lock<std::mutex> lock(this->m);
	bool incluyeElemento = (this->set.find(elemento) != this->set.end());
	if (incluyeElemento){
		return 1;
	}
	this->set.insert(elemento);
	return 0;
}

int SetBloqueante::remover(std::string elemento){
	std::unique_lock<std::mutex> lock(this->m);
	bool incluyeElemento = (this->set.find(elemento) != this->set.end());
	if (!incluyeElemento){
		return 1;
	}
	this->set.erase(elemento);
	return 0;
}

std::set<std::string>::iterator SetBloqueante::inicio(){
	return this->set.begin();
}

std::set<std::string>::iterator SetBloqueante::fin(){
	return this->set.end();
}
