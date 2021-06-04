#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include <vector>
#include <map>
#include <string>
#include "lexem.h"


int evaluatePoliz(std::vector <std::vector <Lexem *>>  &postfixLines, int row);
int initialPosition(std::vector<std::vector<Lexem *>> postfixLines);
// void clean(std::vector<Lexem *> &cleaner);
// void clean(std::vector<std::vector<Lexem *>> &cleaner);

#endif
