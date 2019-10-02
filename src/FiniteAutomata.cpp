#include "FiniteAutomata.h"
#include <vector>
#include <queue>


void FiniteAutomata::transition(Symbol symbol) {
	StateSet sset = currentState;
	currentState.clear();
	TransitionInput ti(0, symbol);

	for (State state : sset) {
		addStateSet(currentState, transitionMap[ti.setState(state)]);
	}
	epsilonTransition();
}
void FiniteAutomata::epsilonTransition() {
	std::queue<State> epq;
	std::vector<bool> check(stateCount);
	for (State state : currentState) {
		epq.push(state);
	}
	State state;
	while (!epq.empty()) {
		state = epq.front();
		epq.pop();
		if (check[state])
			continue;
		check[state] = true;
		addStateSet(currentState, epsilonMap[state]);
		for (State st : epsilonMap[state]) {
			if (check[st])
				continue;
			epq.push(st);
		}
	}
}

void FiniteAutomata::addStateSet(StateSet& dest, const StateSet& rhs) {
	for (State state : rhs)
		dest.insert(state);
}

FiniteAutomata::FiniteAutomata() : FiniteAutomata(1) {  }

FiniteAutomata::FiniteAutomata(int stateCount) {
	if (stateCount <= 0)
		stateCount = 1;
	this->stateCount = stateCount;
	alphabet.insert(EPSILON);
}

FiniteAutomata::FiniteAutomata(std::initializer_list<std::string> il) : FiniteAutomata(il.size()) {
	const std::string *it = il.begin();
	for (int i = 0; it != il.end(); it++, i++)
		labelState(i, *it);
}


FiniteAutomata::~FiniteAutomata() {  }

bool FiniteAutomata::test(const std::string& s) {
	currentState.clear();
	currentState.insert(startState);
	epsilonTransition();
	for (size_t i = 0; i < s.size(); i++)
		transition(s[i]);
	for (State state : currentState)
		if (acceptStates.count(state) > 0)
			return true;
	return false;
}

bool FiniteAutomata::addRule(State startState, Symbol symbol, State endState) {
	if (startState < 0 || startState >= stateCount || endState < 0 || endState >= stateCount)
		return false;
	if (alphabet.count(symbol) == 0)
		alphabet.insert(symbol);
	if (symbol == EPSILON) {
		epsilonMap[startState].insert(endState);
	}
	else {
		TransitionInput ti(startState, symbol);
		transitionMap[ti].insert(endState);
	}
	return true;
}
bool FiniteAutomata::addRule(State startState, Symbol symbol, const std::string& endState) {
	return addRule(startState, symbol, getState(endState));
}
bool FiniteAutomata::addRule(const std::string& startState, Symbol symbol, State endState) {
	return addRule(getState(startState), symbol, endState);
}
bool FiniteAutomata::addRule(const std::string& startState, Symbol symbol, const std::string& endState) {
	return addRule(getState(startState), symbol, getState(endState));
}

bool FiniteAutomata::setStartState(State state) {
	if (state < 0 || state >= stateCount)
		return false;
	startState = 0;
	return true;
}
bool FiniteAutomata::setStartState(const std::string& state) {
	return setStartState(getState(state));
}

bool FiniteAutomata::setAcceptState(State state) {
	if (state < 0 || state >= stateCount)
		return false;
	acceptStates.insert(state);
	return true;
}
bool FiniteAutomata::setAcceptState(const std::string& state) {
	return setAcceptState(getState(state));
}

bool FiniteAutomata::setStateCount(int stateCount) {
	if (stateCount <= 0)
		return false;
	this->stateCount = stateCount;
	return true;
}

int FiniteAutomata::addState(bool acceptState) {
	currentState.insert(0);
	acceptStates.insert(acceptState);
	return stateCount++;
}

int FiniteAutomata::addState(const std::string& label, bool acceptState) {
	int stateId = addState(acceptState);
	labelState(stateId, label);
	return stateId;
}

bool FiniteAutomata::labelState(State state, const std::string& label) {
	if (state < 0 || state >= stateCount || label.empty())
		return false;
	stateLabels[label] = state;
	return true;
}

FiniteAutomata::State FiniteAutomata::getState(const std::string& label) {
	auto it = stateLabels.find(label);
	if (it != stateLabels.end())
		return it->second;
	return -1;
}

std::string FiniteAutomata::getAlphabet() {
	std::string s;
	for (Symbol symbol : alphabet)
		if (symbol != EPSILON)
			s.push_back(symbol);
	return s;
}

/*
std::string FiniteAutomata::getRegex() {
	return std::string();
}
// */
