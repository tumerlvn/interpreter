#include "classes.h"
#include <iostream>

Lexem::Lexem() {

}

int Lexem::type() {return 0;}
OPERATOR Lexem::getType() const {return PLUS;}
int Lexem::getPriority() const{return 0;}
int Lexem::getValue() const {return 0;}
int Lexem::getValue(const int& left, const int& right) {return 0;}
void Lexem::print() {}

Number::Number() {
    value = 0;
}

Number::Number(int value) {
    this->value = value;
}

int Number::type() {
    return 1;
}

int Number::getValue() const {
    return value;
}

void Number::print() {
    std::cout << value;
}



Oper::Oper(char oper) {
    switch (oper) {
    case '+':
        opertype = PLUS;
        break;
    case '-':
        opertype = MINUS;
        break;
    case '*':
        opertype = MULTIPLY;
        break;
    case '(':
        opertype = LBRACKET;
        break;
    case ')':
        opertype = RBRACKET;
        break;
    }
}

int Oper::type() {
    return 2;
}

OPERATOR Oper::getType() const {
    return opertype;
}

int Oper::getPriority() const {
    return PRIORITY[opertype];
}

int Oper::getValue(const int& left, const int& right) {
    int l = left;
    int r = right;
    switch (this->getType()) {
    case 0:
        return l + r;
    case 1:
        return l - r;
    case 2:
        return l * r;
    }
    return 0;
}

void Oper::print() {
    switch (opertype) {
    case 0:
        std::cout << '+';
        break;
    case 1:
        std::cout << '-';
        break;
    case 2:
        std::cout << '*';
        break;
    case 3:
        std::cout << '(';
        break;
    case 4:
        std::cout << ')';
        break;
    }
}

std::vector<Lexem *> parseLexem(std::string codeline) {
    std::vector<Lexem *> res;
    int i = 0;
    int tmp = 0;
    while (codeline[i] != '\0') {
        char ch = codeline[i];
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            i++;
            continue;
        } else if ('0' <= ch && ch <= '9') {
            tmp = tmp * 10 + ch - '0';
            if (codeline[i+1] < '0' || '9' < codeline[i+1]) {
                Lexem *tmpNum = new Number(tmp);
                res.push_back(tmpNum);
                tmp = 0;
            }
        } else {
            Lexem *tmpOper = new Oper(ch);
            res.push_back(tmpOper);
        }
        i++;
    }
    return res;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
    std::vector<Lexem *> operators;
    std::vector<Lexem *> result;
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i]->type() == 1) {
            result.push_back(infix[i]);
        } else if (infix[i]->type() == 2) {
            if (operators.empty()) {
                operators.push_back(infix[i]);
            } else {
                if (infix[i]->getType() == 3) {
                    operators.push_back(infix[i]);
                } else if (infix[i]->getType() == 4) {
                    while (operators.back()->getType() != 3) {
                        result.push_back(operators.back());
                        operators.pop_back();
                    }
                    operators.pop_back();
                } else if (operators.back()->getPriority() >= infix[i]->getPriority() && operators.back()->getType() != 3) {
                    result.push_back(operators.back());
                    operators.pop_back();
                    operators.push_back(infix[i]);
                } else {
                    operators.push_back(infix[i]);
                }
            }
        }
    }
    while (!operators.empty()) {
        result.push_back(operators.back());
        operators.pop_back();
    }
    return result;
}

int evaluatePoliz(std::vector<Lexem *> poliz) {
    for (int i = 0; i < poliz.size(); i++) {
        std::cout << "|";
        poliz[i]->print();
    }
    std::cout << std::endl;
    std::vector<int> stack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i]->type() == 1) {
            stack.push_back(poliz[i]->getValue());
        } else if (poliz[i]->type() == 2) {
            int tmp2 = stack.back();
            stack.pop_back();
            int tmp1 = stack.back();
            stack.pop_back();
            stack.push_back(poliz[i]->getValue(tmp1, tmp2));
        }
    }
    return stack.back();
}
