#ifndef _SYNTAX_H
#define _SYNTAX_H

#include <vector>
#include "lexem.h"

std::vector<Lexem *> buildPostfix(const std::vector<Lexem *> &infix);
void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> &operators);
//void cleanBrackets(std::vector<Lexem *> &brackets);

#endif
