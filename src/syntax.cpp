#include "syntax.h"

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
    std::vector<Lexem *> operators;
    std::vector<Lexem *> result;
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i]->type() == NUMBER || infix[i]->type() == VARIABLE) {
            result.push_back(infix[i]);
        } else if (infix[i]->type() == OPER) {
            if (operators.empty()) {
                operators.push_back(infix[i]);
            } else if (infix[i]->getType() == LBRACKET) {
                operators.push_back(infix[i]);
            } else if (infix[i]->getType() == RBRACKET) {
                while (operators.back()->getType() != LBRACKET) {
                    result.push_back(operators.back());
                    operators.pop_back();
                }
                operators.pop_back();
            } else if (operators.back()->getPriority() >= infix[i]->getPriority() && operators.back()->getType() != LBRACKET) {
                result.push_back(operators.back());
                operators.pop_back();
                operators.push_back(infix[i]);
            } else {
                operators.push_back(infix[i]);
            }
        }
    }
    while (!operators.empty()) {
        result.push_back(operators.back());
        operators.pop_back();
    }
    return result;
}
