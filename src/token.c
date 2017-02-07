#include "token.h"

int isNumber(String s) {
    for (int i = 0; i < s.length(); i++) {
        char c = s.charAt(i);
        if ((c < '0' || c > '9') && c != '-') return 0;
    }
    return 1;
}

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
		case TOKEN_ERROR:
			return "TOKEN_ERROR";
			break;
	}
}

token_t scan_token(String word){
    int state = 0;
    String buf;
    char symbol;
    symbol = word.charAt(0);
    if ( word == "CLEAR" ) {
        return TOKEN_CLEAR;
 	} else if ( word == "PRINT" ) {
        return TOKEN_PRINT;
 	} else if ( word == "IF" ) {
        return TOKEN_IF;
 	} else if ( word == "THEN" ) {
        return TOKEN_THEN;
 	} else if ( word == "GOTO" ) {
        return TOKEN_GOTO;
 	} else if ( word == "INPUT" ) {
        return TOKEN_INPUT;
 	} else if ( word == "LET" ) {
        return TOKEN_LET;
 	} else if ( word == "GOSUB" ) {
        return TOKEN_GOSUB;
 	} else if ( word == "RETURN" ) {
        return TOKEN_RETURN;
 	} else if ( word == "LIST" ) {
        return TOKEN_LIST;
 	} else if ( word == "RUN" ) {
        return TOKEN_RUN;
 	} else if ( word == "END" ) {
        return TOKEN_END;
 	} else if ( word == "(" ) {
        return TOKEN_LPAREN;
 	} else if ( word == ")" ) {
        return TOKEN_RPAREN;
 	} else if ( word == "," ) {
        return TOKEN_COMMA;
 	} else if ( word == "*" ) {
        return TOKEN_MUL;
 	} else if ( word == "/" ) {
        return TOKEN_DIV;
 	} else if ( word == "-" ) {
        return TOKEN_SUB;
 	} else if ( word == "+" ) {
        return TOKEN_ADD;
 	} else if ( word == "=" ) {
        return TOKEN_EQ;
 	} else if ( word == "<" ) {
        return TOKEN_LT;
 	} else if ( word == ">" ) {
        return TOKEN_GT;
 	} else if ( word == "<>" ) {
        return TOKEN_NEQ;
 	} else if ( word == "<=" ) {
        return TOKEN_LE;
 	} else if ( word == ">=" ) {
        return TOKEN_GE;
 	} else if ( word == "A" ) {
        return TOKEN_AND;
 	} else if ( word == "O" ) {
        return TOKEN_OR;
 	} else if ( word == "X" ) {
        return TOKEN_XOR;
 	} else if ( word == "L" ) {
        return TOKEN_SLL;
 	} else if ( word == "R" ) {
        return TOKEN_SLR;
    } else if ( word.startsWith(String("\"")) && word.endsWith(String("\"")) ) {
        return TOKEN_STR;
    } else if ( isNumber(word) ){
        return TOKEN_NUM;
    } else {
        return TOKEN_ERROR;
    }
}

