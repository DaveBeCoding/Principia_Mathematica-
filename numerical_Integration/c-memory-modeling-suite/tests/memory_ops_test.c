// tests/memory_ops_test.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/utils.h"

void test_memcpy() {
    char src[] = "Test";
    char dest[10];
    memcpy(dest, src, 5);
    assert(strcmp(dest, "Test") == 0);
}

void test_memset() {
    char buffer[4];
    memset(buffer, 'Z', 4);
    for (int i = 0; i < 4; i++) assert(buffer[i] == 'Z');
}

// int main() {
//     test_memcpy();
//     test_memset();
//     printf("Memory operations tests passed!\n");
//     return 0;
// }

int main(void) {
    printf("Running memory_ops test...\n");

    demo_memcpy();
    demo_memset();
    demo_memcmp();
    demo_memmove();

    printf("All memory operation demos ran successfully.\n");
    return 0;
}