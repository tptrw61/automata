#include "FiniteAutomata.h"




int FiniteAutomata::transition(Symbol symbol)
{
	StateVec sv = currentState;
	svClear(currentState);
	TransitionInput ti(0, symbol);
	TransitionMap::iterator tr;
	EpsilonTMap::iterator etr;

	for (int i = 0; i < stateCount; i++) {
		if (sv[i] == 0)
			continue;
		tr = transitionMap.find(ti.setState(i));
		if (tr != transitionMap.end())
			svOr(currentState, tr->second);
		etr = epsilonMap.find(i);
		if (etr != epsilonMap.end())
			svOr(currentState, etr->second);
	}
	return 0;
}

FiniteAutomata::FiniteAutomata() : FiniteAutomata(1)
{
}

FiniteAutomata::FiniteAutomata(int stateCount)
{
	if (stateCount <= 0)
		stateCount = 1;
	this->stateCount = stateCount;
	currentState.resize(stateCount);
	acceptStates.resize(stateCount);
	alphabet.insert(EPSILON);
}

FiniteAutomata::FiniteAutomata(std::initializer_list<std::string> il) : FiniteAutomata(il.size())
{
	const std::string *it = il.begin();
	for (int i = 0; it != il.end(); it++, i++)
		labelState(i, *it);
}


FiniteAutomata::~FiniteAutomata()
{
}

bool FiniteAutomata::test(const std::string& s)
{
	EpsilonTMap::iterator etr = epsilonMap.find(startState);
	svClear(currentState);
	currentState[startState] = 1;
	if (etr != epsilonMap.end())
		svOr(currentState, etr->second);
	for (int i = 0; i < s.size(); i++)
		transition(s[i]);
	svAnd(currentState, acceptStates);
	for (int i = 0; i < currentState.size(); i++)
		if (currentState[i])
			return true;
	return false;
}

bool FiniteAutomata::addRule(State startState, Symbol symbol, State endState)
{
	if (startState < 0 || startState >= stateCount || endState < 0 || endState >= stateCount)
		return false;
	if (alphabet.count(symbol) == 0)
		alphabet.insert(symbol);
	StateVec sv(stateCount);
	sv[endState] = 1;
	if (symbol == EPSILON) {
		svOr(sv, epsilonMap[startState]);
		epsilonMap[startState] = sv;
	}
	else {
		TransitionInput ti(startState, symbol);
		svOr(sv, transitionMap[ti]);
		transitionMap[ti] = sv;
	}
	return true;
}
bool FiniteAutomata::addRule(State startState, Symbol symbol, const std::string& endState)
{
	return addRule(startState, symbol, getState(endState));
}
bool FiniteAutomata::addRule(const std::string& startState, Symbol symbol, State endState)
{
	return addRule(getState(startState), symbol, endState);
}
bool FiniteAutomata::addRule(const std::string& startState, Symbol symbol, const std::string& endState)
{
	return addRule(getState(startState), symbol, getState(endState));
}

bool FiniteAutomata::setStartState(State state)
{
	if (state < 0 || state >= stateCount)
		return false;
	startState = 0;
	return true;
}
bool FiniteAutomata::setStartState(const std::string& state)
{
	return setStartState(getState(state));
}

bool FiniteAutomata::setAcceptState(State state, bool accept)
{
	if (state < 0 || state >= stateCount)
		return false;
	acceptStates[state] = accept;
	return true;
}
bool FiniteAutomata::setAcceptState(const std::string& state, bool accept)
{
	return setAcceptState(getState(state), accept);
}

bool FiniteAutomata::setStateCount(int stateCount)
{
	if (stateCount <= 0)
		return false;
	this->stateCount = stateCount;
}

int FiniteAutomata::addState(bool acceptState)
{
	currentState.push_back(0);
	acceptStates.push_back(acceptState);
	return stateCount++;
}

int FiniteAutomata::addState(const std::string& label, bool acceptState)
{
	int stateId = addState(acceptState);
	labelState(stateId, label);
	return stateId;
}

bool FiniteAutomata::labelState(State state, const std::string& label)
{
	if (state < 0 || state >= stateCount || label.size())
		return false;
	stateLabels[label] = state;
	return true;
}

State FiniteAutomata::getState(const std::string& label)
{
	auto it = stateLabels.find(label);
	if (it != stateLabels.end())
		return it->second;
	return NO_STATE;
}

std::string FiniteAutomata::getAlphabet()
{
	std::string s;
	for (Symbol symbol : alphabet)
		if (symbol != EPSILON)
			s.push_back(symbol);
	return s;
}

/*
std::string FiniteAutomata::getRegex()
{
	return std::string();
}
// */
