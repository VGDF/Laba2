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

static char* read_string_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char* str = NULL;
    int len = 0;
    int capacity = 5;

    str = (char*)calloc(capacity, sizeof(char));
    if (!str) {
        fclose(file);
        return NULL;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        if (len + 1 >= capacity) {
            capacity += 5;
            char* new_str = (char*)realloc(str, capacity * sizeof(char));
            if (!new_str) {
                free(str);
                fclose(file);
                return NULL;
            }
            str = new_str;
        }
        str[len++] = ch;
    }
    str[len] = '\0';
    fclose(file);
    return str;
}

int main() {
    char* str = read_string_from_file("input.txt");
    if (!str) {
        printf("Error reading input.txt\n");
        return 1;
    }

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

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        printf("Error creating output.txt\n");
        free(str);
        return 1;
    }

    for (int i = 0; i < word_count; i++) {
        fprintf(out, "%s ", words[i]);
    }
    fclose(out);

    free(str);
    return 0;
}