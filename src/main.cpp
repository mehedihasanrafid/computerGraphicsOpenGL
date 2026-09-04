#include "App.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        yacht::App app;
        return app.run(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}
