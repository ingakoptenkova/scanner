#ifndef LEXICA_SCANNER_H
#define LEXICA_SCANNER_H


typedef enum {
    NUMBER,
    LITERAL,
    ASSIGN,
    NOT_EQUAL,
    EQUAL,
    POINTER,
    DOT,
    LPAREN,
    RPAREN,
    PLUS,
    SLASH,
    LT,
    GT,
    COLON,
    SEMI,

    IF,
    THEN,
    WHILE,
    DO,
    BEGIN,
    END,
    NIL
} TokenType;

typedef struct {
    TokenType tokenType;
    char token[20];
} Keyword;

static Keyword keywords[] = {
        {IF,    "if"},
        {THEN,  "then"},
        {WHILE, "while"},
        {DO,    "do"},
        {BEGIN, "begin"},
        {END,   "end"},
        {NIL,   "nil"},
};

int get_token(FILE *fp, char *token, TokenType *tokenType, size_t size);

void scan(FILE *fp, char *token, size_t size);

#endif /* LEXICA_SCANNER_H */
