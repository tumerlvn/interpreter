#include "syntax.h"

#include <iostream>

std::vector<Lexem *> buildPostfix(const std::vector<Lexem *> &infix) {
    std::vector<Lexem *> operators;
    std::vector<Lexem *> result;
    for (const auto &lexem: infix) {
        if (lexem == nullptr)
            continue;

        if (lexem->type() == VARIABLE) {
            Variable *lexemvar = (Variable *) lexem;
            if (lexemvar->inLabelTable()) {
                joinGotoAndLabel(lexemvar, operators);
            } else {
                result.push_back(lexemvar);
            }
        } else if (lexem->type() == NUMBER) {
            result.push_back(lexem);
        } else if (lexem->type() == OPER) {
            //Oper *lexemoper = (Oper *)lexem;
            if (lexem->getType() == ENDIF || lexem->getType() == THEN) {
                // lexem->print();
                // std::cout << std::endl;
                continue;
            }

            if (operators.empty()) {
                operators.push_back(lexem);
            } else if (lexem->getType() == LBRACKET) {
                operators.push_back(lexem);
            } else if (lexem->getType() == RBRACKET) {
                while (operators.back()->getType() != LBRACKET) {
                    result.push_back(operators.back());
                    operators.pop_back();
                }
                operators.pop_back();
            } else if (operators.back()->getPriority() >= lexem->getPriority() && operators.back()->getType() != LBRACKET) {
                result.push_back(operators.back());
                operators.pop_back();
                operators.push_back(lexem);
            } else {
                operators.push_back(lexem);
            }
        }
    }
    while (!operators.empty()) {
        result.push_back(operators.back());
        operators.pop_back();
    }
    // for (int i = 0; i < result.size(); i++) {
    //     std::cout << "|";
    //     result[i]->print();
    // }
    // std::cout << std::endl;
    return result;
}

void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> &operators) {
    if (operators.back()->getType() == GOTO) {
        Goto *lexemgoto = (Goto *)operators.back();
        lexemgoto->setRow(LABELS[lexemvar->getName()]);
    }
}
