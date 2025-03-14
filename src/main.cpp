// main.cpp
#include <iostream>
#include <ostream>

#include "server.h"
#include <string>

int main() {
    if (startServer()) {
        std::cout << "Server started successfully." << std::endl;
    } else {
        std::cout << "Server failed to start." << std::endl;
    }
    return 0;
}