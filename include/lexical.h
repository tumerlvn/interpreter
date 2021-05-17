#ifndef _LEXICAL_H
#define _LEXICAL_H

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "lexem.h"

Lexem* getOper(const std::string &codeline, int pos, int &next);
Lexem* getNum(const std::string &codeline, int pos, int &next);
Lexem* scanVar(const std::string &codeline, int pos, int &next);
std::vector<Lexem *> parseLexem(const std::string &codeline);
void initLabels(std::vector <Lexem *> &infix, int row);
ERROR_CODES initArrays(std::vector <Lexem *> &infix, int row);
void initJumps(std::vector <std::vector <Lexem *>> &infixLines);

//
#endif
