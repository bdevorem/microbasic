#include "token.h"
#include "Energia.h"

int atoi(char* s, int len) {
    int n = ((s[0] == '-')?1:0);
    int k = 0;
    int p = 1;
    for (int i = len - n - 1; i >= 0; i--) {
        k += (s[i]-'0')*p; p*=10;
    }
    return n?-k:k;
}


int isNumber(char* s, int len) {
    int n = ((s[0] == '-')?1:0);
    for (int i = n; i < len; i++) {
        char c = s[i];
        if (c < '0' || c > '9') return 0;
    }
    return len>=1;
}

int strCmp(char* s1, int l1, char* s2, int l2) {
    if (l1 != l2) return 0;
    
    for (int i = 0; i < l1; i++) {
        if (s1[i] != s2[i]) return 0;
    }
    return 1;
}

token_t scan_token(char* word, int len) {
    int state = 0;
    String buf;
    char symbol = word[0];
    Serial.println(word);
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
        return TOKEN_SRL;
    } else if ( len > 1 && word.startsWith(String("\"")) && word.endsWith(String("\"")) ) {
        return TOKEN_STR;
    } else if ( isNumber(word, len) ){
        return TOKEN_NUM;
    } else {
        return TOKEN_ERROR;
    }
}



