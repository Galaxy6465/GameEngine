#include <iostream>
#include "core/Engine.hpp"

int main() {
    std::cout << "Engine Started." <<std::endl;

    Engine engine;

    engine.run();

    std::cout << "Engine End." << std::endl;

    return 0;
}