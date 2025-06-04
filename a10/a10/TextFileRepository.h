#pragma once
#include "Repository.h"
#include <fstream>
#include <string>

class TextFileRepository : public Repository {
private:
	std::string file_name;
public:
	TextFileRepository(const std::string& file_name) :file_name(file_name) {
		load_from_file();
	}
	~TextFileRepository() {}
	void load_from_file() {
		std::ifstream infile(file_name);
		if (!infile.is_open()) {
			throw FileException("Could not open file: " + file_name);
		}
		std::vector<Dog> dogs_from_file;
		Dog dog;
		while (infile >> dog) {
			dogs_from_file.push_back(dog);
		}
		for (const Dog& dog : dogs_from_file) {
			this->add_dog(dog);
		}
		infile.close();
	}
	void save_to_file() {
		std::ofstream outfile(file_name);
		if (!outfile.is_open()) {
			throw FileException("Could not open file: " + file_name);
		}
		std::vector<Dog> dogs = this->get_all_dogs();
		for (const Dog& dog : dogs) {
			outfile << dog;
		}
		outfile.close();
	}
	void add_dog(const Dog dog) {
		dogs.push_back(dog);
		save_to_file();
	}
	void remove_dog(int index) {
		dogs.erase(dogs.begin() + index);
		save_to_file();
	}
	int find_dog(const std::string& name, const std::string& breed) const
	{
		auto it = std::find_if(dogs.begin(), dogs.end(), [&](const Dog& dog) {return dog.get_name() == name && dog.get_breed() == breed; });
		if (it != dogs.end()) {
			return std::distance(dogs.begin(), it);
		}
		return -1;
	}
	void update_dog(std::string& name, std::string& breed, int age, std::string& photograph, std::string& new_name, std::string& new_breed) {
		int index = find_dog(name, breed);
		if (age != 0) {
			this->dogs[index].set_age(age);
		}
		if (photograph != "") {
			this->dogs[index].set_photograph(photograph);
		}
		if (new_name != "") {
			this->dogs[index].set_name(new_name);
		}
		if (new_breed != "") {
			this->dogs[index].set_breed(new_breed);
		}
		save_to_file();
	}
	void save_adoption_list() override {
		std::ofstream outfile("adoption_list.txt");
		if (!outfile.is_open()) {
			throw FileException("Could not open file: adoption_list.txt");
		}
		for (const Dog& dog : adoption_list) {
			outfile << dog.to_string() << "\n";
		}
		outfile.close();
	}
	std::vector<Dog> get_all_dogs() {
		return dogs;
	}
};