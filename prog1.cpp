#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

static int count_vowels(const char* word) {
    int count = 0;
    while (*word) {
        if (is_vowel(*word)) count++;
        word++;
    }
    return count;
}

static char* read_string_malloc() {
    char* str = NULL;
    char ch;
    int len = 0;
    int capacity = 1;

    str = (char*)malloc(capacity * sizeof(char));
    if (!str) return NULL;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 1 >= capacity) {
            capacity++;
            char* new_str = (char*)malloc(capacity * sizeof(char));
            if (!new_str) {
                free(str);
                return NULL;
            }
            for (int i = 0; i < len; i++) new_str[i] = str[i];
            free(str);
            str = new_str;
        }
        str[len++] = ch;
    }
    str[len] = '\0';
    return str;
}

int fds() {
    char* str = read_string_malloc();
    if (!str) return 1;

    char* longest_word = NULL, * shortest_word = NULL;
    int max_len = 0, min_len = 1000;
    char* words[100];
    int word_count = 0;

    char* token = strtok(str, " ");
    while (token) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < word_count; i++) {
        int wlen = strlen(words[i]);
        if (wlen > max_len) {
            max_len = wlen;
            longest_word = words[i];
        }
        if (wlen < min_len) {
            min_len = wlen;
            shortest_word = words[i];
        }
    }

    if (longest_word && shortest_word && count_vowels(longest_word) == count_vowels(shortest_word)) {
        char temp[100];
        strcpy(temp, longest_word);
        strcpy(longest_word, shortest_word);
        strcpy(shortest_word, temp);
    }

    for (int i = 0; i < word_count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    free(str);
    return 0;
}