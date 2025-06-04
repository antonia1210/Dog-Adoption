#pragma once
#include "Domain.h"
#include "Exception.h"
class DogValidator
{
public:
	void validate(const Dog& dog) {
		if (dog.get_age() < 0) {
			throw ValidationException("The age cannot be negative!\n");
		}
		if (dog.get_name().empty()) {
			throw ValidationException("The name cannot be empty!\n");
		}
		if (dog.get_breed().empty()) {
			throw ValidationException("The breed cannot be empty!\n");
		}
		if (dog.get_photograph().empty()) {
			throw ValidationException("The photograph link cannot be empty!\n");
		}
	}
	void validate_(const std::string& name, const std::string& breed) {
		if (name.empty()) {
			throw ValidationException("The name cannot be empty!\n");
		}
		if (breed.empty()) {
			throw ValidationException("The breed cannot be empty!\n");
		}
	}
	void validate_age_breed(const std::string& breed, int age) {
		if (age < 0) {
			throw ValidationException("The age cannot be negative!\n");
		}
		if (breed.empty()) {
			throw ValidationException("The breed cannot be empty!\n");
		}
	}
};
