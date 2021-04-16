#include "const.h"

const int PRIORITY[] = {
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

const int OP_NUM = sizeof(OPERTEXT)/sizeof(OPERTEXT[0]);

std::map<std::string, int> MAP_OF_VARS;
