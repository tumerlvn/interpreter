#include "lexical.h"


bool isSeparator(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool isNumber(char ch) {
    return ('0' <= ch && ch <= '9');
}

bool isVariable(char ch) {
    return (('a' <= ch && ch <= 'z') ||
    ('A' <= ch && ch <= 'Z') ||
    (ch == '_'));
}


Lexem* getOper(const std::string &codeline, int pos, int &next) {
    for (int op = 0; op < OP_NUM; op++) {
        std::string subcodeline =
            codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            next = pos + OPERTEXT[op].size();
            return new Oper(OPERTEXT[op]);
        }
    }
    return nullptr;
}

Lexem* getNum(const std::string &codeline, int pos, int &next) {
    int i = 0;
    for (; i < codeline.size(); i++) {
        if (!isNumber(codeline[pos+i])) {
            break;
        }
    }
    if (i != 0) {
        std::string subcodeline =
            codeline.substr(pos, i);
        int tmp = stoi(subcodeline);
        next = pos + i;
        return new Number(tmp);
    }
    return nullptr;
}

Lexem* scanVar(const std::string &codeline, int pos, int &next) {
    std::string variable;
    int i = 0;
    for (; i < codeline.size(), isVariable(codeline[pos + i]); i++) {

    }
    if (i != 0) {
        variable = codeline.substr(pos, i);
        next = pos + i;
        return new Variable(variable);
    }
    return nullptr;
}

std::vector<Lexem *> parseLexem(const std::string &codeline) {
    std::vector<Lexem *> res;
    Lexem* lexem;
    for (int pos = 0, next = 0; pos < codeline.size();) {
        if (isSeparator(codeline[pos])) {
            pos++;
            continue;
        }
        lexem = getOper(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
        lexem = getNum(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
        lexem = scanVar(codeline, pos, next);
        if (lexem != nullptr) {
            res.push_back(lexem);
            pos = next;
            continue;
        }
    }
    return res;
}
