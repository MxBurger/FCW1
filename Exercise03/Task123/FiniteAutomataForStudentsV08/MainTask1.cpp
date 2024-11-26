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
    for (const auto& rule : g->rules) {
        const NTSymbol* nt = rule.first;
        bool hasOnlySelfTransitions = true;
        for (const Sequence* seq : rule.second) {
            if(seq->isEpsilon()) { // Handle A → ε
                builder->addFinalState(nt->name);
            }
            if (seq->length() == 1) { // Handle A → a
                const Symbol* sym = seq->at(0);
                if (sym->isT()) {
                    builder->addFinalState("FINAL");
                    builder->addTransition(nt->name, sym->name[0], "FINAL");
                }
            }
            else if (seq->length() == 2) { // Handle A → aB
                const Symbol* first = seq->at(0);
                const Symbol* second = seq->at(1);
                if (first->isT() && second->isNT()) {
                    builder->addTransition(nt->name, first->name[0], second->name);
                }
            }
            // Handle A → aA
            if (seq->length() == 1 || (seq->length() == 2 && seq->at(1)->name != nt->name)) {
                hasOnlySelfTransitions = false;
            }
        }
        // A NT is a final state if it has only self-transitions
        if (hasOnlySelfTransitions && !rule.second.empty()) {
            builder->addFinalState(nt->name);
        }
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
        // A → ε
        if (state == nfa->s1 && nfa->F.contains(state)) {
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
                // A → aB
                if (nextState != "FINAL") {
                    builder->addRule(sp->ntSymbol(state),
                                   new Sequence({sp->tSymbol(string(1, sym)),
                                               sp->ntSymbol(nextState)}));
                }
                // A → a
                else {
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
    // test grammars
    const char* grammarStrings[4] = {
        // grammar 1
        "G(S): \n\
        S -> b A | a B | eps \n\
        A -> b A | b \n\
        B -> b C | b \n\
        C -> a B",
        // grammar 2
        "G(S): \n\
        S -> a B \n\
        A -> b B | eps \n\
        B -> c C | a \n\
        C -> a A | b",
        // grammar 3
        "G(S): \n\
        S -> 0 A | 1 B \n\
        A -> 0 E | 1 B \n\
        B -> 0 C | 1 B \n\
        E -> 0 E | 1 E \n\
        C -> 0 E | 1 S",
        // grammar 4
        "G(S):              \n\
        S -> a A | b S               \n\
        A -> a A | b"
    };

    SymbolPool *sp = new SymbolPool();
    GrammarBuilder *gb = nullptr;
    Grammar *g = nullptr;
    Grammar *g1 = nullptr;
    for(int i = 0; i < 4; i++) {
        gb = new GrammarBuilder(grammarStrings[i]);
        g = gb->buildGrammar();
        cout << "grammar" << i + 1 << " from string-literal:" << endl << *g;
        NFA* nfa = faOf(g);
        cout << "Converted NFA" << i + 1 <<  ":" << endl << *nfa;
        vizualizeFA("nfa", nfa);
        Grammar* g1 = grammarOf(nfa);
        cout << "grammar" << i + 1 <<  " from nfa:" << endl << *g1;
        delete nfa;
        delete g;
        delete g1;
        delete gb;

        cout << "----------------------------------------------------------------" << endl;
    }

    delete sp;
    stopTimer();
    cout << "elapsed time: " << elapsedTime() << endl;
    cout << endl;
    cout << "END Main" << endl;

}