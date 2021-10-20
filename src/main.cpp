#include <iostream>

#include <fmt/core.h>

int main(void) {

    std::cout << fmt::format("Hello World from {}!", "fmt") << std::endl;

    return 0;
}