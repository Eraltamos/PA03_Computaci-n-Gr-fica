#include "Application.hpp"

int main(int argc, char** argv) {
    Application app(1024, 768, "PA3 - Erwin Alain Felix Tayro Mosqueira", argc, argv);
    app.run();
    return 0;
}