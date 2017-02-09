#ifndef TOKEN_H
#define TOKEN_H
#include "Energia.h"

typedef enum {
	TOKEN_PRINT,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_GOTO,
	TOKEN_INPUT,
	TOKEN_LET,
	TOKEN_GOSUB,
	TOKEN_RETURN,
	TOKEN_CLEAR,
	TOKEN_LIST,
	TOKEN_RUN,
	TOKEN_END,
	TOKEN_NUM,
	TOKEN_STR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_COMMA,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_SUB,
	TOKEN_ADD,
	TOKEN_EQ,
	TOKEN_LT,
	TOKEN_GT,
	TOKEN_NEQ,
	TOKEN_LE,
	TOKEN_GE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_XOR,
	TOKEN_SLL,
	TOKEN_SRL,
        TOKEN_ERROR,
        TOKEN_ID,
        TOKEN_CR
} token_t;

struct breezy_t {
    token_t token;
    int value;
};

token_t scan_token(char* line, int len);
int isNumber(char* line, int len);
int atoi(char* line, int len);
int strcmp(char* s1, int l1, char* s2, int l2);
void strcpy(char* s1, char* s2);
void _print(breezy_t e);
void _println(breezy_t e);
#endif








