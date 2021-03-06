#include "syntax.h"

#include <iostream>

std::vector<Lexem *> buildPostfix(const std::vector<Lexem *> &infix) {
    std::vector<Lexem *> operators;
    std::vector<Lexem *> result;
    //std::vector<Lexem *> brackets;
    for (const auto &lexem: infix) {
        if (lexem == nullptr)
            continue;

        if (lexem->type() == VARIABLE) {
            Variable *lexemvar = (Variable *) lexem;
            if (lexemvar->inLabelTable()) {
                joinGotoAndLabel(lexemvar, operators);
            } else if (FUNCTION_TABLE.find(((Variable*)lexem) -> getName()) != FUNCTION_TABLE.end()) {
                operators.push_back(lexem);
                continue;
            } else {
                result.push_back(lexemvar);
            }
        } else if (lexem->type() == NUMBER) {
            result.push_back(lexem);
        } else if (lexem->type() == OPER || lexem->type() == OPERGOTO) {
            //Oper *lexemoper = (Oper *)lexem;


            if (lexem->getType() == ENDIF || lexem->getType() == THEN) {
                // lexem->print();
                // std::cout << std::endl;
                continue;
            }

            if (lexem->getType() == LBRACKET || lexem->getType() == LSQUARE) {
                //brackets.push_back(lexem);
                operators.push_back(lexem);
            } else if (operators.empty()) {
                operators.push_back(lexem);
            } else if (lexem->getType() == RBRACKET) {
                //brackets.push_back(lexem);
                while (operators.back()->getType() != LBRACKET) {
                    result.push_back(operators.back());
                    operators.pop_back();
                }
                Lexem *lbracket = operators.back();
                operators.pop_back();
                if (operators.back()->type() == VARIABLE and FUNCTION_TABLE.find(((Variable*)operators.back())->getName()) != FUNCTION_TABLE.end() ) {
                    result.push_back(lbracket);
                    result.push_back(operators.back());
                    operators.pop_back();
                }
                //operators.pop_back();
            } else if (lexem->getType() == RSQUARE) {
                while (operators.back()->getType() != LSQUARE) {
                    result.push_back(operators.back());
                    operators.pop_back();
                }
                result.push_back(operators.back());
                operators.pop_back();
            } else if (operators.back()->getPriority() >= lexem->getPriority() && operators.back()->getType() != LBRACKET && operators.back()->getType() != LSQUARE) {
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
    //cleanBrackets(brackets);
    return result;
}

void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> &operators) {
    if (operators.back()->getType() == GOTO) {
        Goto *lexemgoto = (Goto *)operators.back();
        lexemgoto->setRow(LABELS[lexemvar->getName()]);
    }
}

// void cleanBrackets(std::vector<Lexem *> &brackets) {
//     for (Lexem *bracket: brackets) {
//         delete (Oper *)bracket;
//         bracket = nullptr;
//     }
// }
