#include <iostream>
#include <vector>

int main() {
    // Create a 3D tensor (2x2x2)
    std::vector<std::vector<std::vector<int>>> tensor = {
        {
            {1, 2}, 
            {3, 4}
        },
        {
            {5, 6}, 
            {7, 8}
        }
    };

    // Loop through depth
    for (size_t i = 0; i < tensor.size(); ++i) {
        // Loop through rows
        for (size_t j = 0; j < tensor[i].size(); ++j) {
            // Loop through columns
            for (size_t k = 0; k < tensor[i][j].size(); ++k) {
                std::cout << "tensor[" << i << "][" << j << "][" << k << "] = " << tensor[i][j][k] << std::endl;
            }
        }
    }

    return 0;
}
