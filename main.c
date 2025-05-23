#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 10

char production[MAX][MAX];
char calc_first[MAX][MAX];
char calc_follow[MAX][MAX];
int count, n = 0, m = 0;
char first[MAX], follow_result[MAX];
int k;
int done_first[MAX], done_follow[MAX];
int num_terminals = 0;
char terminals[MAX];

// Function Declarations
void findfirst(char c, int q1, int q2);
void follow(char c);
void followfirst(char c, int c1, int c2);

int main() {
    int i, j, ptr = -1;
    char c, ch;

    printf("Enter number of productions: ");
    scanf("%d", &count);

    printf("Enter productions in form A=B:\n");
    for (i = 0; i < count; i++) {
        scanf("%s%c", production[i], &ch);
    }

    // FIRST SET
    for (i = 0; i < count; i++) {
        c = production[i][0];
        if (!done_first[c - 'A']) {
            findfirst(c, 0, 0);
            done_first[c - 'A'] = 1;
        }
        printf("FIRST(%c) = { ", c);
        for (j = 0; j < n; j++) {
            printf("%c ", first[j]);
        }
        printf("}\n");
        n = 0;
    }

    printf("\n");

    // FOLLOW SET
    follow(production[0][0]);
    done_follow[production[0][0] - 'A'] = 1;

    for (i = 0; i < count; i++) {
        c = production[i][0];
        if (!done_follow[c - 'A']) {
            follow(c);
            done_follow[c - 'A'] = 1;
        }
        printf("FOLLOW(%c) = { ", c);
        for (j = 0; j < m; j++) {
            printf("%c ", follow_result[j]);
        }
        printf("}\n");
        m = 0;
    }

    // LL(1) Table construction and parsing can follow here
    printf("\nLL(1) table and string parsing can be implemented below as needed.\n");

    return 0;
}

// FIND FIRST
void findfirst(char c, int q1, int q2) {
    int j;
    if (!(isupper(c))) {
        first[n++] = c;
        return;
    }

    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0') {
                    first[n++] = '#';
                } else {
                    findfirst(production[q1][q2], q1, q2 + 1);
                }
            } else if (!isupper(production[j][2])) {
                first[n++] = production[j][2];
            } else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}

// FOLLOW
void follow(char c) {
    int i, j;
    if (production[0][0] == c) follow_result[m++] = '$';

    for (i = 0; i < count; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    followfirst(production[i][j + 1], i, j + 2);
                }

                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    follow(production[i][0]);
                }
            }
        }
    }
}

// FOLLOW FIRST
void followfirst(char c, int c1, int c2) {
    int i, j;

    if (!(isupper(c))) {
        follow_result[m++] = c;
    } else {
        for (i = 0; i < count; i++) {
            if (production[i][0] == c) break;
        }

        for (j = 2; j < strlen(production[i]); j++) {
            if (!isupper(production[i][j])) {
                follow_result[m++] = production[i][j];
                break;
            } else if (production[i][j] == '#') {
                if (production[c1][c2] == '\0') {
                    follow(production[c1][0]);
                } else {
                    followfirst(production[c1][c2], c1, c2 + 1);
                }
            } else {
                findfirst(production[i][j], i, j + 1);
                for (int f = 0; f < n; f++) {
                    if (first[f] != '#')
                        follow_result[m++] = first[f];
                }
                break;
            }
        }
    }
}
