#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	TOKEN_LET,
	TOKEN_PRINT,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_GOTO,
	TOKEN_INPUT,
	TOKEN_GOSUB,
	TOKEN_RETURN,
	TOKEN_CLEAR,
	TOKEN_LIST,
	TOKEN_RUN,
	TOKEN_END
	// and whatever else
} token_t;

const char* str_token(token_t t);

#endif
