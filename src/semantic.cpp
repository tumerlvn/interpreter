#include "semantic.h"

#include <iostream>

int evaluatePoliz(std::vector<Lexem *> &poliz, int row) {
    // for (int i = 0; i < poliz.size(); i++) {
    //     std::cout << "|";
    //     poliz[i]->print();
    // }
    // std::cout << std::endl;
    std::vector<Lexem*> cleaner;

    std::vector<Lexem*> stack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i]->type() == NUMBER) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == VARIABLE || poliz[i]->type() == ARRAY_ELEMENT) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == OPER || poliz[i]->type() == OPERGOTO) {
            if (poliz[i]->getType() == GOTO || poliz[i]->getType() == ELSE || poliz[i]->getType() == ENDWHILE) {
                Goto *lexemgoto = (Goto *)poliz[i];
                clean(cleaner);
                return lexemgoto->getRow();
            } else if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
                Goto *lexemgoto = (Goto *)poliz[i];
                int rvalue = (int)stack.back()->getValue();
                stack.pop_back();
                if (!rvalue) {
                    clean(cleaner);
                    return lexemgoto->getRow();
                }
            } else {
                Lexem* tmp2 = stack.back();
                stack.pop_back();
                Lexem* tmp1 = stack.back();
                stack.pop_back();
                stack.push_back(poliz[i]->getValue(tmp1, tmp2));
                cleaner.push_back(stack.back());
            }
        }
    }
    //return stack.back()->getValue();
    if (!stack.empty()) {
        std::cout << stack.back()->getValue() << std::endl;
    }
    clean(cleaner);
    return row + 1;
}

void clean(std::vector<Lexem *> &cleaner) {
    for (auto &lexem: cleaner) {
        if (lexem == nullptr) continue;
        switch (lexem->type()) {
        case LEXEM:
            delete lexem;
            break;
        case NUMBER:
            delete (Number *)lexem;
            break;
        case VARIABLE:
            delete (Variable *)lexem;
            break;
        case OPER:
            delete (Oper *)lexem;
            break;
        case OPERGOTO:
            delete (Goto *)lexem;
            break;
        case ARRAY_ELEMENT:
            delete (ArrayElement *)lexem;
            break;
        }
        lexem = nullptr;
    }
}

void clean(std::vector<std::vector<Lexem *>> &cleaner) {
    for (std::vector<Lexem *> line: cleaner) {
        for (Lexem *lexem: line) {
            if (lexem == nullptr) continue;
            else {
                switch (lexem->type()) {
                case LEXEM:
                    delete lexem;
                    break;
                case NUMBER:
                    delete (Number *)lexem;
                    break;
                case VARIABLE:
                    delete (Variable *)lexem;
                    break;
                case OPER:
                    delete (Oper *)lexem;
                    break;
                case OPERGOTO:
                    delete (Goto *)lexem;
                    break;
                }

                lexem = nullptr;
            }
        }
    }
    for (std::map<std::string, Array *>::iterator it = ARRAY_TABLE.begin(); it != ARRAY_TABLE.end(); ++it) {
        delete it->second;
    }
}
