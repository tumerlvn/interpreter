#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include <vector>
#include "lexem.h"


int evaluatePoliz(std::vector<Lexem *> &poliz, int row);
void clean(std::vector<Lexem *> &cleaner);
void clean(std::vector<std::vector<Lexem *>> &cleaner);

#endif
