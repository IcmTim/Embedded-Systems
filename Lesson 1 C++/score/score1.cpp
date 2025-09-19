#include <iostream>

int main() {
    int score = 100;

    if (score >= 90) {
        std::cout << "Excellent!" << std::endl;
    } else if (score >= 75) {
        std::cout << "Good job!" << std::endl;
    } else {
        std::cout << "Keep trying!" << std::endl;
    }

    return 0;
}