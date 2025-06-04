#pragma once
#include "Domain.h"
#include "Action.h"
#include "Repository.h"

class ActionRemove : public Action {
private:
	Repository& repo;
	Dog removed_dog;
public:
	ActionRemove(Repository& repo, const Dog& dog) : repo(repo), removed_dog(dog) {}
	void execute_undo() override {
		repo.add_dog(removed_dog);
	}
	void execute_redo() override {
		repo.remove_dog(repo.find_dog(removed_dog.get_name(), removed_dog.get_breed()));
	}
};