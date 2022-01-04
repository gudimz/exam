#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

#include <iostream>
#include <map>
#include "ATarget.hpp"

class TargetGenerator {
private:
	std::map<std::string, ATarget*> targets;
	TargetGenerator(const TargetGenerator& other);
	TargetGenerator& operator=(const TargetGenerator& other);
public:
	TargetGenerator();
	~TargetGenerator();
	void learnTargetType(ATarget*);
	void forgetTargetType(std::string const &);
	ATarget* createTarget(std::string const &);
};

#endif