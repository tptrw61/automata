#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <initializer_list>
#include "AutomataDefs.h"


class FiniteAutomata : public Automata
{
public:
private:
	struct TransitionInput {
		State state;
		Symbol symbol;
		TransitionInput() {}
		TransitionInput(State _state, Symbol _symbol) : state(_state), symbol(_symbol) {}
		TransitionInput& setState(State _state) { state = _state; return *this; }
		bool operator==(const TransitionInput &rhs) const { return state == rhs.state && symbol == rhs.symbol; }
		bool operator!=(const TransitionInput &rhs) const { return !(*this == rhs); }
		bool operator>(const TransitionInput &rhs) const { if (state == rhs.state) return symbol > rhs.symbol; return state > rhs.state; }
		bool operator>=(const TransitionInput &rhs) const { return *this == rhs || *this > rhs; }
		bool operator<(const TransitionInput &rhs) const { return !(*this >= rhs); }
		bool operator<=(const TransitionInput &rhs) const { return !(*this > rhs); }
	};
	
	using TransitionMap = std::map<TransitionInput, StateVec>;
	using EpsilonTMap = std::map<State, StateVec>;

	int stateCount;
	int startState;
	StateVec acceptStates;
	StateVec currentState;
	std::set<Symbol> alphabet;

	TransitionMap transitionMap;
	EpsilonTMap epsilonMap;

	std::map<std::string, int> stateLabels;

	int transition(Symbol symbol);

	
public:

	FiniteAutomata();
	FiniteAutomata(int stateCount);
	FiniteAutomata(std::initializer_list<std::string> il);
	~FiniteAutomata();

	virtual bool test(const std::string& s);

	bool addRule(State startState, Symbol symbol, State endState);
	bool addRule(State startState, Symbol symbol, const std::string& endState);
	bool addRule(const std::string& startState, Symbol symbol, State endState);
	bool addRule(const std::string& startState, Symbol symbol, const std::string& endState);
	bool setStartState(State state);
	bool setStartState(const std::string& state);
	bool setAcceptState(State state, bool accept = 1);
	bool setAcceptState(const std::string& state, bool accept = 1);

	bool setStateCount(int stateCount);
	int addState(bool acceptState = 0);
	int addState(const std::string& label, bool acceptState = 0);

	bool labelState(State state, const std::string& label);
	State getState(const std::string& label);

	std::string getAlphabet();

	//std::string getRegex();
};

