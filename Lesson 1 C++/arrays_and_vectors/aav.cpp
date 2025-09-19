#include <iostream>
#include <vector>

int main() {
    int numbers[3] = {1, 2, 3};
    std::cout << numbers[0];

    std::vector<int> nums {10, 20, 30};
    nums.push_back(40);
    std::cout << nums[2];

    return 0;
}