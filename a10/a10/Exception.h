#pragma once
#include <exception>
#include <string>
class ValidationException : public std::exception {
private:
	std::string message;

public:
	ValidationException(const std::string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}

};

class FileException : public std::exception {
private:
	std::string message;
public:
	FileException(const std::string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

