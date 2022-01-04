#include "Warlock.hpp"

Warlock::Warlock(const std::string& name, const std::string& title):	name(name), title(title),
																		book() {
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
	std::cout << name << ": My job here is done!" << std::endl;
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
	book.learnSpell(spell);
}

void Warlock::forgetSpell(const std::string& name) {
	book.forgetSpell(name);
}

void Warlock::launchSpell(const std::string& name, const ATarget& target) {
	ASpell* newSpell = book.createSpell(name);
	if (newSpell) {
		target.getHitBySpell(*newSpell);
	}
}