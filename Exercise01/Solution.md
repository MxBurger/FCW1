# 1. Grammatiken – Grundbegriffe

## a) Bestimmen Sie die Mengen VT und VN
```
Satzsymbol = DataStat
Vt = { DataDeclRest, DataDeclRest, DataNameList, 
       DataName, DataValueList, DataValue, DataDoList,
       DDataDoListRest }
Vn = { "DATA",",", "/", id, num, "*", "+", "-", str, "(", ")", expr }

Anmerkung: id, num, str und expr sind Terminalklassen!
ε ist kein Terminalsymbol
```

## b) Geben Sie den/die kürzesten Satz/Sätze an, den/die man mit dieser Grammatik bilden kann.

DS => DATA *DD* *DDR* =>
DATA *DNL* / *DVL* / *DDR* =>
DATA *DN* / *DVL* / *DDR* =>
DATA id / *DVL* / *DDR* =>
DATA id / *DV* / *DDR* =>
DATA id / id / *DDR* =>
DATA id / id /

## c) Ermitteln Sie alle rekursiven Nonterminalsymbole. Geben Sie für jedes dieser Nonterminalsymbole an, ob es direkt- oder indirekt- und links-, zentral- oder rechtsrekursiv ist.

**NT** ...Nonterminalsymbol
**d/i**...direkt oder indirekt rekursiv
**l/z/r**...links, zentral oder rechts rekursiv

| NT  | d / i | l / z / r |
|---  |---    | ---       |
| DDR  |   d |  l   |
| DNL  |   d |  r   |
| DVL  |   d |  l   |
| DDL  |   d |  z   |
| DDL  |   i |  z   |
| DDLR |   d |  l   |
| DDLR |   i |  z   |


## d) Transformieren Sie die gegebene Grammatik in das Regelsystem der formalen Sprachen. Welche Grammatikschreibweise halten Sie für lesbarer? Begründen Sie Ihre Antwort.

```
DataStat                -> DATA DataDecl DataDeclRest
DataDeclRest            -> ε | DataDeclRest OptionalComma DataDecl
OptionalComma           -> ε | ,
DataDecl                -> DataNameList / DataValueList /
DataNameList            -> DataName | DataName , DataNameList
DataName                -> id | DataDoList
DataValueList           -> DataValue | DataValueList , DataValue
DataValue               -> NumOrId OptionalValue | SignedNumOrStr
NumOrId                 -> num | id
NumOrStr                -> num | str
OptionalValue           -> ε | * id | * OptinalSign num | * str
SignedNumOrStr          -> OptinalSign num | OptinalSign str
OptinalSign             -> ε | + | -
DataDoList              -> ( ODDL DataDoListRest )
ODDL                    -> IdList | DataDoList
IdList                  -> id ( CommaSeparatedId ) 
CommaSeparatedId        -> ε | , id CommaSeparatedId
DataDoListRest          -> ε | DataDoListRest , 
DataDoListRestOption    -> id Expression | DataDoList
Expression              -> ( ExpressionList ) | = expr , expr expr | = expr , expr
ExpressionList          -> expr | expr , ExpressionList
```

Die Wirthsch'e EBNF halte ich für lesbarer, da die zusätzlichen Metasymbole sehr
ausdrucksstark sind und die Einführung zusätzlicher Nonterminalsymbole teilweise überflüssig machen. Die von Niklaus Wirth gewählten Metasymbole sind außerdem leicht in herkömmlichen Texteditoren zu verwenden. (keine fancy zeilenübergreifenden Symbole)


## e) Zeichnen Sie den Syntaxbaum für folgenden Satz, verwenden Sie dazu die gegebene Grammatik G(DataStat) von oben:
```
DATA id, id / num * str /, ( id(id), id = expr, expr ) / num * num /
```

![Syntaxtree](pictures/Syntaxtree.png)

## Gibt es mehrere Syntaxbäume für diesen Satz? (Mit Begründung!)

In jedem Fall gibt es nur eine mögliche Alternative beim Ersetzen der Regeln. Deshalb gibt es zu diesem Satz mit der gegebenen Grammatik nur einen Syntaxbaum.



# 2. Konstruktion einer Grammatik

Z...Zahl
ZF...Ziffernfolge
UZ...Ungerade Ziffer
MZ...Mehrstellige Zahl
SZ...Start-Ziffer
MTZ...Mittlere Ziffer

```
Z -> + ZF | - ZF | ZF
ZF -> UZ | MZ
UZ -> 1 | 3 | 5 | 7 | 9 
MZ -> SZ MTZ UZ
SZ -> 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
MTZ -> 0 MTZ | 1 MTZ | 2 MTZ | 3 MTZ | 4 MTZ | 5 MTZ | 6 MTZ | 7 MTZ | 8 MTZ | 9 MTZ |  ε
```

in Wirth'scher EBNF
```
Z = [ "+" | "-" ] 
[
    ( "1", "2", "3", "4", "5", "6", "7", "8", "9" )
    { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }
]
( "1" | "3" | "5" | "7" | "9" ) .
```

# 3. Oo-Implementierung von Grammatiken

## a) `Grammar *newEpsilonFreeGrammarOf(const Grammar *g);`

Die Lösungsidee ist die Beseitigung von ε-Regeln durch systematische Erzeugung aller möglichen Alternativen ohne Grammatikregeln bei denen ein Nonterminalsymbol zu  ε abgeleitet wird . 

1. Identifiziere alle löschbaren Nonterminalsymbole
2. Generiere für jede Alternative mit löschbaren Symbolen alle Kombinationen, wo diese entweder vorhanden sind oder weggelassen werden
3. Füge einen neuen Startzustand hinzu, falls das ursprüngliche Startsymbol löschbar war

```cpp
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

            // Generate all combinations (deletable ^ 2) of deletable symbols
            int combinations = static_cast<int>(pow(2, deletableIndices.size()));
            for (int i = 0; i < combinations; i++) {
                Sequence* newAlt = new Sequence();
                for (int j = 0; j < alt->length(); j++) {
                    // Check if current position is deletable
                    auto it = find(deletableIndices.begin(), deletableIndices.end(), j);
                    if (it == deletableIndices.end()) {
                        // Not deletable - always include
                        newAlt->append(alt->at(j));
                    } else {
                        // Deletable - include only if bit is set
                        int bitPos = it - deletableIndices.begin();
                        if (!(i & (1 << bitPos))) {
                            newAlt->append(alt->at(j));
                        }
                    }
                }
                // Only add non-empty alternatives
                if (newAlt->length() > 0) {
                    builder->addRule(nt, newAlt);
                } else {
                    delete newAlt; // Clean up empty alternatives
                }
            }
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
```


### Konsolenausgabe
```
START Main

TESTCASE 4

original grammar:

G(S):
S -> A B C
A -> eps | B B
B -> C C | a
C -> A A | b
---
VNt = { A, B, C, S }, deletable: { A, B, C, S }
VT  = { a, b }


epsilon free grammar:

G(S'):
S' -> eps | S
S -> A | A B | A B C | A C | B | B C | C
A -> B | B B
B -> C | C C | a
C -> A | A A | b
---
VNt = { A, B, C, S, S' }, deletable: { S' }
VT  = { a, b }



symbol pool: 2 terminals and 5 nonterminals
  terminals    = { b, a }
  nonterminals = { S', B, C, A, S }

elapsed time: 0.017

END Main


----------------------------------------------------
report generated on destruction of ObjectCounter<>s:

Grammar:
  +2 -2 = 0 alive

TSymbol:
  +2 -2 = 0 alive

Sequence:
  +55 -55 = 0 alive

Vocabulary<Symbol>::XSymbol:
  +64 -64 = 0 alive

NTSymbol:
  +5 -5 = 0 alive

Vocabulary<Symbol>:
  +4 -4 = 0 alive

Vocabulary<TSymbol>:
  +4 -4 = 0 alive

Vocabulary<NTSymbol>:
  +7 -7 = 0 alive

RulesMap:
  +4 -4 = 0 alive

GrammarBuilder:
  +2 -2 = 0 alive

SymbolPoolData:
  +1 -1 = 0 alive

SymbolPool:
  +7 -7 = 0 alive

SequenceSet:
  +19 -19 = 0 alive

Process finished with exit code 0

```

## b) `Language *languageOf(const Grammar *g, int maxLen);`

Die Lösungsidee ist eine systematische Generierung aller möglichen Sätze bis zur maximalen Länge durch:

1. Starte mit dem Startsymbol
2. Ersetze iterativ Nonterminalsymbole durch ihre Alternativen
3. Sobald eine Sequenz nur aus Terminalsymbolen besteht und nicht länger als maxLen ist, füge sie zur Sprache hinzu
4. Fortsetzung bis keine neuen gültigen Sätze mehr gefunden werden können oder zu überprüfende Sequenzen die maximale Länge überschreiten würden

```cpp
#include "Language.h"
#include "Grammar.h"

Language::Language() {}

Language::~Language() {
    for (auto* seq : sentences) {
        delete seq;
    }
}

void Language::addSentence(Sequence *sentence) {
    sentences.insert(sentence);
}

size_t Language::size() const {
    return sentences.size();
}

set<Sequence *>::iterator Language::begin() const { return sentences.begin(); }

set<Sequence *>::iterator Language::end() const { return sentences.end(); }

std::ostream &operator<<(std::ostream &os, const Language &l) {
    for(auto* seq : l) {
        os << *seq << std::endl;
    }
    return os;
}

Language* languageOf(const Grammar* g, int maxLen) {

    Language* lang = new Language();

    // initialize set of sequences to check with the start symbol
    std::set<Sequence> toCheck;
    Sequence start(g->root);
    toCheck.insert(start);

    while (!toCheck.empty()) {
        // Get and remove first sequence to check
        Sequence current = *toCheck.begin();
        toCheck.erase(toCheck.begin());

        // If sequence contains only terminals and length <= maxLen, add to language
        if (current.hasTerminalsOnly() && current.length() <= maxLen) {
            lang->addSentence(new Sequence(current));
        }

        // Try to expand each nonterminal in the sequence
        for (size_t pos = 0; pos < current.length(); pos++) {
            Symbol* sym = current.at(pos);
            if (sym->isNT()) {
                NTSymbol* nt = dynamic_cast<NTSymbol*>(sym);
                // For each rule with this NT on the left side
                for (auto& rule : g->rules) {
                    if (rule.first == nt) {
                        // For each alternative of the rule
                        for (Sequence* alt : rule.second) {
                            // Create new sequence with the alternative at the position of the NT
                            Sequence newSeq(current);
                            newSeq.replaceSymbolAt(pos, alt);

                            // If resulting sequence is smaller maxLen, add to sequences to check
                            if (newSeq.length() <= maxLen) {
                                toCheck.insert(newSeq);
                            }
                        }
                    }
                }
            }
        }
    }
    return lang;
}
```

### Konsolenausgabe
```
START Main

TESTCASE 5

language of grammar:
a a b b a b
a a b b b a
a a b a b b
a a b b
a a a b b b
a b
a b a a b b
b b a a b a
b b a a
a b b b a a
b a a a b b
b a a b
a b b a a b
b a a b b a
a b a b b a
a b a b a b
a b b a b a
b b a a a b
b a b a b a
b a b a
a b b a
b a
a b a b
b a b a a b
b a a b a b
b a b b a a
b b b a a a
b b a b a a


Total number of sentences: 28

symbol pool: 2 terminals and 3 nonterminals
  terminals    = { b, a }
  nonterminals = { B, A, S }

elapsed time: 0.02

END Main


----------------------------------------------------
report generated on destruction of ObjectCounter<>s:

Grammar:
  +1 -1 = 0 alive

TSymbol:
  +2 -2 = 0 alive

Sequence:
  +661 -661 = 0 alive

Vocabulary<Symbol>::XSymbol:
  +25 -25 = 0 alive

NTSymbol:
  +3 -3 = 0 alive

Vocabulary<Symbol>:
  +2 -2 = 0 alive

Vocabulary<TSymbol>:
  +2 -2 = 0 alive

Vocabulary<NTSymbol>:
  +2 -2 = 0 alive

RulesMap:
  +2 -2 = 0 alive

GrammarBuilder:
  +1 -1 = 0 alive

SymbolPoolData:
  +1 -1 = 0 alive

SymbolPool:
  +4 -4 = 0 alive

SequenceSet:
  +7 -7 = 0 alive

Process finished with exit code 0
```

## c) `bool Language::hasSentence(const Sequence *s) const;`

```cpp
bool Language::hasSentence(const Sequence *s) const {
    for (const auto* seq : sentences) {
        if (*seq == *s) return true;
    }
    return false;
}
```

### Testfunktion
```cpp
void testHasSentence(Language* lang, Sequence* seq, bool expected) {
  bool actual = lang->hasSentence(seq);
  cout << *seq << " --- Expected: " << (expected ? "true" : "false") << " - "
               << "Actual: " << (actual ? "true" : "false") << std::endl;
  delete seq;
}
```

### Konsolenausgabe

```
START Main

TESTCASE 6

language of grammar:
a a b b
a b
a a b a b b
a a a b b b
a b a a b b
b b a a b a
b b a a
a a b b a b
a a b b b a
b b a a a b
b a b a b a
a b a b
a b b a b a
b a a a b b
a b b b a a
b a a b
b a a b a b
b a a b b a
a b a b a b
a b b a a b
a b b a
b a b a a b
a b a b b a
b a
b a b b a a
b a b a
b b a b a a
b b b a a a

a b --- Expected: true - Actual: true
a a b --- Expected: false - Actual: false
a a a b --- Expected: false - Actual: false
a a a a b --- Expected: false - Actual: false
a b b a --- Expected: true - Actual: true
a b b a b a --- Expected: true - Actual: true
a a a a b b b b --- Expected: false - Actual: false

symbol pool: 2 terminals and 3 nonterminals
  terminals    = { b, a }
  nonterminals = { B, A, S }

elapsed time: 0.03

END Main


----------------------------------------------------
report generated on destruction of ObjectCounter<>s:

Grammar:
  +1 -1 = 0 alive

TSymbol:
  +2 -2 = 0 alive

Sequence:
  +668 -668 = 0 alive

Vocabulary<Symbol>::XSymbol:
  +25 -25 = 0 alive

NTSymbol:
  +3 -3 = 0 alive

Vocabulary<Symbol>:
  +2 -2 = 0 alive

Vocabulary<TSymbol>:
  +2 -2 = 0 alive

Vocabulary<NTSymbol>:
  +2 -2 = 0 alive

RulesMap:
  +2 -2 = 0 alive

GrammarBuilder:
  +1 -1 = 0 alive

SymbolPoolData:
  +1 -1 = 0 alive

SymbolPool:
  +11 -11 = 0 alive

SequenceSet:
  +7 -7 = 0 alive

Process finished with exit code 0
```