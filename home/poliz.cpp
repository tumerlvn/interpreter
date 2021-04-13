#include <iostream>
#include <string>
#include <vector>
#include <map>

enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    PLUS, MINUS,
    MULTIPLY
};

enum LEXEM_TYPE {
    LEXEM,
    OPER,
    NUMBER,
    VARIABLE
};

class Lexem {
public:
    Lexem();
    virtual LEXEM_TYPE type();
    virtual OPERATOR getType() const;
    virtual int getPriority() const;
    virtual int getValue() const;
    virtual int getValue(const int& left, const int& right);
    virtual void print();
};

class Number : public Lexem {
    int value;
public:
    Number();
    Number(int value);
    LEXEM_TYPE type();
    int getValue() const;
    void print();
};

class Oper : public Lexem {
    OPERATOR opertype;
    static int PRIORITY[];
public:
    Oper();
    Oper(char oper);
    LEXEM_TYPE type();
    OPERATOR getType() const;
    int getPriority() const;
    int getValue(const int& left, const int& right);
    void print();
};

class Variable : public Lexem {
    std::string name;
public:
    Variable();
    int getValue();
    void setValue(int value);
    LEXEM_TYPE type();
};

std::map<std::string, Variable*> MAP_OF_VARS;

std::vector<Lexem *> parseLexem(std::string codeline);
std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix);
int evaluatePoliz(std::vector<Lexem *> poliz);

int main() {
    std::string codeline;
    std::vector<Lexem *> infix;
    std::vector<Lexem *> postfix;
    int value;
    while (std::getline(std::cin, codeline)) {
        if (!codeline.empty()) {
            infix = parseLexem(codeline);
            postfix = buildPoliz(infix);
            value = evaluatePoliz(postfix);
            std::cout << value << std::endl;
        }
    }
    return 0;
}

int Oper::PRIORITY[] = {
    -1, -1,
    0,
    1, 1,
    2
};

Lexem::Lexem() {

}

LEXEM_TYPE Lexem::type() {return LEXEM;}
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

LEXEM_TYPE Number::type() {
    return NUMBER;
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
        case '=':
            opertype = ASSIGN;
            break;

    }
}

LEXEM_TYPE Oper::type() {
    return OPER;
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
        case PLUS:
            return l + r;
        case MINUS:
            return l - r;
        case MULTIPLY:
            return l * r;
    }
    return 0;
}

void Oper::print() {
    switch (opertype) {
        case PLUS:
            std::cout << '+';
            break;
        case MINUS:
            std::cout << '-';
            break;
        case MULTIPLY:
            std::cout << '*';
            break;
        case LBRACKET:
            std::cout << '(';
            break;
        case RBRACKET:
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
        if (infix[i]->type() == NUMBER) {
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
            } else if (operators.back()->getPriority() >= infix[i]->getPriority() && operators.back()->getType() != 3) {
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

int evaluatePoliz(std::vector<Lexem *> poliz) {
    for (int i = 0; i < poliz.size(); i++) {
        std::cout << "|";
        poliz[i]->print();
    }
    std::cout << std::endl;
    std::vector<int> stack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i]->type() == NUMBER) {
            stack.push_back(poliz[i]->getValue());
        } else if (poliz[i]->type() == OPER) {
            int tmp2 = stack.back();
            stack.pop_back();
            int tmp1 = stack.back();
            stack.pop_back();
            stack.push_back(poliz[i]->getValue(tmp1, tmp2));
        }
    }
    return stack.back();
}
