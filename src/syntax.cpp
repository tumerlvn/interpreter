#include "syntax.h"

// std::vector<Lexem *> buildPostfix(std::vector<Lexem *> infix) {
//     std::vector<Lexem *> operators;
//     std::vector<Lexem *> result;
//     for (int i = 0; i < infix.size(); i++) {
//         if (infix[i]->type() == NUMBER || infix[i]->type() == VARIABLE) {
//             result.push_back(infix[i]);
//         } else if (infix[i]->type() == OPER) {
//             if (operators.empty()) {
//                 operators.push_back(infix[i]);
//             } else if (infix[i]->getType() == LBRACKET) {
//                 operators.push_back(infix[i]);
//             } else if (infix[i]->getType() == RBRACKET) {
//                 while (operators.back()->getType() != LBRACKET) {
//                     result.push_back(operators.back());
//                     operators.pop_back();
//                 }
//                 operators.pop_back();
//             } else if (operators.back()->getPriority() >= infix[i]->getPriority() && operators.back()->getType() != LBRACKET) {
//                 result.push_back(operators.back());
//                 operators.pop_back();
//                 operators.push_back(infix[i]);
//             } else {
//                 operators.push_back(infix[i]);
//             }
//         }
//     }
//     while (!operators.empty()) {
//         result.push_back(operators.back());
//         operators.pop_back();
//     }
//     return result;
// }

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
    return result;
}

void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> &operators) {
    if (operators.back()->getType() == GOTO) {
        Goto *lexemgoto = (Goto *)operators.back();
        lexemgoto->setRow(LABELS[lexemvar->getName()]);
    }
}
