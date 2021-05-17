#ifndef _LEXEM_H
#define _LEXEM_H

#include <string>
#include <vector>
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
    Oper(OPERATOR opertype);
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
    bool inLabelTable();
    bool inArrayTable();
    std::string getName();
};

class Goto : public Oper {
    int row;
public:
    enum {UNDEFINED = -INT32_MAX};
    Goto (OPERATOR opertype);
    LEXEM_TYPE type();
    void setRow(int row);
    int getRow();
    void print();
};

class ArrayElement;

class Array {
    std::vector<int> data;
    friend class ArrayElement;
public:
    Array(int size);
    Lexem *getElement(int index);
};

class ArrayElement : public Lexem {
    int *data;
public:
    ArrayElement();
    ArrayElement(Array *array, int index);
    LEXEM_TYPE type();
    int getValue() const;
    void setValue(int value);
};

extern std::map<std::string, Array *> ARRAY_TABLE;

#endif
