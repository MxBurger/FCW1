#include <cstdio>
#include <iomanip>
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
    cout << "NFA Test Program" << endl;
    cout << "----------------" << endl;

    FABuilder fab;
    // State S
    fab.addTransition("S", 'a', "A");  // S -a-> A
    fab.addTransition("S", 'b', "B");  // S -b-> B
    fab.addTransition("S", 'c', "C");  // S -c-> C
    fab.addTransition("S", 'a', "S");  // S -a-> S (self loop)
    fab.addTransition("S", 'b', "S");  // S -b-> S (self loop)
    fab.addTransition("S", 'c', "S");  // S -c-> S (self loop)

    // State A
    fab.addTransition("A", 'a', "A");  // A -a-> A (self loop)
    fab.addTransition("A", 'b', "A");  // A -b-> A (self loop)
    fab.addTransition("A", 'c', "A");  // A -c-> A (self loop)
    fab.addTransition("A", 'a', "R");  // A -a-> R

    // State B
    fab.addTransition("B", 'a', "B");  // B -a-> B (self loop)
    fab.addTransition("B", 'b', "B");  // B -b-> B (self loop)
    fab.addTransition("B", 'c', "B");  // B -c-> B (self loop)
    fab.addTransition("B", 'b', "R");  // B -b-> R

    // State C
    fab.addTransition("C", 'a', "C");  // C -a-> C (self loop)
    fab.addTransition("C", 'b', "C");  // C -b-> C (self loop)
    fab.addTransition("C", 'c', "C");  // C -c-> C (self loop)
    fab.addTransition("C", 'c', "R");  // C -c-> R

    // Set start and final states
    fab.setStartState("S");
    fab.addFinalState("R");

    NFA* nfa = fab.buildNFA();
    vizualizeFA("nfa", nfa);

    DFA* dfa = nfa->dfaOf();
    vizualizeFA("dfa", dfa);

    DFA* minDfa = dfa->minimalOf();
    vizualizeFA("minDfa", minDfa);

    const char* testStrings[] = {
        "aa",       // Minimal accepting string
        "aaaaaaaa", // Long string with lots of self-loops
        "abcabcabc",// many state changes
        "abcabcz",  // Invalid string
        "abc",      // Non-accepting valid string
        ""          // Empty string
    };

    for (const char* str : testStrings) {
        cout << "\nTesting string \"" << str << "\":" << endl;
        cout << "----------------------------------------" << endl;

        // Test accepts1 (Multithreading)
        startTimer();
        bool result1 = nfa->accepts1(str);
        stopTimer();
        cout << "accepts1 (Multithreading): "
             << (result1 ? "accepted" : "rejected")
             << " [Time: " << elapsedTime() << " microseconds]" << endl;

        // Test accepts2 (Backtracking)
        startTimer();
        bool result2 = nfa->accepts2(str);
        stopTimer();
        cout << "accepts2 (Backtracking):   "
             << (result2 ? "accepted" : "rejected")
             << " [Time: " << elapsedTime() << " microseconds]" << endl;

        // Test accepts3 (State Sets)
        startTimer();
        bool result3 = nfa->accepts3(str);
        stopTimer();
        cout << "accepts3 (State Sets):     "
             << (result3 ? "accepted" : "rejected")
             << " [Time: " << elapsedTime() << " microseconds]" << endl;

        if ((result1 != result2) || (result2 != result3)) {
            cout << "WARNING: Inconsistent results between methods!" << endl;
        }
    }

    cout << "\nPerformance test with long string:" << endl;
    cout << "----------------------------------------" << endl;

    // long string with many self-loops
    string longStr = "a";
    for(int i = 0; i < 200; i++) {
        longStr += "a";
    }
    longStr += "a";

    cout << "Testing string of length " << longStr.length() << ":" << endl;

    startTimer();
    nfa->accepts1(longStr);
    stopTimer();
    cout << "accepts1 time: " << elapsedTime() << " microseconds" << endl;

    startTimer();
    nfa->accepts2(longStr);
    stopTimer();
    cout << "accepts2 time: " << elapsedTime() << " microseconds" << endl;

    startTimer();
    nfa->accepts3(longStr);
    stopTimer();
    cout << "accepts3 time: " << elapsedTime() << " microseconds" << endl;

    delete nfa;
    delete dfa;
    delete minDfa;
    return 0;
}