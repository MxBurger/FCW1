// Language.h
#pragma once
#include <set>
#include <string>
#include "Grammar.h"
#include "SequenceStuff.h"

class Language {

private:
    std::set<Sequence*> sentences;

public:
    Language();

    ~Language();

    void addSentence(Sequence* sentence);

    bool hasSentence(const Sequence* s) const;

    size_t size() const;

    set<Sequence*>::iterator begin() const;

    set<Sequence*>::iterator  end() const;

};

std::ostream &operator<<(std::ostream &os, const Grammar &g);

Language* languageOf(const Grammar* g, int maxLen);