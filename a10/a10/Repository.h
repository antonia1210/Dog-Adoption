#pragma once
#pragma once
#include "Domain.h"
#include "Exception.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Repository
{
protected:
	std::vector<Dog> dogs;
	std::vector<Dog> adoption_list;

public:
	Repository() {}
	~Repository() {};
	virtual int find_dog(const std::string& name, const std::string& breed) const = 0;
	virtual void add_dog(const Dog dog) = 0;
	virtual std::vector<Dog> get_all_dogs() = 0;
	virtual void remove_dog(int index) = 0;
	virtual void update_dog(std::string& name, std::string& breed, int age, std::string& photograph, std::string& new_name, std::string& new_breed) = 0;
	void add_dog_to_adoption(Dog dog) {
		adoption_list.push_back(dog);
	}
	std::vector<Dog> filter_dogs(std::string& given_breed, int given_age) {
		std::vector<Dog> filtered_dogs;
		for (const Dog& dog : dogs)
		{
			if ((dog.get_breed() == given_breed || given_breed == "any") && dog.get_age() < given_age) {
				filtered_dogs.push_back(dog);
			}
		}
		return filtered_dogs;
	}
	std::vector<Dog> get_adoption_list() { return adoption_list; }
	int get_size() { return dogs.size(); }
	virtual void save_adoption_list() = 0;
};