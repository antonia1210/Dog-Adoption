#pragma once
#include "Repository.h"
#include <fstream>

class HTMLFileRepository : public Repository {
private:
	std::string file_name;
public:
	HTMLFileRepository(const std::string& file_name) :file_name(file_name) {}
	~HTMLFileRepository() {}
	void save_adoption_list() override {
		std::ofstream outfile(file_name);
		if (!outfile.is_open()) throw FileException("Could not open HTML file.");

		outfile << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
		outfile << "<table border='1'><tr><th>Breed</th><th>Name</th><th>Age</th><th>Photo</th></tr>\n";
		for (const Dog& dog : adoption_list) {
			outfile << dog.to_HTML() << "\n";
		}
		outfile << "</table></body></html>\n";
		outfile.close();
	}
	void add_dog(const Dog) override {}
	void remove_dog(int) override {}
	void update_dog(std::string&, std::string&, int, std::string&, std::string&, std::string&) override {}
	std::vector<Dog> get_all_dogs() override { return std::vector<Dog>(); }
	int find_dog(const std::string& name, const std::string& breed) const override { return -1; }
};