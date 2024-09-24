/*
 1. std::vector<std::vector<std::vector<double>>>: This declares a 3D vector. The outermost vector holds layers (2D matrices), and each matrix holds rows, where each row contains elements (doubles).

 2.	Accessing Elements: You access an element in the 3D vector using three indices, like v[i][j][k], where i is the layer, j is the row, and k is the column.

Difference Between 2D and 3D Vectors:

•	A 2D vector (std::vector<std::vector<T>>) stores a grid-like structure where each element is accessed by two indices (rows and columns).

•	A 3D vector (std::vector<std::vector<std::vector<T>>>) introduces an additional “depth” or “layer” dimension, so each element is accessed by three indices (layer, row, column).

In simple terms, a 2D vector represents a matrix, while a 3D vector can represent a stack of matrices.
*/

#include <iostream>
#include <vector>

int main() {
    // Define a 3D vector with dimensions 2x2x3
    std::vector<std::vector<std::vector<double>>> v = {
        {
            {1.0, 2.0, 3.0}, 
            {4.0, 5.0, 6.0}
        },
        {
            {7.0, 8.0, 9.0}, 
            {10.0, 11.0, 12.0}
        }
    };

    // Access and print elements in the 3D vector
    std::cout << "Element v[1][0][2]: " << v[1][0][2] << std::endl;  // Outputs 9.0

    // Loop through the 3D vector and print all elements
    for (int i = 0; i < v.size(); ++i) {  // Loop over layers
        std::cout << "Layer " << i << ":\n";
        for (int j = 0; j < v[i].size(); ++j) {  // Loop over rows
            for (int k = 0; k < v[i][j].size(); ++k) {  // Loop over columns
                std::cout << v[i][j][k] << " ";  // Print element
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

/*
 
3D vectors are useful in scenarios where you need to represent volumetric data or data that exists in three dimensions, such as:

	•	Graphics: Storing 3D coordinates or pixel data for 3D rendering.
	•	Simulations: Representing physical simulations in 3D space, such as fluid or heat simulations.
	•	Deep Learning: Storing multi-channel data (e.g., RGB images as 3D tensors).

*/
