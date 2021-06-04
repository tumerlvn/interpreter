#include <iostream>
#include <string>
#include <vector>

#include "lexem.h"
#include "lexical.h"
#include "semantic.h"
#include "syntax.h"

int main() {
    std::string codeline;
    std::vector <std::vector <Lexem*>> infixLines, postfixLines;
    ERROR_CODES code = WORKS_FINE;

    while (std::getline(std::cin, codeline)) {
        infixLines.push_back(parseLexem(codeline));
    }

    for (int row = 0; row < (int)infixLines.size(); row++) {
        initLabels(infixLines[row], row);
    }

    for (int row = 0; row < (int)infixLines.size(); row++) {
        code = initArrays(infixLines[row], row);
    }

    // for (std::map<std::string, Array *>::iterator it = ARRAY_TABLE.begin(); it != ARRAY_TABLE.end(); ++it) {
    //     std::cout << it->first << std::endl;
    // }

    initJumps(infixLines);

    for (const auto &infix: infixLines) {
        postfixLines.push_back(buildPostfix(infix));
    }

    int row = initialPosition(postfixLines);
    //std::cout << row << '\n';
    while (0 <= row && row < (int)postfixLines.size()) {
        row = evaluatePoliz(postfixLines, row);
    }
    // clean(infixLines);
    return 0;
}
