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
	if (!spells.count(spell->getName())) {
		this->spells[spell->getName()] = spell->clone();
	}
}

void SpellBook::forgetSpell(std::string const& name) {
	if (spells.count(name)) {
		delete spells[name];
		spells.erase(name);
	}
}

ASpell* SpellBook::createSpell(std::string const& name) {
	if (spells.count(name)) {
		return spells[name];
	}
	return 0;
}