#include "lexem.h"
#include <iostream>

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
    for (int i = 0; i < OP_NUM; i++) {
        if (oper == OPERTEXT[i]) {
            opertype = (OPERATOR)i;
            break;
        }
    }
}

Oper::Oper(OPERATOR opertype) {
    this->opertype = opertype;
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
        if (left->type() == VARIABLE || left->type() == ARRAY_ELEMENT) {
            left->setValue(r);
            //std::cout << ((Variable*)left)->getValue();
            result = new Number(left->getValue());
        } else {
            result = new Number(l);
        }
        break;
    case LSQUARE:
        if (left->type() == VARIABLE && ((Variable *)left)->inArrayTable()) {
            result = ARRAY_TABLE[((Variable *)left)->getName()]->getElement(r);
        } else {
            result = new Number(0);
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
        result = new Number(l < r);
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

    // if (left->type() == NUMBER) {
    //     delete (Number*)left;
    // } else if (left->type() == VARIABLE) {
    //     delete (Variable*)left;
    // }
    //
    // if (right->type() == NUMBER) {
    //     delete (Number*)right;
    // } else if (right->type() == VARIABLE) {
    //     delete (Variable*)right;
    // }
    // delete left;
    // delete right;
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

bool Variable::inLabelTable() {
    return (LABELS.find(this->name) != LABELS.end());
}

bool Variable::inArrayTable() {
    return (ARRAY_TABLE.find(this->name) != ARRAY_TABLE.end());
}

std::string Variable::getName() {
    return name;
}

Goto::Goto(OPERATOR opertype) : Oper(opertype) {
    row = UNDEFINED;
}

LEXEM_TYPE Goto::type() {
    return OPERGOTO;
}

void Goto::setRow(int row) {
    this->row = row;
}

int Goto::getRow() {
    return row;
}

void Goto::print() {
    std::cout << "[<row " << row << ">" << OPERTEXT[this->getType()] << "] ";
}

Array::Array(int size) {
    data.resize(size);
    for (int x: data) {
        x = 0;
    }
}

Lexem *Array::getElement(int index) {
    if (0 <= index && index <= data.size() - 1) {
        return new ArrayElement(this, index);
    } else {
        return nullptr;
    }
}

ArrayElement::ArrayElement() {
    data = nullptr;
}

ArrayElement::ArrayElement(Array *array, int index) {
    this->data = &(array->data[index]);
}

LEXEM_TYPE ArrayElement::type() {
    return ARRAY_ELEMENT;
}

int ArrayElement::getValue() const {
    return *data;
}

void ArrayElement::setValue(int value) {
    *data = value;
}

std::map<std::string, Array *> ARRAY_TABLE;
