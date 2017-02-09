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

int strcmp(char* s1, int l1, char* s2, int l2) {
    if (l1 != l2) return 0;
    
    for (int i = 0; i < l1; i++) {
        if (s1[i] != s2[i]) return 0;
    }
    return 1;
}
void strcpy(char* s1, char* s2) {
    char c;
    while (c = *s1) {
       s1++;
       (*s2)=c;
       s2++;
    }
    (*s2)=0;
}


token_t scan_token(char* word, int len) {
    int state = 0;
    String buf;
    char symbol = word[0];
    if ( strcmp(word, len, "CLEAR", 5) ) {
        return TOKEN_CLEAR;
 	} else if ( strcmp(word, len, "PRINT", 5 ) ) {
        return TOKEN_PRINT;
 	} else if ( strcmp(word, len, "IF", 2 ) ) {
        return TOKEN_IF;
 	} else if ( strcmp(word, len, "THEN", 4 ) ) {
        return TOKEN_THEN;
 	} else if ( strcmp(word, len, "GOTO", 4 ) ) {
        return TOKEN_GOTO;
 	} else if ( strcmp(word, len, "INPUT", 5 ) ) {
        return TOKEN_INPUT;
 	} else if ( strcmp(word, len, "LET", 3 ) ) {
        return TOKEN_LET;
 	} else if ( strcmp(word, len, "GOSUB", 5 ) ) {
        return TOKEN_GOSUB;
 	} else if ( strcmp(word, len, "RETURN", 6 ) ) {
        return TOKEN_RETURN;
 	} else if ( strcmp(word, len, "LIST", 4 ) ) {
        return TOKEN_LIST;
 	} else if ( strcmp(word, len, "RUN", 3 ) ) {
        return TOKEN_RUN;
 	} else if ( strcmp(word, len, "END", 3 ) ) {
        return TOKEN_END;
 	} else if ( strcmp(word, len, "(", 1 ) ) {
        return TOKEN_LPAREN;
 	} else if ( strcmp(word, len, ")", 1 ) ) {
        return TOKEN_RPAREN;
 	} else if ( strcmp(word, len, ",", 1 ) ) {
        return TOKEN_COMMA;
 	} else if ( strcmp(word, len, "*", 1 ) ) {
        return TOKEN_MUL;
 	} else if ( strcmp(word, len, "/", 1 ) ) {
        return TOKEN_DIV;
 	} else if ( strcmp(word, len, "-", 1 ) ) {
        return TOKEN_SUB;
 	} else if ( strcmp(word, len, "+", 1 ) ) {
        return TOKEN_ADD;
 	} else if ( strcmp(word, len, "=", 1 ) ) {
        return TOKEN_EQ;
 	} else if ( strcmp(word, len, "<", 1 ) ) {
        return TOKEN_LT;
 	} else if ( strcmp(word, len, ">", 1 ) ) {
        return TOKEN_GT;
 	} else if ( strcmp(word, len, "<>", 2 ) ) {
        return TOKEN_NEQ;
 	} else if ( strcmp(word, len, "<=", 2 ) ) {
        return TOKEN_LE;
 	} else if ( strcmp(word, len, ">=", 2 ) ) {
        return TOKEN_GE;
 	} else if ( strcmp(word, len, "&", 1 ) ) {
        return TOKEN_AND;
 	} else if ( strcmp(word, len, "|", 1 ) ) {
        return TOKEN_OR;
 	} else if ( strcmp(word, len, "^", 1 ) ) {
        return TOKEN_XOR;
 	} else if ( strcmp(word, len, "<<", 2 ) ) {
        return TOKEN_SLL;
 	} else if ( strcmp(word, len, "<<", 2 ) ) {
        return TOKEN_SRL;
    } else if ( len > 1 && word[0] == '"' && word[len-1] == '"' ) {
        return TOKEN_STR;
    } else if ( len == 1 && word[0] >= 'A' && word[0] <= 'Z' ) {
        return TOKEN_ID;
    } else if ( isNumber(word, len) ){
        return TOKEN_NUM;
    } else {
        return TOKEN_ERROR;
    }
}




