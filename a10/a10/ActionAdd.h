#pragma once
#include "Domain.h"
#include "Action.h"
#include "Repository.h"

class ActionAdd : public Action {
private:
	Repository& repo;
	Dog added_dog;
public:
	ActionAdd(Repository& repo, const Dog& dog) : repo(repo), added_dog(dog) {}
	void execute_undo() override {
		repo.remove_dog(repo.find_dog(added_dog.get_name(), added_dog.get_breed()));
	}
	void execute_redo() override {
		repo.add_dog(added_dog);
	}
};