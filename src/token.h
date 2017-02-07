#ifndef TOKEN_H
#define TOKEN_H

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
    TOKEN_ERROR
} token_t;

struct breezy_t {
    token_t token;
    int value;
};

const char* str_token(token_t t);
token_t scan_token(char* line);
int isNumber(String s);
#endif
