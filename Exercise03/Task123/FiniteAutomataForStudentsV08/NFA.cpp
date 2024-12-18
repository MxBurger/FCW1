// NFA.cpp:                                               HDO, 2006-2019
// -------
// Objects of class NFA represent non-deterministic finite automata.
//======================================================================

#include <cstring>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

using namespace std;


#include "TapeStuff.h"
#include "StateStuff.h"
#include "DeltaStuff.h"
#include "FA.h"
#include "DFA.h"
#include "NFA.h"
#include "FABuilder.h"


// --- implementation of class NFA ---


NFA::NFA(const StateSet &S,  const TapeSymbolSet &V,
         const State    &s1, const StateSet      &F,
         const NDelta   &delta)
: FA(S, V, s1, F), delta(delta) {
} // NFA::NFA


StateSet NFA::deltaAt(const State &src, TapeSymbol tSy) const {
  return delta[src][tSy];
} // NFA::deltaAt


bool NFA::accepts(const Tape &tape) const {
  bool ac1 = accepts1(tape);
  bool ac2 = accepts2(tape);
  bool ac3 = accepts3(tape);
  if ( (ac1 == ac2) && (ac2 == ac3) )
    return ac1;
  else
    throw runtime_error("results in NFA::accepts methods do not match");
} // NFA::accepts


// NFA::accepts1: uses multithreading to simulate non-determinism
//--------------

static bool  accepted;
static mutex mtx;  // used to synchronize access to variable accepted

static void accept1(const NDelta &delta, const StateSet &F,
                    const State &s, const Tape &tape, int i) {
  vector<thread> tv; // thread vector
  for (const State &epsDest : delta[s][eps]) // eps. transitions
    tv.push_back(thread(accept1, cref(delta), cref(F),
      epsDest, tape, i));
  TapeSymbol tSy = tape[i];
  if (tSy == eot && F.contains(s)) { // end of tape and s is final
    mtx.lock();
    accepted = true;
    mtx.unlock();
  } else
    for (const State &tSyDest : delta[s][tSy]) // symbol transitions
      tv.push_back(thread(accept1, cref(delta), cref(F),
        tSyDest, tape, i + 1));
  for (auto &t : tv)
    t.join(); // join thread t with current thread
} // accept1

bool NFA::accepts1(const Tape &tape) const {
  accepted = false;
  accept1(this->delta, this->F, this->s1, tape, 0); // normal call ...
                                       // ... within current thread
  return accepted;
} // NFA::accepts1


// NFA::accepts2: uses backtracking to simulate non-determinism
//--------------

bool NFA::accepts2(const Tape &tape) const { // public
  return accepts2(s1, tape, 0); // see below
} // NFA::accepts2

bool NFA::accepts2(const State &s,           // private
                   const Tape &tape, int i) const {
  for (const State &epsDest : delta[s][eps]) // eps transitions
    if (accepts2(epsDest, tape, i))  // recursive call
      return true;
  TapeSymbol tSy = tape[i];
  if (tSy == eot)
    return F.contains(s);  // accepted <==> s is final
  for (const State &tSyDest : delta[s][tSy]) // symbol transitions
    if (accepts2(tSyDest, tape, i + 1)) // recursive call
      return true;
  return false;   // not accepted as no call succeeded
} // NFA::accepts2


// NFA::epsilonClosureOf (cf. Aho/Sethi/Ullman, p. 119):
//----------------------

StateSet NFA::epsClosureOf(const State &src) const {
  return epsClosureOf(StateSet(src)); // see below
} // NFA::epsClosureOf

StateSet NFA::epsClosureOf(const StateSet &src) const {
  StateSet ec  = src;
  StateSet stc = src; // states to check
  while (!stc.empty()) {
    State s = stc.anyElement();
    stc.erase(s);
    for (const State &dest: delta[s][eps]) {
      auto ir = ec.insert(dest);
      if (ir.second)       // new state dest was inserted
        stc.insert(dest);
    } // for
  } // while
  return ec;
} // NFA::epsClosureOf


// NFA::allDestsFor (function move from Aho/Sethi/Ullman, p. 118):
//-----------------

StateSet NFA::allDestsFor(const StateSet &src, TapeSymbol tSy) const {
  StateSet ad; // start with empty set for all destinations
  for (const State &s: src)
    for (const State &dest: delta[s][tSy])
      ad.insert(dest);
  return ad;
} // NFA::allDestsFor


// NFA::accepts3: tracing of state sets to simulate non-determinism
//--------------

bool NFA::accepts3(const Tape &tape) const {
  int        i   = 0;       // index of first symbol
  TapeSymbol tSy = tape[i]; // fetch first symbol
  StateSet   ss  = epsClosureOf(StateSet(s1));

  while (tSy != eot) {      // eot = end of tape
    StateSet dest = allDestsFor(ss, tSy);
    if (!defined(dest))
      return false;         // undefined, so no acceptance
    ss = epsClosureOf(dest);
    i++;
    tSy = tape[i];
  } // while
                         // ^ intersection operator:
  return !empty(ss ^ F); // accepted <==> (ss ^ F) != {}
} // NFA::accepts3


// NFA::dfaOf (cf. Aho/Sethi/Ullman, p. 118):
//-----------


DFA *NFA::dfaOf() const {

  FABuilder fab;

  // 1. construct new delta function for DFA (S and V implicitly)
  StateSet       startStateSet = epsClosureOf(s1);
  SetOfStateSets allStateSets  = startStateSet;
  SetOfStateSets sstc = startStateSet; // StateSets to check
  while (!sstc.empty()) {
    StateSet srcStateSet = sstc.anyElement();
                           sstc.erase(srcStateSet);
    for (TapeSymbol tSy : V) {
      StateSet destStateSet =
        epsClosureOf(allDestsFor(srcStateSet, tSy));
      if (!destStateSet.empty()) {  // transition is defined
        if (!allStateSets.contains(destStateSet)) {
          allStateSets.insert(destStateSet);
          sstc.insert(destStateSet);
        } // if
        fab.addTransition( srcStateSet.stateOf(), tSy,
                          destStateSet.stateOf());
      } // if
    } // for
  } // while

  // 2. define new start state s1 for DFA
  fab.setStartState(startStateSet.stateOf());

  // 3. look for final states f and define new F for DFA
  for (const StateSet &stateSet: allStateSets)
    for (const State &f: F)
      if (stateSet.contains(f))
        fab.addFinalState(stateSet.stateOf());

  return fab.buildDFA();
} // NFA::dfaOf


// end of NFA.cpp
//======================================================================


