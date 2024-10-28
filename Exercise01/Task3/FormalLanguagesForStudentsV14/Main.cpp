// Main.cpp:                                             HDO, 2004-2022
// --------
// Main program for the object-oriented representation of formal
// languages using classes for symbols, sequences and grammars.
// ====================================================================

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
#endif


void testHasSentence(Language* lang, Sequence* seq, bool expected) {
  bool actual = lang->hasSentence(seq);
  cout << *seq << " --- Expected: " << (expected ? "true" : "false") << " - "
               << "Actual: " << (actual ? "true" : "false") << std::endl;
  delete seq;
}


int main(int argc, char * argv[]) {

  installSignalHandlers();

  cout << "START Main" << endl;
  cout << endl;
  startTimer();

try {

  SymbolPool *sp = new SymbolPool();
   // cout << *sp << endl;

  GrammarBuilder *gb1 = nullptr;
  GrammarBuilder *gb2 = nullptr;
  GrammarBuilder *gb3 = nullptr;
  GrammarBuilder *gb4 = nullptr;
  GrammarBuilder *gb5 = nullptr;

  Grammar *g1 = nullptr;
  Grammar *g2 = nullptr;
  Grammar *g3 = nullptr;
  Grammar *g4 = nullptr;
  Grammar *g5 = nullptr;


// *** test case selection: 1, 2, 3, 4, 5 or 6 ***
#define TESTCASE 4
// ***************************************

  cout << "TESTCASE " << TESTCASE << endl << endl;

#if TESTCASE == 1 // programmatical grammar construction

  // G(S):
  // S -> A ;
  // A -> a B | B B b
  // B -> b | a b

  NTSymbol *S  = sp->ntSymbol("S");
  NTSymbol *A  = sp->ntSymbol("A");
  NTSymbol *B  = sp->ntSymbol("B");

   TSymbol *a  = sp-> tSymbol("a");
   TSymbol *b  = sp-> tSymbol("b");
   TSymbol *sc = sp-> tSymbol(";");

  gb1 = new GrammarBuilder(S);

#if 0 // with separate Sequence variables ...

  Sequence *seq1 = new Sequence({A, sc});
  Sequence *seq2 = new Sequence({a, B});
  Sequence *seq3 = new Sequence({B, B, b});
  Sequence *seq4 = new Sequence(b);
  Sequence *seq5 = new Sequence({a, b});

  gb1->addRule(S, seq1);
  gb1->addRule(A, {seq2, seq3});
  gb1->addRule(B, {seq4, seq5});

#else // .. much simpler with Sequences constructed in place

  gb1->addRule(S,  new Sequence({A, sc}));
  gb1->addRule(A, {new Sequence({a, B}),
                   new Sequence({B, B, b})});
  gb1->addRule(B, {new Sequence(b),
                   new Sequence({a, b})});
#endif

  g1 = gb1->buildGrammar();
  cout << "grammar constructed programmatically:" << endl << *g1 << endl;


#elif TESTCASE == 2 // grammar construction from text file

  gb2 = new GrammarBuilder(string("G.txt"));
  g2 = gb2->buildGrammar();
  // or for short: g2 = GrammarBuilder(string("G.txt")).buildGrammar();

  cout << "grammar from text file:" << endl << *g2 << endl;


#elif TESTCASE == 3 // grammar construction from C string literal

  gb3 = new GrammarBuilder(
    "G(S):                          \n\
     S -> E ;                       \n\
     E -> a A b E | b B a E | eps   \n\
     A -> a A b A | eps             \n\
     B -> b B a B | eps             ");
  g3 = gb3->buildGrammar();
  // or for short: g3 = GrammarBuilder("...").buildGrammar();

  cout << "grammar from C string:" << endl << *g3 << endl;

#elif TESTCASE == 4 // epsilon free grammar

  gb4 = new GrammarBuilder(
      "G(S):           \n\
     S -> A B C                 \n\
     A -> B B | eps             \n\
     B -> C C | a               \n\
     C -> A A | b             ");
  g4 = gb4->buildGrammar();
  cout << "original grammar:" << endl << *g4 << endl;

  auto epsFreeGrammer = newEpsilonFreeGrammarOf(g4);
  cout << "epsilon free grammar:" << endl << *epsFreeGrammer << endl;
  delete epsFreeGrammer;

#elif TESTCASE == 5 // language of

  gb5 = new GrammarBuilder(
      "G(S):           \n\
     S -> a B | b A             \n\
     A -> a   | a S | b A A     \n\
     B -> b   | b S | a B B         ");
  g5 = gb5->buildGrammar();
  Language* lang = languageOf(g5, 6);

  cout << "language of grammar:" << endl << *lang << endl;

  cout << endl << "Total number of sentences: " << lang->size() << std::endl;

  delete lang;

#elif TESTCASE == 6 // language of

  gb5 = new GrammarBuilder(
      "G(S):           \n\
     S -> a B | b A             \n\
     A -> a   | a S | b A A     \n\
     B -> b   | b S | a B B         ");
  g5 = gb5->buildGrammar();
  Language* lang = languageOf(g5, 6);

  cout << "language of grammar:" << endl << *lang << endl;

  testHasSentence(lang, new Sequence("a b"), true);
  testHasSentence(lang, new Sequence("a a b"), false);
  testHasSentence(lang, new Sequence("a a a b"), false);
  testHasSentence(lang, new Sequence("a a a a b"), false);
  testHasSentence(lang, new Sequence("a b b a"), true);
  testHasSentence(lang, new Sequence("a b b a b a"), true);
  testHasSentence(lang, new Sequence("a a a a b b b b"), false);


  delete lang;

#else // none of the TESTCASEs above

  cerr << "ERROR: invalid TESTCASE " << TESTCASE << endl;

#endif

  delete gb1;
  delete gb2;
  delete gb3;
  delete gb4;
  delete gb5;

  delete g1;
  delete g2;
  delete g3;
  delete g4;
  delete g5;

  cout << endl << *sp << endl; // final contents of symbol pool
  delete sp;

 } catch(const exception &e) {
  cerr <<  "ERROR (" << typeid(e).name() << "): " << e.what() << endl;
} // catch

  stopTimer();
  cout << "elapsed time: " << elapsed() << endl;
  cout << endl;
  cout << "END Main" << endl;

  // cout << "type CR to continue ...";
  // getchar();

  return 0;
} // main




// end of Main.cpp
//======================================================================
