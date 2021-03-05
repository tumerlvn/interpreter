#ifndef _CLASSES_H
#define _CLASSES_H

#include <string>
#include <vector>

enum OPERATOR {
    PLUS, MINUS,
    MULTIPLY,
    LBRACKET, RBRACKET
};

class Lexem {
public:
    Lexem();
    virtual int type();
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
    int type();
    int getValue() const;
    void print();
};


class Oper : public Lexem {
    OPERATOR opertype;
    int PRIORITY[5] = {
        -1, -1,
        0,
        1, 1
    };
public:
    Oper();
    Oper(char oper);
    int type();
    OPERATOR getType() const;
    int getPriority() const;
    int getValue(const int& left, const int& right);
    void print();
};

std::vector<Lexem *> parseLexem(std::string codeline);

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix);

int evaluatePoliz(std::vector<Lexem *> poliz);

#endif
