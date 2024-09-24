#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Loop through vector using index
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    // Range-based loop (C++11 or higher)
    for (int val : vec) {
        std::cout << "Value: " << val << std::endl;
    }

    return 0;
}
