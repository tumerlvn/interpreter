#include "semantic.h"

#include <iostream>

int evaluatePoliz(std::vector <std::vector <Lexem *>>  &postfixLines, int row) {
    // for (int i = 0; i < poliz.size(); i++) {
    //     std::cout << "|";
    //     poliz[i]->print();
    // }
    // std::cout << std::endl;
    // std::vector<Lexem*> cleaner;

    std::vector<Lexem *> poliz = postfixLines[row];
    std::vector<Lexem*> stack;

    for (int i = 0; i < poliz.size(); i++) {
        if (poliz[i] == nullptr) {
            continue;
        }
        if (poliz[i]->type() == NUMBER) {
            stack.push_back(poliz[i]);
        } else if (poliz[i]->type() == VARIABLE || poliz[i]->type() == ARRAY_ELEMENT) {
            stack.push_back(poliz[i]);
        } else if (poliz[i] -> getType() == RETURN) {
            if (stack.back()) {
                GLOBAL_STACK.push_back(stack.back());
                stack.pop_back();
            }
            //MAP_OF_VARS.clear();
            //ARRAY_TABLE.clear();
            return -1;
        } else if (poliz[i] -> getType() == FUNCTION) {
            std::vector<Lexem *> reverseStack;
            while(!GLOBAL_STACK.empty()) {
                reverseStack.push_back(GLOBAL_STACK.back());
                GLOBAL_STACK.pop_back();
            }
            while (!reverseStack.empty()) {
                stack.back() -> setValue(reverseStack.back()->getValue());
                stack.pop_back();
                reverseStack.pop_back();
            }
            continue;
        } else if (poliz[i]->type() == OPER || poliz[i]->type() == OPERGOTO) {
            if (poliz[i] -> getType() == LBRACKET) {
                if (i + 1 >= poliz.size())
                    continue;
                if (poliz[i + 1] -> type() != VARIABLE)
                    continue;
                if (FUNCTION_TABLE.find(((Variable *)poliz[i + 1]) -> getName()) == FUNCTION_TABLE.end())
                    continue;
                Lexem *functionName = poliz[i + 1];
                poliz[i + 1] = nullptr;
                for (int arg = 0; arg < FUNCTION_TABLE[((Variable*)functionName)->getName()].numOfArgs; arg++) {
                    GLOBAL_STACK.push_back(stack.back());
                    //GLOBAL_STACK.back()->print();
                    stack.pop_back();
                }
                // NameSpace *currentSpace = new NameSpace;
                // currentSpace -> variablesMap = MAP_OF_VARS;
                // currentSpace -> arraysMap = ARRAY_TABLE;
                //MAP_OF_VARS.clear();
                //ARRAY_TABLE.clear();
                int tmp_row = FUNCTION_TABLE[((Variable*)functionName)->getName()].row;
                while (tmp_row >= 0) {
                    tmp_row = evaluatePoliz(postfixLines, tmp_row);
                }
                //MAP_OF_VARS = currentSpace -> variablesMap;
                //ARRAY_TABLE = currentSpace -> arraysMap;
                //delete currentSpace;
                if (!GLOBAL_STACK.empty()) {
                    stack.push_back(GLOBAL_STACK.back() );
                    GLOBAL_STACK.pop_back();
                }
                continue;
            }
            if (poliz[i]->getType() == GOTO || poliz[i]->getType() == ELSE || poliz[i]->getType() == ENDWHILE) {
                Goto *lexemgoto = (Goto *)poliz[i];
                // clean(cleaner);
                return lexemgoto->getRow();
            } else if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
                Goto *lexemgoto = (Goto *)poliz[i];
                int rvalue = (int)stack.back()->getValue();
                stack.pop_back();
                if (!rvalue) {
                    // clean(cleaner);
                    return lexemgoto->getRow();
                }
            } else if (poliz[i]->getType() == PRINT) {
                std::cout << stack.back()->getValue() << std::endl;
                stack.pop_back();
            } else {
                Lexem* tmp2 = stack.back();
                stack.pop_back();
                Lexem* tmp1 = stack.back();
                stack.pop_back();
                stack.push_back(poliz[i]->getValue(tmp1, tmp2));
                // cleaner.push_back(stack.back());
            }
        }
    }
    //return stack.back()->getValue();
    // if (!stack.empty()) {
    //     std::cout << stack.back()->getValue() << std::endl;
    // }
    // clean(cleaner);
    return row + 1;
}

int initialPosition(std::vector<std::vector<Lexem *>> postfixLines) {
    int start = 0;
    for (int i = 0; i < postfixLines.size(); i++) {
        int rowSize = postfixLines[i].size();
        if (rowSize - 1 < 0)
            continue;
        if (postfixLines[i][rowSize - 1] == nullptr)
            continue;
        if (postfixLines[i][rowSize - 1] -> type() == OPER && postfixLines[i][rowSize - 1] -> getType() == RETURN) {
            start = i + 1;
        }
    }
    return start;
}

// void clean(std::vector<Lexem *> &cleaner) {
//     for (auto &lexem: cleaner) {
//         if (lexem == nullptr) continue;
//         switch (lexem->type()) {
//         case LEXEM:
//             delete lexem;
//             break;
//         case NUMBER:
//             delete (Number *)lexem;
//             break;
//         case VARIABLE:
//             delete (Variable *)lexem;
//             break;
//         case OPER:
//             delete (Oper *)lexem;
//             break;
//         case OPERGOTO:
//             delete (Goto *)lexem;
//             break;
//         case ARRAY_ELEMENT:
//             delete (ArrayElement *)lexem;
//             break;
//         }
//         lexem = nullptr;
//     }
// }
//
// void clean(std::vector<std::vector<Lexem *>> &cleaner) {
//     for (std::vector<Lexem *> line: cleaner) {
//         for (Lexem *lexem: line) {
//             if (lexem == nullptr) continue;
//             else {
//                 switch (lexem->type()) {
//                 case LEXEM:
//                     delete lexem;
//                     break;
//                 case NUMBER:
//                     delete (Number *)lexem;
//                     break;
//                 case VARIABLE:
//                     delete (Variable *)lexem;
//                     break;
//                 case OPER:
//                     delete (Oper *)lexem;
//                     break;
//                 case OPERGOTO:
//                     delete (Goto *)lexem;
//                     break;
//                 }
//
//                 lexem = nullptr;
//             }
//         }
//     }
//     for (std::map<std::string, Array *>::iterator it = ARRAY_TABLE.begin(); it != ARRAY_TABLE.end(); ++it) {
//         delete it->second;
//     }
// }
