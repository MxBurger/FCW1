// Grammar.cpp:                                           HDO, 2004-2020
// -----------
// Objects of class Grammar represent context free grammars.
// =====================================================================

#include <cstdarg>
#include <cstddef>
#include <cstring>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;
using std::function;

#include "GrammarBasics.h"
#include "GrammarBuilder.h"
#include "Grammar.h"


// macro used in operator<<:
#define LIST_RULES_IN_TOPOLOGIC_ORDER    // #undef for lexicographic order


// === implementation of class Grammar =================================

Grammar::Grammar(NTSymbol *const root, const RulesMap &rules,
                 const VNt &vNt, const VT &vT, const V &v)
: root(root), rules(rules), vNt(vNt), vT(vT), v(v) {
  // nothing left to do
} // Grammar::Grammar


VNt Grammar::deletableNTs() const {
  VNt vNtDel;

  // 1. look for NTs with an empty sequence
  for (auto &rule: rules) {
    for (Sequence *seq: rule.second) {
      if (seq->isEpsilon()) {
        vNtDel.insert(const_cast<NTSymbol *>(rule.first));
        break;
      } // if
    } // for
  } // for

  // 2. look for NTs having at least one deletable sequence
  int oldSize;
  do {
    oldSize = vNtDel.size();
    for (auto &rule: rules) {
      if (!vNtDel.contains(const_cast<NTSymbol *>(rule.first))) {
        for (Sequence *seq: rule.second) {
          bool seqIsDeletable = true;
          for (const Symbol *sy: *seq) {
            if (   sy->isT () ||
                 ( sy->isNT() &&
                  !vNtDel.contains(dynamic_cast<NTSymbol *>(
                                     const_cast<Symbol   *>(sy))) ) ) {
              seqIsDeletable = false;
              break;
            } // if
          } // for
          if (seqIsDeletable) {
            vNtDel.insert(const_cast<NTSymbol *>(rule.first));
            break;
          } // if
        } // for
      } // if
    } // for
  } while (vNtDel.size() > oldSize);

  return vNtDel;
} // Grammar::deletableNTs


bool Grammar::isEpsilonFree() const {
  for (auto &rule: rules) {
    if (rule.first != root)  // empty seq. allowed for root only
      for (Sequence *seq: rule.second) {
        if (seq->isEpsilon())
          return false;
      } // for
  } // for
  return true;
} //  Grammar::isEpsilonFree


bool Grammar::rootHasEpsilonAlternative() const {
  for (Sequence *seq: rules.find(root)->second) {
    if (seq->isEpsilon()) // root -> ... | EPS | ...
     return true;
  } // for
  return false;
} // Grammar::rootHasEpsilonAlternative


#ifdef LIST_RULES_IN_TOPOLOGIC_ORDER
static vector<NTSymbol *> topSortedNts(const Grammar &g) {
  vector<NTSymbol *> ntv;       // topologically sorted nonterminals
  ntv.push_back(g.root);        // start with root nonterminal

  // 1. insert reachable nonterminals
  for (size_t i = 0; i < ntv.size(); i++)
    for (const Sequence *seq: const_cast<Grammar &>(g).rules[ntv[i]])
      for (const Symbol *sy: *seq)
        if (sy->isNT()) {
          NTSymbol *ntSy = (NTSymbol *)sy;
          if (find(ntv.begin(), ntv.end(), ntSy) ==
              ntv.end())        // sy is not in ntvs yet
            ntv.push_back(ntSy);
        } // if

  //2. insert unreachable nonterminals, too
  for (auto &rule: g.rules)
    if (find(ntv.begin(), ntv.end(), rule.first) ==
      ntv.end())                // nonterminal is not in ntv yet
      ntv.push_back(rule.first);

  return ntv;
} // topSortedNts
#endif

ostream& operator<<(ostream &os, const Grammar &g) {
  vector<NTSymbol *> ntv;  // vector of nonterminals
#ifdef LIST_RULES_IN_TOPOLOGIC_ORDER
  ntv = topSortedNts(g);
#else // list rules in lexicographic order
  for (auto &rule: g.rules)
    ntv.push_back(rule.first);
#endif
  os << endl;
  os << "G(" << *g.root << "):" << endl;
  for (NTSymbol *ntSy: ntv) {
    os << *ntSy << " -> ";
    bool first = true;
    for (const Sequence *seq: const_cast<Grammar &>(g).rules[ntSy]) {
      if (!first)
        os << " | ";
      os << *seq;
      first = false;
    } // for
    os << endl;
  } // for
  os << "---" << endl;
  os << "VNt = " << g.vNt;

  VNt vNtDel = g.deletableNTs();
  os << ", deletable: " << vNtDel;

  os << endl;
  os << "VT  = " << g.vT << endl;
  os << endl;
  return os;
} // operator<<

void generateCombinations(Sequence* newAlt, size_t pos, const vector<size_t>& deletableIndices, const Sequence* alt, NTSymbol* nt, GrammarBuilder* builder) {
  if (pos == deletableIndices.size()) {
    if (newAlt->length() > 0) {
      builder->addRule(nt, new Sequence(*newAlt));
    }
    return;
  }

  // Include the deletable symbol
  newAlt->append(alt->at(deletableIndices[pos]));
  generateCombinations(newAlt, pos + 1, deletableIndices, alt, nt, builder);

  // Exclude the deletable symbol
  if (!newAlt->empty()) {
    newAlt->pop_back();
  }
  generateCombinations(newAlt, pos + 1, deletableIndices, alt, nt, builder);
}


Grammar *newEpsilonFreeGrammarOf(const Grammar *g) {
    // Get all deletable nonterminal symbols
    Vocabulary<NTSymbol> deletableNTs = g->deletableNTs();

    SymbolPool* sp = new SymbolPool();
    GrammarBuilder* builder = new GrammarBuilder(g->root);

    for (const auto& rule : g->rules) {
        NTSymbol* nt = rule.first;

        for (const Sequence* alt : rule.second) {
            // Skip empty alternatives
            if (alt->length() == 0) continue;

            // Find positions of deletable symbols in this alternative
            vector<size_t> deletableIndices;
            for (int i = 0; i < alt->length(); i++) {
                Symbol* sym = alt->at(i);
                if (sym->isNT() && deletableNTs.contains(dynamic_cast<NTSymbol*>(sym))) {
                    deletableIndices.push_back(i);
                }
            }

            // Generate a new  alternative with non-deletable symbols
            Sequence* newAlt = new Sequence();
            for (int i = 0; i < alt->length(); i++) {
                if (find(deletableIndices.begin(), deletableIndices.end(), i) == deletableIndices.end()) {
                    newAlt->append(alt->at(i));
                }
            }

            generateCombinations(newAlt, 0, deletableIndices, alt, nt, builder);
            delete newAlt;
        }
    }

    // Handle deletable start symbol
    if (deletableNTs.contains(g->root)) {
        NTSymbol* newRoot = sp->ntSymbol(g->root->name + "'");
        builder->setNewRoot(newRoot);
        Sequence* emptySeq = new Sequence();
        builder->addRule(newRoot, {emptySeq, new Sequence({g->root})});
    }

    Grammar* result = builder->buildGrammar();
    delete sp;
    delete builder;
    return result;
}



// === test ============================================================

#if 0

#include <cstdio>

#include <typeinfo>

#include "SymbolStuff.cpp"
#include "SequenceStuff.cpp"
#include "GrammarBasics.cpp"
#include "GrammarBuilder.cpp"

#ifdef TEST
#error previously included cpp file already defines a main function for testing
#endif
#define TEST

int main(int argc, char *argv[]) {
try {

  cout << "START: Grammar test" << endl;
  cout << endl;

  SymbolPool *sp = new SymbolPool();

  GrammarBuilder gb(string("G.txt"));
  Grammar       *g = gb.buildGrammar();

  cout << "g = " << endl << *g << endl;

  Grammar *g2 = new Grammar(*g);
  cout << "g2 = " << endl << *g2 << endl;

  delete g2;

  cout << "g = " << endl << *g << endl;

  delete g;
  delete sp;

  cout << endl;
  cout << "END" << endl;

} catch(const exception &e) {
  cerr <<  "ERROR (" << typeid(e).name() << "): " << e.what() << endl;
} // catch

  // cout << "type CR to continue ...";
  // getchar();

  return 0;
} // main

#endif


// end of Grammar.cpp
//======================================================================
