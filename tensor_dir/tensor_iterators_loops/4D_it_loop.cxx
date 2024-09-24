#include <iostream>
#include <vector>

int main() {
    // Create a 4D tensor (2x2x2x2)
    std::vector<std::vector<std::vector<std::vector<int>>>> tensor = {
        {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}},
        {{{9, 10}, {11, 12}}, {{13, 14}, {15, 16}}}
    };

    // Loop through all dimensions
    for (size_t i = 0; i < tensor.size(); ++i) {
        for (size_t j = 0; j < tensor[i].size(); ++j) {
            for (size_t k = 0; k < tensor[i][j].size(); ++k) {
                for (size_t l = 0; l < tensor[i][j][k].size(); ++l) {
                    std::cout << "tensor[" << i << "][" << j << "][" << k << "][" << l << "] = " << tensor[i][j][k][l] << std::endl;
                }
            }
        }
    }

    return 0;
}
