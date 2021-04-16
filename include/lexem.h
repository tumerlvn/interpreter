#ifndef _LEXEM_H
#define _LEXEM_H

#include <string>
#include "const.h"

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
    //static const int PRIORITY[];
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

#endif
