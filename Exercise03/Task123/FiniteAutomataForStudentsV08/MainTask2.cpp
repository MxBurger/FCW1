using namespace std;

#include <iostream>
#include "SignalHandling.h"
#include "Timer.h"
#include "SymbolStuff.h"
#include "SequenceStuff.h"
#include "Vocabulary.h"
#include "GrammarBasics.h"
#include "GrammarBuilder.h"
#include "Grammar.h"
#include "Language.h"
#include "TapeStuff.h"
#include "StateStuff.h"
#include "MbMatrix.h"
#include "DeltaStuff.h"
#include "FA.h"
#include "DFA.h"
#include "NFA.h"
#include "MooreDFA.h"
#include "FABuilder.h"
#include "GraphVizUtil.h"
#include "MealyDFA.h"

// Activation (with 1) allows simple builds via command line
// * for GNU   use:  g++      -std=c++17 Main.cpp
// * for Clang use:  clang++  -std=c++17 Main.cpp
// * for M.S.  use:  cl /EHsc /std:c++17 Main.cpp
#if 1
#include "SignalHandling.cpp"
#include "Timer.cpp"
#include "SymbolStuff.cpp"
#include "SequenceStuff.cpp"
#include "GrammarBasics.cpp"
#include "GrammarBuilder.cpp"
#include "Grammar.cpp"
#include "Language.cpp"
#include "TapeStuff.cpp"
#include "StateStuff.cpp"
#include "MbMatrix.cpp"
#include "DeltaStuff.cpp"
#include "FA.cpp"
#include "DFA.cpp"
#include "NFA.cpp"
#include "MooreDFA.cpp"
#include "FABuilder.cpp"
#include "GraphVizUtil.cpp"
#include "MealyDFA.cpp"
#endif

int main() {
    FABuilder* builder = new FABuilder();
    builder->setStartState("B");
    builder->addFinalState("R");
    builder->addTransition("B", 'b', "R");
    builder->addTransition("R", 'b', "R");
    builder->addTransition("R", 'z', "R");
    DFA* baseDfa = builder->buildDFA();

    // Output mapping for MealyDFA
    map<State, map<TapeSymbol, char>> lambda = {
        {"B", {{'b', 'c'}}},
        {"R", {{'b', 'c'}, {'z', 'd'}}}
    };
    MealyDFA* mealyDFA = new MealyDFA(
        baseDfa->S,
        baseDfa->V,
        baseDfa->s1,
        baseDfa->F,
        baseDfa->delta,
        lambda
    );
    vizualizeFA("mealy", mealyDFA);

    // Tests
    cout << "Translate 'b' to 'c':" << endl;
    mealyDFA->accepts("b");
    cout << endl;
    cout << "Translate 'bzzb' to 'cddc':" << endl;
    mealyDFA->accepts("bzzb");
    cout << endl;
    delete mealyDFA;
    delete baseDfa;
    delete builder;
    return 0;
}