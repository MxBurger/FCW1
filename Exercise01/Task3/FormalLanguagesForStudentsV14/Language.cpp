#include "Language.h"
#include "Grammar.h"
#include <memory>
#include <unordered_set>

Language::Language() {}

Language::~Language() {
    for (auto* seq : sentences) {
        delete seq;
    }
}

void Language::addSentence(Sequence *sentence) {
    sentences.insert(sentence);
}

bool Language::hasSentence(const Sequence *s) const {
    for (const auto* seq : sentences) {
        if (*seq == *s) return true;
    }
    return false;
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
