#include <iostream>
#include <string>
#include <vector>
#include <map>

enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    EQ, NEQ,
    SHL, SHR,
    LEQ, LT, GEQ, GT,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};

const std::string OPERTEXT[] = {
    "(", ")",
    "=",
    "or",
    "and",
    "|",
    "^",
    "&",
    "==", "!=",
    "<<", ">>",
    "<=", "<", ">=", ">",
    "+", "-",
    "*", "/", "%"
};

const int operAmount = sizeof(OPERTEXT)/sizeof(OPERTEXT[0]);

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
    virtual Lexem* getValue(Lexem* left, Lexem* right);
    virtual void print();
    virtual void setValue(int);
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
    static const int PRIORITY[];
public:
    Oper();
    Oper(std::string oper);
    LEXEM_TYPE type();
    OPERATOR getType() const;
    int getPriority() const;
    Lexem* getValue(Lexem* left, Lexem* right);
    void print();
};

class Variable : public Lexem {
    std::string name;
public:
    Variable();
    Variable(std::string);
    int getValue() const;
    void setValue(int value);
    LEXEM_TYPE type();
    void print();
};

std::map<std::string, int> MAP_OF_VARS;

Lexem* getOper(const std::string &codeline, int pos, int &next);
Lexem* getNum(const std::string &codeline, int pos, int &next);
Lexem* scanVar(const std::string &codeline, int pos, int &next);
std::vector<Lexem *> parseLexem(const std::string &codeline);
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

bool isSeparator(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool isNumber(char ch) {
    return ('0' <= ch && ch <= '9');
}

bool isVariable(char ch) {
    return (('a' <= ch && ch <= 'z') ||
    ('A' <= ch && ch <= 'Z') ||
    (ch == '_'));
}

const int Oper::PRIORITY[] = {
    -1, -1,
    0,
    1,
    2,
    3,
    4,
    5,
    6, 6,
    7, 7,
    8, 8, 8, 8,
    9, 9,
    10, 10, 10
};

Lexem::Lexem() {

}

LEXEM_TYPE Lexem::type() {return LEXEM;}
OPERATOR Lexem::getType() const {return PLUS;}
int Lexem::getPriority() const{return 0;}
int Lexem::getValue() const {return 0;}
Lexem* Lexem::getValue(Lexem* left, Lexem* right) {return nullptr;}
void Lexem::print() {}
void Lexem::setValue(int value) {}

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



Oper::Oper(std::string oper) {
    for (int i = 0; i < operAmount; i++) {
        if (oper == OPERTEXT[i]) {
            opertype = (OPERATOR)i;
            break;
        }
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

Lexem* Oper::getValue(Lexem* left, Lexem* right) {
    int l = left->getValue();
    int r = right->getValue();
    Lexem* result;
    switch (this->getType()) {
    case PLUS:
        result = new Number(l + r);
        break;
    case MINUS:
        result = new Number(l - r);
        break;
    case MULTIPLY:
        result = new Number(l * r);
        break;
    case ASSIGN:
        if (left->type() == VARIABLE) {
            left->setValue(r);
            //std::cout << ((Variable*)left)->getValue();
            result = new Number(left->getValue());
        } else {
            result = new Number(l);
        }
        break;
    case OR:
        result = new Number(l || r);
        break;
    case AND:
        result = new Number(l && r);
        break;
    case BITOR:
        result = new Number(l | r);
        break;
    case XOR:
        result = new Number(l ^ r);
        break;
    case BITAND:
        result = new Number(l & r);
        break;
    case EQ:
        result = new Number(l == r);
        break;
    case NEQ:
        result = new Number(l != r);
        break;
    case SHL:
        result = new Number(l << r);
        break;
    case SHR:
        result = new Number(l >> r);
        break;
    case LEQ:
        result = new Number(l <= r);
        break;
    case LT:
        result = new Number(l <= r);
        break;
    case GEQ:
        result = new Number(l >= r);
        break;
    case GT:
        result = new Number(l > r);
        break;
    case DIV:
        result = new Number(l / r);
        break;
    case MOD:
        result = new Number(l % r);
        break;
    }
    delete left;
    delete right;
    return result;
}

void Oper::print() {
    std::cout << OPERTEXT[opertype];
}

Variable::Variable() {
    name = "";
}

Variable::Variable(std::string name) {
    this->name = name;
    //this->setValue(0);
}

int Variable::getValue() const {
    //std::cout << "var";
    return MAP_OF_VARS[name];
}

void Variable::setValue(int value) {
    MAP_OF_VARS[name] = value;
}

LEXEM_TYPE Variable::type() {
    return VARIABLE;
}

void Variable::print() {
    std::cout << "(" << name << ", " << this->getValue() << ")";
}

Lexem* getOper(const std::string &codeline, int pos, int &next) {
    for (int op = 0; op < operAmount; op++) {
        std::string subcodeline =
            codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            next = pos + OPERTEXT[op].size();
            return new Oper(OPERTEXT[op]);
        }
    }
    return nullptr;
}

Lexem* getNum(const std::string &codeline, int pos, int &next) {
    int i = 0;
    for (; i < codeline.size(); i++) {
        if (!isNumber(codeline[pos+i])) {
            break;
        }
    }
    if (i != 0) {
        std::string subcodeline =
            codeline.substr(pos, i);
        int tmp = stoi(subcodeline);
        next = pos + i;
        return new Number(tmp);
    }
    return nullptr;
}

Lexem* scanVar(const std::string &codeline, int pos, int &next) {
    std::string variable;
    int i = 0;
    for (; i < codeline.size(), isVariable(codeline[pos + i]); i++) {

    }
    if (i != 0) {
        variable = codeline.substr(pos, i);
        next = pos + i;
        return new Variable(variable);
    }
    return nullptr;
}

std::vector<Lexem *> parseLexem(const std::string &codeline) {
    std::vector<Lexem *> res;
    Lexem* lexem;
    for (int pos = 0, next = 0; pos < codeline.size();) {
        if (isSeparator(codeline[pos])) {
            pos++;
            continue;
        }
        lexem = getOper(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
        lexem = getNum(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
        lexem = scanVar(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
    }
    return res;
}

// std::vector<Lexem *> parseLexem(std::string codeline) {
//     std::vector<Lexem *> res;
//     int i = 0;
//     int tmp = 0;
//     std::string tmpName = "";
//     while (codeline[i] != '\0') {
//         char ch = codeline[i];
//         if (ch == ' ' || ch == '\t' || ch == '\n') {
//             i++;
//             continue;
//         } else if ('0' <= ch && ch <= '9') {
//             tmp = tmp * 10 + ch - '0';
//             if (codeline[i+1] < '0' || '9' < codeline[i+1]) {
//                 Lexem *tmpNum = new Number(tmp);
//                 res.push_back(tmpNum);
//                 tmp = 0;
//             }
//         } else if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
//             tmpName += ch;
//             if (!(('a' <= codeline[i+1] && codeline[i+1] <= 'z') || ('A' <= codeline[i+1] && codeline[i+1] <= 'Z'))) {
//                 Lexem *tmpVar = new Variable(tmpName);
//                 res.push_back(tmpVar);
//                 tmpName = "";
//             }
//         } else {
//             Lexem *tmpOper = new Oper(ch);
//             res.push_back(tmpOper);
//         }
//         i++;
//     }
//     return res;
// }

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

int evaluatePoliz(std::vector<Lexem *> poliz) {
    for (int i = 0; i < poliz.size(); i++) {
        std::cout << "|";
        poliz[i]->print();
    }
    std::cout << std::endl;
    std::vector<Lexem*> stack;
    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i]->type() == NUMBER) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == VARIABLE) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == OPER) {
            Lexem* tmp2 = stack.back();
            stack.pop_back();
            Lexem* tmp1 = stack.back();
            stack.pop_back();
            stack.push_back(poliz[i]->getValue(tmp1, tmp2));
        }
    }
    return stack.back()->getValue();
}
