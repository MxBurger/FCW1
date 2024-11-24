#include <iostream>
#include "MealyDFA.h"

MealyDFA::MealyDFA(const StateSet &S,  const TapeSymbolSet &V,
                   const State    &s1, const StateSet      &F,
                   const DDelta   &delta,
                   const map<State, map<TapeSymbol, char>> &lambda)
    : DFA(S, V, s1, F, delta), lambda(lambda) {
}

bool MealyDFA::accepts(const Tape &tape) const {
    int i = 0;
    TapeSymbol tSy = tape[i];
    State s = s1;

    while (tSy != eot) {
        if (!defined(delta[s][tSy])) {
            return false;
        }

        if (lambda.count(s) > 0 && lambda.at(s).count(tSy) > 0) {
            std::cout << lambda.at(s).at(tSy);
        }
        s = delta[s][tSy];
        i++;
        tSy = tape[i];
    }
    return F.contains(s);
}