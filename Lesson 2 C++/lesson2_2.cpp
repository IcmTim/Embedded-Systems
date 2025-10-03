#include <iostream>
#include <fstream>

int main() {
    std::ofstream outFile("example.txt");
    if (outFile.is_open()) {
        outFile << "Hello, file!" << std::endl;
        outFile << "This is a second line." << std::endl;
        outFile.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
    return 0;
}