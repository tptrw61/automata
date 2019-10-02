#pragma once
#include <string>
#include <vector>


using State = int;
using Symbol = int;


class Automata {
protected:
	using StateVec = std::vector<bool>;

	void svOr(StateVec& dest, const StateVec& sv);
	void svAnd(StateVec& dest, const StateVec& sv);
	void svXor(StateVec& dest, const StateVec& sv);
	void svNot(StateVec& sv);
	void svSet(StateVec& sv, bool state);
	void svClear(StateVec& sv);
public:
	const Symbol EPSILON = 0xffff;
	const State NO_STATE = -1;

	Automata();
	virtual ~Automata();
	virtual bool test(const std::string& s) = 0;
};
