void bubble_sort_pointer(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            int *a = arr + j;
            int *b = arr + j + 1;
            if (*a > *b) {
                int temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }
}
