#ifndef MEALYDFA_H
#define MEALYDFA_H

#include <map>
#include "DFA.h"

class MealyDFA : public DFA {
private:
    map<State, map<TapeSymbol, char>> lambda;

public:
    MealyDFA(const StateSet &S,  const TapeSymbolSet &V,
             const State    &s1, const StateSet      &F,
             const DDelta   &delta,
             const map<State, map<TapeSymbol, char>> &lambda);

    virtual ~MealyDFA() = default;

    bool accepts(const Tape &tape) const override;

    const map<State, map<TapeSymbol, char>>& getLambda() const {
        return lambda;
    }
};

#endif //MEALYDFA_H
