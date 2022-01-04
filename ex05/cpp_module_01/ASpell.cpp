#include "ASpell.hpp"

ASpell::ASpell(): name(), effects() {}

ASpell::ASpell(const std::string& name, const std::string& effects):
	name(name),
	effects(effects) {}

ASpell::~ASpell() {}

ASpell::ASpell(const ASpell& other) {
	*this = other;
}

ASpell& ASpell::operator=(const ASpell& other) {
	if (this != &other) {
		this->name = other.name;
		this->effects = other.effects;
	}
	return *this;
}

const std::string& ASpell::getName() const {
	return this->name;
}

const std::string& ASpell::getEffects() const {
	return this->effects;
}

void ASpell::launch(const ATarget& target) const {
	target.getHitBySpell(*this);
}