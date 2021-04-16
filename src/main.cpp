#include <iostream>
#include <string>
#include <vector>

#include "lexem.h"
#include "lexical.h"
#include "semantic.h"
#include "syntax.h"


int main() {
    std::string codeline;
    std::vector<Lexem *> infix;
    std::vector<Lexem *> postfix;
    int value;
    while (std::getline(std::cin, codeline)) {
        if (!codeline.empty()) {
            infix = parseLexem(codeline);
            postfix = buildPoliz(infix);
            value = evaluatePoliz(postfix);
            std::cout << value << std::endl;
        }
    }
    return 0;
}
