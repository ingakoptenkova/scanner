#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "scanner.h"


void process_number_token(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i);

void process_alpha_token(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i);

void process_operator(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i);

void assign(TokenType type, char *token, TokenType *tokenType, size_t size, int c, int *i);

int strcicmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}
const char *TokenTypeString[] = {
        "NUMBER",
        "LITERAL",
        "ASSIGN",
        "NOT_EQUAL",
        "EQUAL",
        "POINTER",
        "DOT",
        "LPAREN",
        "RPAREN",
        "PLUS",
        "SLASH",
        "LT",
        "GT",
        "COLON",
        "SEMI",
        "IF",
        "THEN",
        "WHILE",
        "DO",
        "BEGIN",
        "END",
        "NIL"
};

void scan(FILE *fp, char* token, size_t size) {
    TokenType type;
    while (get_token(fp, token, &type, size) != EOF) {
        printf("Token - %15s, Type - %10s\n", token, TokenTypeString[type]);
    }
}

int get_token(FILE *fp, char *token, TokenType *tokenType, size_t size) {
    int i = 0;

    int c;
    do {
        c = fgetc(fp);
    } while (isspace(c));

    if (isdigit(c)) {
        process_number_token(fp, token, tokenType, size, c, &i);
    } else if (isalpha(c)) {
        process_alpha_token(fp, token, tokenType, size, c, &i);
    } else if (ispunct(c)) {
        process_operator(fp, token, tokenType, size, c, &i);
    } else if (c == EOF) {
        return EOF;
    }

    *(token + i) = 0;

    if (*tokenType == LITERAL) {
        for(int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) {
            if (strcicmp(keywords[j].token, token) == 0) {
                *tokenType = keywords[j].tokenType;
                break;
            }
        }
    }

    return 0;
}

void process_operator(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i) {
    switch (c) {
        case '.':
            assign(DOT, token, tokenType, size, c, i);
            break;
        case '/':
            assign(SLASH, token, tokenType, size, c, i);
            break;
        case '^':
            assign(POINTER, token, tokenType, size, c, i);
            break;
        case '+':
            assign(PLUS, token, tokenType, size, c, i);
            break;
        case ')':
            assign(RPAREN, token, tokenType, size, c, i);
            break;
        case '(':
            assign(LPAREN, token, tokenType, size, c, i);
            break;
        case '=':
            assign(EQUAL, token, tokenType, size, c, i);
            break;
        case '<':
            assign(LT, token, tokenType, size, c, i);
            c = fgetc(fp);
            if (c == '>') {
                assign(NOT_EQUAL, token, tokenType, size, c, i);
            } else {
                ungetc(c, fp);
            }
            break;
        case '>':
            assign(GT, token, tokenType, size, c, i);
            break;
        case ':':
            assign(COLON, token, tokenType, size, c, i);
            c = fgetc(fp);
            if (c == '=') {
                assign(ASSIGN, token, tokenType, size, c, i);
            } else {
                ungetc(c, fp);
            }
            break;
        case ';':
            assign(SEMI, token, tokenType, size, c, i);
            break;
        default:
            break;
    }
}

void assign(TokenType type, char *token, TokenType *tokenType, size_t size, int c, int *i) {
    *(token + (*i)++) = c;
    *tokenType = type;
}

void process_alpha_token(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i) {
    do {
        *(token + (*i)++) = c;
        c = fgetc(fp);
    } while (isalnum(c));
    ungetc(c, fp);
    *tokenType = LITERAL;
}


void process_number_token(FILE *fp, char *token, TokenType *tokenType, size_t size, int c, int *i) {
    do {
        *(token + (*i)++) = c;
        c = fgetc(fp);
    } while (isdigit(c));
    ungetc(c, fp);
    *tokenType = NUMBER;
}
