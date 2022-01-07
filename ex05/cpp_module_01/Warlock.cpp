#include "Warlock.hpp"

Warlock::Warlock(const std::string& name, const std::string& title):	name(name), title(title),
																		spells() {
	std::cout << name << ": This looks like another boring day." << std::endl;
}
Warlock::~Warlock() {
	std::cout << name << ": My job here is done!" << std::endl;
	std::map<std::string, ASpell*>::iterator it;
	for (it = spells.begin(); it != spells.end(); ++it) {
		delete it->second;
	}
	this->spells.clear();
}

void Warlock::introduce() const {
	std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}

const std::string& Warlock::getName() const {
	return this->name;
}

const std::string& Warlock::getTitle() const {
	return this->title;
}

void Warlock::setTitle(const std::string& title) {
	this->title = title;
}

void Warlock::learnSpell(ASpell* spell) {
	this->spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(const std::string& name) {
	if (spells.count(name)) {
		delete spells[name];
		spells.erase(name);
	}
}

void Warlock::launchSpell(const std::string& name, const ATarget& target) {
	if (spells.count(name)) {
		spells[name]->launch(target);
	}
}

