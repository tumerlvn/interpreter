#ifndef _CONST_H
#define _CONST_H

#include <string>
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

enum LEXEM_TYPE {
    LEXEM,
    OPER,
    NUMBER,
    VARIABLE
};


extern const int PRIORITY[];
extern const std::string OPERTEXT[];
extern const int OP_NUM;
extern std::map<std::string, int> MAP_OF_VARS;

#endif
