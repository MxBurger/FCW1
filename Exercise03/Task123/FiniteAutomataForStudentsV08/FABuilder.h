// FABuilder.h:                                                HDO, 2019
// -----------
// FABuilder implements the builder pattern in order to build
// deterministic and non-deterministic finite automata, i.e.
// objects of classes DFA or NFA (both derived from abstract base FA).
//======================================================================

#pragma once
#ifndef FABuilder_h
#define FABuilder_h

#include <initializer_list>
#include <iosfwd>
#include <string>

#include "ObjectCounter.h"
#include "TapeStuff.h"
#include "StateStuff.h"
#include "DeltaStuff.h"


class FA;    // forward declarations for ...
class DFA;   //    ... the return types in ...
class NFA;   //    ... the build methods below
class MooreDFA;

class FABuilder final // no public base class
               /*OC+*/ : private ObjectCounter<FABuilder> /*+OC*/ {

  friend std::ostream &operator<<(std::ostream &os, const FABuilder &fab);

  private:

    StateSet        S;     // set of statse       (cf. "nonterminals")
    TapeSymbolSet   V;     // set of tape symbols (cf. "terminals")
    Delta<StateSet> delta; // type for NFA, transformed to Delta<State> for DFA
    State           s1;    // start state, an element of S
    StateSet        F;     // set of final states, a subset of S
    std::map<State, char> mooreLambda;

    void checkStates() const;

    void initFromStream(std::istream &is);  // read FA from stream, synax:
      // -> S -> a B | ...  leading -> flags the one and only start sate
      //    B -> c E | ...  meaning: delta[B][c] = E or (B, c) -> E
      // () E -> ...        leading () flags final state(s)
      // also allowed: -> () S -> ... for start state being final, too

  public:

    FABuilder() = default; // empty builder, needs programmatical init.
    FABuilder(const std::string &fileName); // init. from text file
    FABuilder(const char        *str);      // init. from C string (e.g., in the source)

    FABuilder &operator==(const FABuilder  &fab) = delete;
    FABuilder &operator==(      FABuilder &&fab) = delete;

    ~FABuilder() = default; // no virtual as class is final

    // following methods for programmatical init. provide a fluent interface:

    FABuilder &setStartState (const State    &s);

    FABuilder &addFinalState (const State    &s);
    FABuilder &addFinalStates(const StateSet &sSet);
    FABuilder &addFinalStates(std::initializer_list<State> il);

    FABuilder &addTransition(
               const State &src, TapeSymbol tSy, const State    &dest);
    FABuilder &addTransition(
               const State &src, TapeSymbol tSy, const StateSet &destSet);
    FABuilder &addTransition(
               const State &src, TapeSymbol tSy, std::initializer_list<State> il);
    FABuilder &setMooreLambda(const std::map<State, char> mooreLambda);

    // build methods:

    bool representsDFA() const;

     FA *buildFA()  const;  // build DFA when possible, otherwise build NFA
    DFA *buildDFA() const;  // requires: representsDFA() == true
    NFA *buildNFA() const;  // always works
    MooreDFA *buildMooreDFA() const;

    // finally, a clear method that allows reuse or the builder:

    void clear();

}; // FABuilder

ostream &operator<<(std::ostream &os, const FABuilder &fab);


#endif

// end of FABuilder.h
//======================================================================