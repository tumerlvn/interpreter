#include "classes.h"
#include <iostream>

int main() {
    std::string codeline;
    std::vector<Lexem *> infix;
    std::vector<Lexem *> postfix;
    int value;

    while (std::getline(std::cin, codeline)) {
        infix = parseLexem(codeline);
        postfix = buildPoliz(infix);
        value = evaluatePoliz(postfix);
        std::cout << value << std::endl;
    }
    return 0;
}
