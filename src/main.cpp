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

    while (std::getline(std::cin, codeline)) {
        infixLines.push_back(parseLexem(codeline));
    }

    for (int row = 0; row < (int)infixLines.size(); row++) {
        initLabels(infixLines[row], row);
    }

    initJumps(infixLines);

    for (const auto &infix: infixLines) {
        postfixLines.push_back(buildPostfix(infix));
    }

    int row = 0;
    while (0 <= row && row < (int)postfixLines.size()) {
        row = evaluatePoliz(postfixLines[row], row);
    }
    clean(infixLines);
    return 0;
}
