#include "token.h"

const char* str_token(token_t t){
	switch(t) {
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
		case TOKEN_LET:
			return "TOKEN_LET";
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
		case TOKEN_END:
			return "TOKEN_END";
			break;

		case TOKEN_NUM:
			return "TOKEN_NUM";
			break;
		case TOKEN_STR:
			// \"[alphanum]*\"
			return "TOKEN_STR";
			break;


		case TOKEN_LPAREN:
			return "TOKEN_LPAREN";
			break;
		case TOKEN_RPAREN:
			return "TOKEN_RPAREN";
			break;
		case TOKEN_COMMA:
			return "TOKEN_COMMA";
			break;
		case TOKEN_MUL:
			return "TOKEN_MUL";
			break;
		case TOKEN_DIV:
			return "TOKEN_DIV";
			break;
		case TOKEN_SUB:
			return "TOKEN_SUB";
			break;
		case TOKEN_ADD:
			return "TOKEN_ADD";
			break;
		case TOKEN_EQ:
			return "TOKEN_EQ";
			break;
		case TOKEN_LT:
			return "TOKEN_LT";
			break;
		case TOKEN_GT:
			return "TOKEN_GT";
			break;
		case TOKEN_NEQ:
			return "TOKEN_NEQ";
			break;
		case TOKEN_LE:
			return "TOKEN_LE";
			break;
		case TOKEN_GE:
			return "TOKEN_GE";
			break;
		case TOKEN_AND:
			return "TOKEN_AND";
			break;
		case TOKEN_OR:
			return "TOKEN_OR";
			break;
		case TOKEN_XOR:
			return "TOKEN_XOR";
			break;
		case TOKEN_SLL:
			return "TOKEN_SLL";
			break;
		case TOKEN_SRL:
			return "TOKEN_SRL";
			break;
	}
}

token_t scan_token(char* line){







}

