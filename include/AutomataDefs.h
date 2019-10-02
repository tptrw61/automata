#pragma once
#include <string>
#include <set>


using State = int;
using Symbol = int;

const Symbol EPSILON = 0xffff;
const State NO_STATE = -1;

class Automata {
protected:
	using StateSet = std::set<State>;

	void addStateSet(StateSet& dest, const StateSet& rhs);
public:
	Automata();
	virtual ~Automata();
	virtual bool test(const std::string& s) = 0;
};
