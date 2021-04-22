#include "semantic.h"

#include <iostream>

int evaluatePoliz(std::vector<Lexem *> poliz, int row) {
    // // for (int i = 0; i < poliz.size(); i++) {
    // //     std::cout << "|";
    // //     poliz[i]->print();
    // // }
    // std::cout << std::endl;
    std::vector<Lexem*> stack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i]->type() == NUMBER) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == VARIABLE) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == OPER) {
            if (poliz[i]->getType() == GOTO) {
                Goto *lexemgoto = (Goto *)poliz[i];
                return lexemgoto->getRow();
            } else {
                Lexem* tmp2 = stack.back();
                stack.pop_back();
                Lexem* tmp1 = stack.back();
                stack.pop_back();
                stack.push_back(poliz[i]->getValue(tmp1, tmp2));
            }
        }
    }
    //return stack.back()->getValue();
    if (!stack.empty()) {
        std::cout << stack.back()->getValue() << std::endl;
    }
    return row + 1;
}
