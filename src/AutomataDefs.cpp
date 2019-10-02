#include "AutomataDefs.h"

void Automata::svOr(StateVec& dest, const StateVec& sv) {
	for (int i = 0; i < dest.size() && i < sv.size(); i++) {
		dest[i] = dest[i] | sv[i];
	}
}

void Automata::svAnd(StateVec& dest, const StateVec& sv)
{
	for (int i = 0; i < dest.size() && i < sv.size(); i++) {
		dest[i] = dest[i] & sv[i];
	}
}

void Automata::svXor(StateVec& dest, const StateVec& sv)
{
	for (int i = 0; i < dest.size() && i < sv.size(); i++) {
		dest[i] = dest[i] ^ sv[i];
	}
}

void Automata::svNot(StateVec& sv)
{
	for (int i = 0; i < sv.size(); i++) {
		sv[i] = !sv[i];
	}
}

void Automata::svSet(StateVec& sv, bool state)
{
	for (int i = 0; i < sv.size(); i++) {
		sv[i] = state;
	}
}

void Automata::svClear(StateVec& sv)
{
	svSet(sv, 0);
}

Automata::Automata()
{
}

Automata::~Automata()
{
}
