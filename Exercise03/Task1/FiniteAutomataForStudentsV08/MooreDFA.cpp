// MooreDFA.h:                                           HDO, 2021-10-22
// ----------
// Objects of class MooreDFA represent deterministic finite automata
// for transformation purposes as defined by Edward F. Moore.
//======================================================================

#include <iostream>
#include <map>

using namespace std;

#include "TapeStuff.h"
#include "StateStuff.h"
#include "MbMatrix.h"
#include "FABuilder.h"
#include "MooreDFA.h"


// --- implementation of class MooreDFA ---

MooreDFA::MooreDFA(const StateSet &S,  const TapeSymbolSet &V,
                   const State    &s1, const StateSet      &F,
                   const DDelta   &delta,
                   const map<State, char> &lambda)
: DFA(S, V, s1, F, delta), lambda(lambda) { // without const: lambda(move(lambda))
} // MooreDFA::MooreDFA

bool MooreDFA::accepts(const Tape &tape) const {
  cerr << "ERROR: implementation of MooreDFA::accepts missing" << endl;
  return false;
} // accepts


// end of MooreDFA.cpp
//======================================================================
