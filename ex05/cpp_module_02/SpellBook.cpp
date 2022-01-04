#include "SpellBook.hpp"

SpellBook::SpellBook(): spells() {}

SpellBook::~SpellBook() {
	std::map<std::string, ASpell*>::iterator it;
	for (it = spells.begin(); it != spells.end(); ++it) {
		delete it->second;
	}
	this->spells.clear();
}

void SpellBook::learnSpell(ASpell* spell) {
	this->spells[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(std::string const& name) {
	std::map<std::string, ASpell*>::iterator it;
	it = spells.find(name);
	if (it != spells.end()) {
		delete it->second;
		spells.erase(it);
	}
}

ASpell* SpellBook::createSpell(std::string const& name) {
	if (spells.count(name)) {
		return spells[name];
	}
	return 0;
}