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

struct NameSpace;

class Variable : public Lexem {
    std::string name;
    NameSpace *currentSpace;
public:
    Variable();
    Variable(std::string);
    int getValue() const;
    void setValue(int value);
    LEXEM_TYPE type();
    void print();
    bool inLabelTable();
    bool inArrayTable();
    bool inFunctionTable();
    std::string getName();
    void setSpace(NameSpace *newSpace);
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

struct Function;

struct NameSpace {
    std::map<std::string, int> variablesMap;
    std::map<std::string, Array *> arraysMap;
    std::vector<Lexem *> computationVector;
    std::map<std::string, Function *> funcMap;
};

struct Function {
    int numOfArgs;
    int row;
};

extern std::map<std::string, Array *> ARRAY_TABLE;
extern std::map<std::string, int> MAP_OF_VARS;
extern std::map<std::string, int> LABELS;
extern std::map<std::string, Function> FUNCTION_TABLE;
extern std::vector<Lexem *> GLOBAL_STACK;

#endif
