#ifndef _LEXICAL_H
#define _LEXICAL_H

#include <string>
#include <vector>
#include "lexem.h"

Lexem* getOper(const std::string &codeline, int pos, int &next);
Lexem* getNum(const std::string &codeline, int pos, int &next);
Lexem* scanVar(const std::string &codeline, int pos, int &next);
std::vector<Lexem *> parseLexem(const std::string &codeline);

#endif
