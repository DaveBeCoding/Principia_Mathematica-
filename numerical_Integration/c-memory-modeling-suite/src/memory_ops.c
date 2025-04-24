// src/memory_ops.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void demo_memcpy(void) {
    char src[] = "AppleMemoryOps";
    char dest[50];
    memcpy(dest, src, strlen(src) + 1);
    printf("memcpy: %s\n", dest);
}

void demo_memset(void) {
    char buffer[10];
    memset(buffer, 'A', sizeof(buffer));
    for (int i = 0; i < 10; i++) putchar(buffer[i]);
    putchar('\n');
}

void demo_memcmp(void) {
    char a[] = "AAPL";
    char b[] = "AAPL";
    if (memcmp(a, b, strlen(a)) == 0) {
        printf("memcmp: Buffers are equal\n");
    }
}

void demo_memmove(void) {
    char str[20] = "1234567890";
    memmove(str + 4, str, 6);
    printf("memmove: %s\n", str);
}

int main(void) {
    printf("-- Memory Ops Demo --\n");
    demo_memcpy();
    demo_memset();
    demo_memcmp();
    demo_memmove();
    return 0;
}


/*
🚧 Warnings (Fixable in memory_ops.c)
“function declaration without a prototype is deprecated…”

🔧 Solution:
You need to explicitly declare the functions with void parameters if they take no arguments:

Change this:
void demo_memcpy() {

To this:
void demo_memcpy(void) {
*/