/*
Layer 0 (v[0]):
  Row\Col   0     1     2
         +-----+-----+-----+
Row 0    | 1.0 | 2.0 | 3.0 |
         +-----+-----+-----+
Row 1    | 4.0 | 5.0 | 6.0 |
         +-----+-----+-----+

Layer 1 (v[1]):
  Row\Col   0     1     2
         +-----+-----+-----+
Row 0    | 7.0 | 8.0 | 9.0 |
         +-----+-----+-----+
Row 1    | 10.0 | 11.0|12.0|
         +-----+-----+-----+
*/

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

//3D vector with dimensions 2x2x3
//double value = v[1][0][2];  // Access the element in Layer 1, Row 0, Column 2
//std::cout << "v[1][0][2] = " << value << std::endl;  // Output: 9.0
