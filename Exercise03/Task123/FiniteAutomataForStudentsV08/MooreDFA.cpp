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

void MooreDFA::OnStateEntered(const State &s) const {
    cout << lambda.at(s) << endl;
}

#if 0
bool MooreDFA::accepts(const Tape &tape) const {
    int        i   = 0;       // index of first symbol
    TapeSymbol tSy = tape[i]; // fetch first tape symbol
    State      s   = s1;      // start state
    cout << lambda.at(s) << endl;
    while (tSy != eot) {      // eot = end of tape
        s = delta[s][tSy];
        if (!defined(s))
            return false;         // s undefined, so no acceptance
        cout << lambda.at(s) << endl;
        i++;
        tSy = tape[i];          // fetch next symbol
    } // while
    return F.contains(s);

} // accepts

#endif

// end of MooreDFA.cpp
//======================================================================
