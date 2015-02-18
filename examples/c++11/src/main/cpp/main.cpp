#include <iostream>

int main(void) {
    auto l = []() {
        std::cout << "Hello, World!" << std::endl;
    };

    l();
    return 0;
}
