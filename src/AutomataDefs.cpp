#include "AutomataDefs.h"


void Automata::addStateSet(StateSet & dest, const StateSet & rhs)
{
	for (State state : rhs)
		dest.insert(state);
}

Automata::Automata()
{
}

Automata::~Automata()
{
}
