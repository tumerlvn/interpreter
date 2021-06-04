#ifndef _CONST_H
#define _CONST_H

#include <string>
#include <map>

enum OPERATOR {
    RETURN,
    FUNCTION,
    PRINT,
    SIZE,
    IF, THEN,
    ELSE, ENDIF,
    WHILE, ENDWHILE,
    GOTO, ASSIGN, COLON,
    LSQUARE, RSQUARE,
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
    OPERGOTO,
    ARRAY_ELEMENT
};

enum ERROR_CODES {
    WORKS_FINE,
    ARRAY_WRONG_SIZE
};

extern const int PRIORITY[];
extern const std::string OPERTEXT[];
extern const int OP_NUM;



#endif
