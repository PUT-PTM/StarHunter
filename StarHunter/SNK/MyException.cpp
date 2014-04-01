#include "MyException.h"

MyException::MyException(std::string message){
	this->message = message;
}

std::string MyException::getMessage(){
	return message;
}