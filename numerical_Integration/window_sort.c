/*

Input: s = "barfoothefoobarman", words = ["foo","bar"]

Output: [0,9]

Explanation:

The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringCount {
    char* key;
    int count;
} StringCount;

int compare(const void* a, const void* b) {
    return strcmp(((StringCount*)a)->key, ((StringCount*)b)->key);
}

int findSubstring(const char* s, const char** words, int numWords, char*** result) {
    if (s == NULL || *words == NULL || numWords <= 0) {
        *result = NULL;
        return 0;
    }

    int wordLen = strlen(words[0]);
    int windowSize = wordLen * numWords;

    StringCount* wordCounter = (StringCount*)malloc(numWords * sizeof(StringCount));
    for (int i = 0; i < numWords; ++i) {
        wordCounter[i].key = strdup(words[i]);
        wordCounter[i].count = 1;
        for (int j = i + 1; j < numWords; ++j) {
            if (strcmp(wordCounter[i].key, words[j]) == 0) {
                ++wordCounter[i].count;
                break;
            }
        }
    }

    int resultSize = 0;
    *result = (char**)malloc(1024 * sizeof(char*)); // Assuming the maximum number of results is 1024

    for (int i = 0; i <= strlen(s) - windowSize; ++i) {
        StringCount* seen = (StringCount*)calloc(numWords, sizeof(StringCount));
        int valid = 1;
        for (int j = 0; j < numWords; ++j) {
            int start = i + j * wordLen;
            char* word = strndup(s + start, wordLen);
            qsort(wordCounter, numWords, sizeof(StringCount), compare);

            StringCount searchWord = {word, 1};
            StringCount* foundWord = bsearch(&searchWord, wordCounter, numWords, sizeof(StringCount), compare);
            if (foundWord != NULL) {
                ++seen[j].count;
                if (seen[j].count > foundWord->count) {
                    valid = 0;
                    break;
                }
            } else {
                valid = 0;
                break;
            }

            free(word);
        }

        if (valid) {
            (*result)[resultSize++] = strdup(s + i);
        }

        free(seen);
    }

    qsort(*result, resultSize, sizeof(char*), compare);

    for (int i = 0; i < numWords; ++i) {
        free(wordCounter[i].key);
    }
    free(wordCounter);

    return resultSize;
}

int main() {
    const char* s = "barfoothefoobarman";
    const char* words[] = {"foo", "bar"};
    int numWords = sizeof(words) / sizeof(words[0]);
    char** result;
    int resultSize = findSubstring(s, words, numWords, &result);

    for (int i = 0; i < resultSize; ++i) {
        printf("%s ", result[i]);
    }
    printf("\n");

    for (int i = 0; i < resultSize; ++i) {
        free(result[i]);
    }
    free(result);

    return 0;
}
