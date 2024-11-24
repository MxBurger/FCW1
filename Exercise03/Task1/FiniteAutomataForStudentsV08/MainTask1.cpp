#include <cstdio>

#include <iostream>
#include <typeinfo>



using namespace std;

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
#endif

// TASK 1a)
NFA* faOf(const Grammar* g) {
    FABuilder* builder = new FABuilder();
    builder->setStartState(g->root->name);

    // Analyze rules to determine which NTs have only self-transitions
    std::map<string, bool> hasOnlySelfTransitions;
    for (const auto& rule : g->rules) {
        const NTSymbol* nt = rule.first;
        hasOnlySelfTransitions[nt->name] = true;

        for (const Sequence* seq : rule.second) {
            // A nonterminal is not a final state if it has a rule that is not a self-transition
            if (seq->length() == 1 || (seq->length() == 2 && seq->at(1)->name != nt->name)) {
                hasOnlySelfTransitions[nt->name] = false;
                break;
            }
        }
    }

    bool needsFinalState = false;
    for (const auto& rule : g->rules) {
        const NTSymbol* nt = rule.first;

        for (const Sequence* seq : rule.second) {
            if(seq->isEpsilon()) {
                builder->addFinalState(nt->name);
            }
            if (seq->length() == 1) {
                // Handle A → a
                const Symbol* sym = seq->at(0);
                if (sym->isT()) {
                    needsFinalState = true;
                    builder->addTransition(nt->name, sym->name[0], "FINAL");
                }
            }
            else if (seq->length() == 2) {
                // Handle A → aB
                const Symbol* first = seq->at(0);
                const Symbol* second = seq->at(1);
                if (first->isT() && second->isNT()) {
                    builder->addTransition(nt->name, first->name[0], second->name);
                }
            }
        }

        // A NT is a final state if it has only self-transitions
        if (hasOnlySelfTransitions[nt->name] && !rule.second.empty()) {
            builder->addFinalState(nt->name);
        }
    }

    if (needsFinalState) {
        builder->addFinalState("FINAL");
    }

    NFA* result = builder->buildNFA();
    delete builder;
    return result;
}

// TASK 1b)
Grammar* grammarOf(const NFA* nfa) {
    SymbolPool* sp = new SymbolPool();
    GrammarBuilder* builder = new GrammarBuilder(sp->ntSymbol(nfa->s1));

    for (const State& state : nfa->S) {
        if (nfa->F.contains(state) && state == nfa->s1) {
            bool hasFinalTransition = false;
            for (const TapeSymbol& sym : nfa->V) {
                if (nfa->delta[state][sym].contains("FINAL")) {
                    hasFinalTransition = true;
                    break;
                }
            }
            if (!hasFinalTransition) {
                builder->addRule(sp->ntSymbol(state), new Sequence());
            }
        }

        for (const TapeSymbol& sym : nfa->V) {
            StateSet nextStates = nfa->delta[state][sym];
            for (const State& nextState : nextStates) {
                if (nextState != "FINAL") {
                    // A → aB
                    builder->addRule(sp->ntSymbol(state),
                                   new Sequence({sp->tSymbol(string(1, sym)),
                                               sp->ntSymbol(nextState)}));
                } else {
                    // A → a
                    builder->addRule(sp->ntSymbol(state),
                                   new Sequence({sp->tSymbol(string(1, sym))}));
                }
            }
        }
    }

    Grammar* result = builder->buildGrammar();
    delete sp;
    delete builder;
    return result;
}




int main(int argc, char *argv[]) {
    installSignalHandlers();
    startTimer();

    SymbolPool *sp = new SymbolPool();
    GrammarBuilder *gb3 = nullptr;
    Grammar *g3 = nullptr;
    Grammar *g4 = nullptr;
  // gb3 = new GrammarBuilder(
  //"G(S): \n\
  //S -> b A | a B | eps \n\
  //A -> b A | b \n\
  //B -> b C | b \n\
  //C -> a B");

   gb3 = new GrammarBuilder(
   "G(S): \n\
   S -> a B \n\
   A -> b B | eps \n\
   B -> c C | a \n\
   C -> a A | b");

    //gb3 = new GrammarBuilder(
    //"G(S): \n\
    //           S -> 0 A | 1 B \n\
    //           A -> 0 E | 1 B \n\
    //           B -> 0 C | 1 B \n\
    //           E -> 0 E | 1 E \n\
    //           C -> 0 E | 1 S");

    //gb3 = new GrammarBuilder(
    //"G(S):              \n\
    // S -> a A | b S               \n\
    // A -> a A | b");

    g3 = gb3->buildGrammar();
    cout << "grammar from C string:" << endl << *g3 << endl;

    NFA* nfa = faOf(g3);
    cout << "Converted NFA:" << endl << *nfa << endl;
    vizualizeFA("nfa", nfa);

    g4 = grammarOf(nfa);
    cout << "grammar from nfa:" << endl << *g4 << endl;

    delete nfa;
    delete g3;
    delete g4;
    delete gb3;
    delete sp;

    stopTimer();
    cout << "elapsed time: " << elapsedTime() << endl;
    cout << endl;
    cout << "END Main" << endl;

}