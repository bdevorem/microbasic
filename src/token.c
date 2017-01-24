#include "token.h"

const char* str_token(token_t t){
	switch(t) {
		case TOKEN_LET:
			return "TOKEN_LET";
			break;
		case TOKEN_PRINT:
			return "TOKEN_PRINT";
			break;
		case TOKEN_IF:
			return "TOKEN_IF";
			break;
		case TOKEN_THEN:
			return "TOKEN_THEN";
			break;
		case TOKEN_GOTO:
			return "TOKEN_GOTO";
			break;
		case TOKEN_INPUT:
			return "TOKEN_INPUT";
			break;
		case TOKEN_GOSUB:
			return "TOKEN_GOSUB";
			break;
		case TOKEN_RETURN:
			return "TOKEN_RETURN";
			break;
		case TOKEN_CLEAR:
			return "TOKEN_CLEAR";
			break;
		case TOKEN_LIST:
			return "TOKEN_LIST";
			break;
		case TOKEN_RUN:
			return "TOKEN_RUN";
			break;
		case TOKEN_END
			return "TOKEN_END";
			break;
		// and whatever else
	}
}

#endif
