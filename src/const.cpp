#include "const.h"

const int PRIORITY[] = {
    -8,
    -7,
    -6,
    -5,
    -4, -4,
    -4, -4,
    -4, -4,
    -4, -3, -4,
    20, 20,
    -1, -1,
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

const std::string OPERTEXT[] = {
    "return",
    "function",
    "print",
    "size",
    "if", "then",
    "else", "endif",
    "while", "endwhile",
    "goto", ":=", ":",
    "[", "]",
    "(", ")",
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

const int OP_NUM = sizeof(OPERTEXT)/sizeof(OPERTEXT[0]);
