#include <iostream>
#include <string>
#include <vector>

#include "lexem.h"
#include "lexical.h"
#include "semantic.h"
#include "syntax.h"


/*int main() {
    std::string codeline;
    std::vector<Lexem *> infix;
    std::vector<Lexem *> postfix;
    int value;
    while (std::getline(std::cin, codeline)) {
        if (!codeline.empty()) {
            infix = parseLexem(codeline);
            postfix = buildPostfix(infix);
            value = evaluatePoliz(postfix);
            std::cout << value << std::endl;
        }
    }
    return 0;
}*/

int main() {
    std::string codeline;
    std::vector <std::vector <Lexem*>> infixLines, postfixLines;

    while (std::getline(std::cin, codeline)) {
        infixLines.push_back(parseLexem(codeline));
    }

    for (int row = 0; row < (int)infixLines.size(); row++) {
        initLabels(infixLines[row], row);
    }

    for (const auto &infix: infixLines) {
        postfixLines.push_back(buildPostfix(infix));
    }

    int row = 0;
    while (0 <= row && row < (int)postfixLines.size()) {
        row = evaluatePoliz(postfixLines[row], row);
    }
    return 0;
}
