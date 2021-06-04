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
        std::string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            next = pos + OPERTEXT[op].size();
            if (op == GOTO || op == IF || op == ELSE || op == WHILE || op == ENDWHILE || op == ENDIF) {
                return new Goto((OPERATOR)op);
            }
            return new Oper((OPERATOR)op);
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
    for (; i < codeline.size() && isVariable(codeline[pos + i]); i++) {

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
    // for (int i = 0; i < res.size(); i++) {
    //     std::cout << "|";
    //     res[i]->print();
    // }
    // std::cout << std::endl;
    return res;
}

void initLabels(std::vector <Lexem *> &infix, int row) {
    for (int i = 1; i < (int)infix.size(); i++) {
        if (infix[i-1]->type() == VARIABLE && infix[i]->type() == OPER) {
            Variable *lexemvar = (Variable *)infix[i-1];
            Oper *lexemop = (Oper *)infix[i];
            if (lexemop->getType() == COLON) {
                LABELS[lexemvar->getName()] = row;
                delete (Variable *)lexemvar;
                delete (Oper *)lexemop;
                infix[i-1] = nullptr;
                infix[i] = nullptr;
                i++;
            }
        }

    }
    for (int i = 1; i < (int)infix.size() - 1; i++) {
        if (infix[i-1]->type() == OPER && infix[i-1] -> getType() == FUNCTION) {
            int magicConstant = i + 3;// 0x5f3759df  <- quake reference
            Variable *lexemvar = (Variable *)infix[i];
            FUNCTION_TABLE[lexemvar -> getName()].numOfArgs = infix.size() - magicConstant;//  i-1       i   i+1        size-1
            FUNCTION_TABLE[lexemvar -> getName()].row = row;                               // function  func  (  a  b  c  )     args == (size-1) - (i+1) - 1
            delete infix[i];
            delete infix[i+1];
            delete infix[infix.size() - 1];
            infix[i+1] = nullptr;  // delete brackets
            infix[infix.size() - 1] = nullptr;
            infix[i] = nullptr;
            return;
        }
    }

}

ERROR_CODES initArrays(std::vector <Lexem *> &infix, int row) {
    for (int i = 2; i < (int)infix.size(); i++) {
        if (infix[i-2] != nullptr && infix[i-1] != nullptr && infix[i] != nullptr) {
            if (infix[i-2]->type() == VARIABLE && infix[i-1]->type() == OPER && infix[i]->type() == NUMBER) {
                Variable *lexemvar = (Variable *)infix[i-2];
                Oper *lexemop = (Oper *)infix[i-1];
                Number *lexemnum = (Number *)infix[i];
                if (lexemop->getType() == SIZE) {
                    if (lexemnum->getValue() <= 0) {
                        return ARRAY_WRONG_SIZE;
                    }
                    ARRAY_TABLE[lexemvar->getName()] = new Array(lexemnum->getValue());
                    delete (Variable *)lexemvar;
                    delete (Oper *)lexemop;
                    delete (Number *)lexemnum;
                    infix[i-2] = nullptr;
                    infix[i-1] = nullptr;
                    infix[i] = nullptr;
                    i += 2;
                }
            }
        }
    }
    return WORKS_FINE;
}

void initJumps(std::vector <std::vector <Lexem *>> &infixLines) {
    std::stack<Goto *> stackOfGoto;
    for (int row = 0; row < infixLines.size(); row++) {
        //std::cout << "row: " << row << std::endl;
        for (int i = 0; i < infixLines[row].size(); i++) {
            //std::cout << " word: " << i << std::endl;
            if (infixLines[row].at(i) != nullptr && infixLines[row].at(i)->type() == OPERGOTO) {
                //std::cout << "row: " << row << " word: " << i << std::endl;
                Oper *lexemoper = (Oper *)infixLines[row].at(i);
                Goto *lexemgoto = nullptr;

                switch (lexemoper->getType()) {
                case IF:
                    stackOfGoto.push((Goto *)lexemoper);
                    //std::cout << "if in stack" << '\n';
                    break;
                case ELSE:
                    stackOfGoto.top()->setRow(row + 1);
                    stackOfGoto.pop();
                    stackOfGoto.push((Goto *)lexemoper);
                    break;
                case ENDIF:
                    // delete lexemoper;
                    // lexemoper = nullptr;
                    stackOfGoto.top()->setRow(row + 1);
                    stackOfGoto.pop();
                    //std::cout << "endif: if out of stack" << '\n';
                    break;
                case WHILE:
                    lexemgoto = (Goto *)lexemoper;
                    lexemgoto->setRow(row);
                    stackOfGoto.push(lexemgoto);
                    //std::cout << "while in stack" << '\n';
                    break;
                case ENDWHILE:
                    lexemgoto = (Goto *)lexemoper;
                    lexemgoto->setRow(stackOfGoto.top()->getRow());
                    stackOfGoto.top()->setRow(row + 1);
                    stackOfGoto.pop();
                    //std::cout << "endwhile: while out of stack" << '\n';
                    break;
                }
            }
        }
    }
}
