#ifndef _CONST_H
#define _CONST_H

#include <string>
#include <map>

enum OPERATOR {
    IF, THEN,
    ELSE, ENDIF,
    WHILE, ENDWHILE,
    GOTO, ASSIGN, COLON,
    LBRACKET, RBRACKET,
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
    VARIABLE,
    OPERGOTO
};


extern const int PRIORITY[];
extern const std::string OPERTEXT[];
extern const int OP_NUM;
extern std::map<std::string, int> MAP_OF_VARS;
extern std::map<std::string, int> LABELS;

#endif
