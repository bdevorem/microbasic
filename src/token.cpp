#include "token.h"
#include "Energia.h"

int atoi(String& s) {
    int n = ((s.charAt(0) == '-')?1:0);
    int k = 0;
    int p = 1;
    for (int i = s.length() - n - 1; i >= 0; i--) {
        k += (s.charAt(i)-'0')*p; p*=10;
    }
    return n?-k:k;
}


int isNumber(String s) {
    int n = ((s.charAt(0) == '-')?1:0);
    for (int i = n; i < s.length(); i++) {
        char c = s.charAt(i);
        if (c < '0' || c > '9') return 0;
    }
    return s.length()>=1;
}

int isIdentifier(String s) {
    if (s.length() != 1) return 0;
    if (s.charAt(0) < 'A' || s.charAt(0) > 'Z') return 0;
    return 1;
}

const char* str_token(token_t t){
	switch(t) {
		case TOKEN_PRINT:
			return "TOKEN_PRINT";
		case TOKEN_IF:
			return "TOKEN_IF";
		case TOKEN_THEN:
			return "TOKEN_THEN";
		case TOKEN_GOTO:
			return "TOKEN_GOTO";
		case TOKEN_INPUT:
			return "TOKEN_INPUT";
		case TOKEN_LET:
			return "TOKEN_LET";
		case TOKEN_GOSUB:
			return "TOKEN_GOSUB";
		case TOKEN_RETURN:
			return "TOKEN_RETURN";
		case TOKEN_CLEAR:
			return "TOKEN_CLEAR";
		case TOKEN_LIST:
			return "TOKEN_LIST";
		case TOKEN_RUN:
			return "TOKEN_RUN";
		case TOKEN_END:
			return "TOKEN_END";
		case TOKEN_NUM:
			return "TOKEN_NUM";
		case TOKEN_STR:
			return "TOKEN_STR";
		case TOKEN_LPAREN:
			return "TOKEN_LPAREN";
		case TOKEN_RPAREN:
			return "TOKEN_RPAREN";
		case TOKEN_COMMA:
			return "TOKEN_COMMA";
		case TOKEN_MUL:
			return "TOKEN_MUL";
		case TOKEN_DIV:
			return "TOKEN_DIV";
		case TOKEN_SUB:
			return "TOKEN_SUB";
		case TOKEN_ADD:
			return "TOKEN_ADD";
		case TOKEN_EQ:
			return "TOKEN_EQ";
		case TOKEN_LT:
			return "TOKEN_LT";
		case TOKEN_GT:
			return "TOKEN_GT";
		case TOKEN_NEQ:
			return "TOKEN_NEQ";
		case TOKEN_LE:
			return "TOKEN_LE";
		case TOKEN_GE:
			return "TOKEN_GE";
		case TOKEN_AND:
			return "TOKEN_AND";
		case TOKEN_OR:
			return "TOKEN_OR";
		case TOKEN_XOR:
			return "TOKEN_XOR";
		case TOKEN_SLL:
			return "TOKEN_SLL";
		case TOKEN_SRL:
			return "TOKEN_SRL";
		case TOKEN_ERROR:
			return "TOKEN_ERROR";
        case TOKEN_ID:
            return "TOKEN_ID";
        case TOKEN_CR:
            return "TOKEN_CR";
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
 	} else if ( word == "&" ) {
        return TOKEN_AND;
 	} else if ( word == "|" ) {
        return TOKEN_OR;
 	} else if ( word == "<<" ) {
        return TOKEN_SLL;
 	} else if ( word == ">>" ) {
        return TOKEN_SRL;
    } else if ( word.length() > 1 && word.startsWith(String("\"")) && word.endsWith(String("\"")) ) {
        return TOKEN_STR;
    } else if ( isNumber(word) ){
        return TOKEN_NUM;
    } else if ( isIdentifier(word) ){
        return TOKEN_ID;
    } else {
        return TOKEN_ERROR;
    }
}



