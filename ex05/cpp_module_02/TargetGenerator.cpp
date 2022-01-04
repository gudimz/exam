#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(): targets() {}

TargetGenerator::~TargetGenerator() {
	std::map<std::string, ATarget*>::iterator it;
	for (it = targets.begin(); it != targets.end(); ++it) {
		delete it->second;
	}
	this->targets.clear();
}

void TargetGenerator::learnTargetType(ATarget* target) {
	this->targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(std::string const& type) {
	std::map<std::string, ATarget*>::iterator it;
	it = targets.find(type);
	if (it != targets.end()) {
		delete it->second;
		targets.erase(it);
	}
}

ATarget* TargetGenerator::createTarget(std::string const& type) {
	if (targets.count(type)) {
		return targets[type];
	}
	return 0;
}