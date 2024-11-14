// MooreDFA.h:                                           HDO, 2021-10-22
// ----------
// Objects of class MooreDFA represent deterministic finite automata
// for transformation purposes as defined by Edward F. Moore.
//======================================================================

#ifndef MooreDFA_h
#define MooreDFA_h

#include <map>

#include "ObjectCounter.h"
#include "TapeStuff.h"
#include "StateStuff.h"
#include "DFA.h"


class FABuilder;           // forward for friend declaration only

class MooreDFA: public DFA
 /*OC+*/ , private ObjectCounter<MooreDFA> /*+OC*/ {

  friend class FABuilder;  // so ::build... methods can call prot. constr.

  private:

    typedef DFA Base;

  protected:

    // constructor called by FABuilder::buildMooreDFA method only
    MooreDFA(const StateSet &S,  const TapeSymbolSet &V,
             const State    &s1, const StateSet      &F,
             const DDelta   &delta,
             const std::map<State, char> &lambda);

  public:

    const std::map<State, char> lambda;    // lambda function for output

    virtual bool accepts(const Tape &tape) const; // override DFA::accepts

}; // MooreDFA


#endif

// end of MooreDFA.h
//======================================================================

