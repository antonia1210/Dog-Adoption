#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Dog
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;

public:
	Dog(const std::string& breed, const std::string& name, int age, const std::string& photograph) { this->breed = breed; this->name = name; this->age = age; this->photograph = photograph;; }
	std::string get_breed() const { return this->breed; }
	void set_breed(std::string new_breed) { this->breed = new_breed; }
	std::string get_name() const { return this->name; }
	void set_name(std::string new_name) { this->name = new_name; }
	int get_age() const { return this->age; }
	void set_age(int new_age) { this->age = new_age; }
	std::string get_photograph() const { return this->photograph; }
	void set_photograph(std::string new_link) { this->photograph = new_link; }
	std::string to_string() const { return "Name: " + name + " Breed: " + breed + " Age: " + std::to_string(age) + " Photograph link: " + photograph; }
	Dog() { this->breed = ""; this->name = ""; this->age = 0; this->photograph = ""; }

	friend std::istream& operator>>(std::istream& in, Dog& dog) {
		std::getline(in, dog.breed);
		std::getline(in, dog.name);
		in >> dog.age;
		in.ignore();
		std::getline(in, dog.photograph);
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Dog& dog) {
		out << dog.breed << "\n" << dog.name << "\n" << dog.age << "\n" << dog.photograph << "\n";
		return out;
	}
	std::string to_CSV() const
	{
		return this->name + "," + this->breed + "," + std::to_string(age) + "," + this->photograph;
	}
	std::string to_HTML() const
	{
		return "<tr><td>" + name + "</td><td>" + breed + "</td><td>" + std::to_string(age) + "</td><td><a href=\"" + photograph + "\">Photo</a></td></tr>";
	}
};
