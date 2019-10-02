#pragma once
#include <string>
#include <set>


using Symbol = int;

const Symbol EPSILON = 0xffff;

class Automata {
public:
	Automata();
	virtual ~Automata();
	virtual bool test(const std::string& s) = 0;
};
