#pragma once
#include "Domain.h"
#include "Action.h"
#include "Repository.h"

class ActionUpdate : public Action {
private:
	Repository& repo;
	Dog updated_dog;
	Dog after_update_dog;
public:
	ActionUpdate(Repository& repo, const Dog& dog, const Dog& after_dog) : repo(repo), updated_dog(dog), after_update_dog(after_dog) {}
	void execute_undo() override {
		std::string name = updated_dog.get_name();
		std::string breed = updated_dog.get_breed();
		std::string photograph = updated_dog.get_photograph();
		std::string new_name = updated_dog.get_name();
		std::string new_breed = updated_dog.get_breed();
		repo.update_dog(name, breed, updated_dog.get_age(), photograph, new_name, new_breed);
	}
	void execute_redo() override {
		std::string name = after_update_dog.get_name();
		std::string breed = after_update_dog.get_breed();
		std::string photograph = after_update_dog.get_photograph();
		std::string new_name = after_update_dog.get_name();
		std::string new_breed = after_update_dog.get_breed();
		repo.update_dog(name, breed, after_update_dog.get_age(), photograph, new_name, new_breed);
	}
};