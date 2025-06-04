#pragma once
#include "Exception.h"
#include "TextFileRepository.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include "Action.h"		
#include <stack>
#include <algorithm>

class Service {
private:
	Repository* repo;
	std::stack<std::unique_ptr<Action>> undo_stack;
	std::stack<std::unique_ptr<Action>> redo_stack;
public:
	Service(Repository* repo) : repo(repo) {}
	~Service() { delete repo; }
	void add_ten_dogs() {
		Dog dog1 = Dog("Labrador", "Buddy", 3, "https://upload.wikimedia.org/wikipedia/commons/9/90/Labrador_Retriever_portrait.jpg");
		this->add_dog(dog1);
		Dog dog2 = Dog("Bulldog", "Clyde", 5, "https://upload.wikimedia.org/wikipedia/commons/1/13/Clyde_The_Bulldog.jpg");
		this->add_dog(dog2);
		Dog dog3 = Dog("Poodle", "Bella", 2, "https://upload.wikimedia.org/wikipedia/commons/d/d8/Poodle_Puppy_-_Green_eyes.jpg");
		this->add_dog(dog3);
		Dog dog4 = Dog("Beagle", "Charlie", 4, "https://upload.wikimedia.org/wikipedia/commons/d/d0/Beagle_puppy_Cadet_2.jpg");
		this->add_dog(dog4);
		Dog dog5 = Dog("German Shepherd", "Rocky", 6, "https://upload.wikimedia.org/wikipedia/commons/6/61/20110425_German_Shepherd_Dog_8505.jpg");
		this->add_dog(dog5);
		Dog dog6 = Dog("Golden Retriever", "Luna", 1, "https://upload.wikimedia.org/wikipedia/commons/f/f1/Golden_Retriever_2020_5.jpg");
		this->add_dog(dog6);
		Dog dog7 = Dog("French Bulldog", "Daisy", 3, "https://upload.wikimedia.org/wikipedia/commons/7/79/French_Bulldog_puppy_259A4145.jpg");
		this->add_dog(dog7);
		Dog dog8 = Dog("Rottweiler", "Thor", 7, "https://upload.wikimedia.org/wikipedia/commons/0/04/Rottweiler_kopf_2.jpg");
		this->add_dog(dog8);
		Dog dog9 = Dog("Cocker Spaniel", "Lucy", 4, "https://upload.wikimedia.org/wikipedia/commons/a/a7/English_Cocker_Spaniel_young.JPG");
		this->add_dog(dog9);
		Dog dog10 = Dog("Siberian Husky", "Milo", 5, "https://upload.wikimedia.org/wikipedia/commons/f/f0/Brown_eye_siberian_husky_2.jpg");
		this->add_dog(dog10);
	}
	void add_dog(Dog dog) {
		int index = repo->find_dog(dog.get_name(), dog.get_breed());
		if (index != -1)
			throw ValidationException("The dog already exists!\n");
		repo->add_dog(dog);
		std::unique_ptr<Action> dog_ptr = std::make_unique<ActionAdd>(*repo,dog);
		undo_stack.push(std::move(dog_ptr));
	}
	void remove_dog(std::string name, std::string breed) {
		int index = repo->find_dog(name, breed);
		if (index == -1)
			throw ValidationException("The dog does not exist!\n");
		Dog dog = repo->get_all_dogs()[index];
		std::unique_ptr<Action> dog_ptr = std::make_unique<ActionRemove>(*repo, dog);
		undo_stack.push(std::move(dog_ptr));
		repo->remove_dog(index);
	}

	void update_dog(std::string name, std::string breed, int age, std::string photograph, std::string new_name, std::string new_breed) {
		int index = repo->find_dog(name, breed);
		if (index == -1)
			throw ValidationException("The dog does not exist!\n");
		Dog dog = repo->get_all_dogs()[index];
		Dog updated_dog;
		repo->update_dog(name, breed, age, photograph, new_name, new_breed);
		if (new_name == "" && new_breed == "") {
			updated_dog = repo->get_all_dogs()[index];
		}
		else if (new_name == "") {
			int  i = repo->find_dog(name, new_breed);
			updated_dog = repo->get_all_dogs()[i];
		}
		else if (new_breed == "") {
			int  i = repo->find_dog(new_name, breed);
			updated_dog = repo->get_all_dogs()[i];
		}
		else {
			int  i = repo->find_dog(new_name, new_breed);
			updated_dog = repo->get_all_dogs()[i];
		}
		std::unique_ptr<Action> dog_ptr = std::make_unique<ActionUpdate>(*repo, dog,updated_dog);
		undo_stack.push(std::move(dog_ptr));
	}
	void validate_existance(std::string name, std::string breed) {
		int index = repo->find_dog(name, breed);
		if (index == -1)
			throw ValidationException("The dog does not exist!\n");
	}
	std::vector<Dog> get_all_dogs() {
		return repo->get_all_dogs();
	}
	void add_dog_to_adoption_list(Dog dog)
	{
		repo->add_dog_to_adoption(dog);
	}
	std::vector<Dog> filter_dogs(std::string given_breed, int given_age) {
		if (given_breed == "") {
			std::string any = "any";
			return repo->filter_dogs(any, given_age);
		}
		else return repo->filter_dogs(given_breed, given_age);
	}
	std::vector<Dog> get_adoption_list() {
		return repo->get_adoption_list();
	}
	int get_service_size() {
		return repo->get_size();
	}
	void save_adoption_list() {
		repo->save_adoption_list();
	}
	void undo() {
		if (undo_stack.empty()) {
			throw ValidationException("No more actions to undo!\n");
		}
		std::unique_ptr<Action> action = std::move(undo_stack.top());
		undo_stack.pop();
		action->execute_undo();
		redo_stack.push(std::move(action));
	}
	void redo() {
		if (redo_stack.empty()) {
			throw ValidationException("No more actions to redo!\n");
		}
		std::unique_ptr<Action> action = std::move(redo_stack.top());
		redo_stack.pop();
		action->execute_redo();
		undo_stack.push(std::move(action));
	}
};