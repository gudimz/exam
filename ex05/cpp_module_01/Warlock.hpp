#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>
#include <map>
#include "ASpell.hpp"

class Warlock {
private:
	std::string name;
	std::string title;
	std::map<std::string, ASpell*> spells;
public:
	Warlock();
	Warlock(const Warlock& other);
	~Warlock();
	Warlock& operator=(const Warlock& other);
	Warlock(const std::string& name, const std::string& title);
	const std::string& getName(void) const;
	const std::string& getTitle(void) const;
	void setTitle(const std::string& title);
	void introduce(void) const;
	void learnSpell(ASpell* spell);
	void forgetSpell(const std::string& name);
	void launchSpell(const std::string& name, const ATarget& target);
};

#endif