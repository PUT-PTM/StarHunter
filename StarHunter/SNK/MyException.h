#pragma once

#include <string>

class MyException{
private:
	std::string message;
public:
	MyException(std::string message);
	std::string getMessage();
};