#define CLK P1_4
#define DAT P1_5
#include "lut.h"
#include "token.h"

#define NVARS (10)
#define MAX_LEN (40)
#define ESC "\033"

int count = 0;
int data = 0;
int o = 0;
String vars[NVARS];
String line;

void setup() {
    Serial.begin(9600);
    Serial.println("OK");
    pinMode(DAT, INPUT);
    lock();
    sleep(3);
    unlock();
}

void loop() {
    int n = digitalRead(CLK);
    breezy_t line_tokens[35];
    int ret_val;

    if ((!n)&&(n!=o)) {
        data|=digitalRead(DAT)<<(count++);
        if (count >= 11) {
            lock();
            data = data>>1; //kill stop bit
            data &= ~0x100; //kill start bit
            char toAdd = doLut(data);
            if (toAdd != 0) {
                Serial.print(toAdd);
            }
            if (line.length() < MAX_LEN || toAdd == '\b') {
              if (toAdd != 0) {
                  if (toAdd == 'B')
                      Serial.print(ESC"[32m");
                  Serial.print(toAdd);
                  if (toAdd =='B')
                      Serial.print(ESC"[0m");
              }
            switch (toAdd) {
                case 0: break;
                case '\b': Serial.print(" \b"); line = line.substring(0, line.length() - 1); break;
                case '\n': 
                    Serial.print('\r');
                    ret_val = scanner(line, line_tokens);

                    if (ret_val == 1) Serial.println("ERROR: scan failed, you suck"); 
                    else parser(line_tokens); 

                    line = "";
                    break;
                default: line += toAdd; break;
            }
            count = 0;
            data = 0;  
            unlock();
        }
    }
    o = n;
}

int scanner(String &line, breezy_t *line_tokens) {
    String wordle;
    int token_num = 0;
    token_t type;

    line[line.length()-1] = ' ';
    for (int i = 0; i < line.length(); i++) {
      char c = line.charAt(i);
      if (c == ' ') {
        type = scan_token(wordle);
        if (type == TOKEN_NUM || type == TOKEN_STR || type == TOKEN_ID)
            line_tokens[token_num] = (breezy_t){type, wordle};
        else if (type == TOKEN_ERROR) return 1;
        else line_tokens[token_num] = (breezy_t){type, 0};
        Serial.println(str_token(line_tokens[token_num]));
        token_num++;
        wordle = "";
      } else
        wordle += c;
    }
    line_tokens[token_num] = TOKEN_CR;
    return 0;
}

int parser(breezy_t *line){
    // parse and execute one line at a time
    int i = 0;
    switch (line[i].token) {
        i++;
        case TOKEN_NUM:
			Serial.println("ERROR: not implemented");
			return 1;
        case TOKEN_PRINT:
            do {
                if (line[i].token == TOKEN_STR){
                    Serial.print(line[i].value);
                    i++; // next token
                } else if (line[i].token == TOKEN_COMMA){
                    Serial.print(" ");
                    i++;
                } else if (line[i].token == TOKEN_ID){
					Serial.println("ERROR: not implemented");
					return 1;
                } else if (line[i].token == TOKEN_NUM){
                    Serial.print(expr(line, &i).value);
                } else {
                    Serial.println("ERROR: parse failed, you suck");
                    return 1; //error
                }
            } while (line[i].token != TOKEN_CR);
			Serial.println();
            break;
        case TOKEN_IF:
            break;
        case TOKEN_GOTO
            break;
        case TOKEN_INPUT:
            break;
        case TOKEN_LET:
            break;
        case TOKEN_CLEAR:
            break;
        case TOKEN_LIST:
            break;
    } 
}

breezy_t expr(breezy_t *line, int &i){
    breezy_t t1, t2;
    token_t op;

    t1 = term(line, &i); //all muls and divs
    op = line[i].token;

    while (op == TOKEN_ADD || 
        op == TOKEN_SUB ||
        op == TOKEN_AND ||
        op == TOKEN_OR) {
        
        i++;
        t2 = term(line, &i);
		if (t1.token == TOKEN_ERROR || t1.token == TOKEN_ERROR)
			return (breezy_t){TOKEN_ERROR, 0};
        switch (op){
            case TOKEN_ADD:
                t1.value = t1.value + t2.value;
                break;
            case TOKEN_SUB:
                t1.value = t1.value - t2.value;
                break;
            case TOKEN_AND:
                t1.value = t1.value & t2.value;
                break;
            case TOKEN_OR:   
                t1.value = t1.value | t2.value;
                break;
        }
        op = line[i].token;
    }
    return t1;
}

breezy_t term(breezy_t *line, int &i){
    breezy_t f1, f2;
    token_t op;

    f1 = factor(line, &i); //vars, numbers
    op = line[i].token;

    while (op == TOKEN_MUL || op == TOKEN_DIV) {
        i++;
        f2 = factor(line, &i);
		if (f2.token == TOKEN_ERROR || f1.token == TOKEN_ERROR)
			return (breezy_t){TOKEN_ERROR, 0};
        switch (op){
            case TOKEN_MUL:
                f1.value = f1.value * f2.value;
                break;
            case TOKEN_DIV:
                f1.value = f1.value / f2.value;
                break;
        }
        op = line[i].token;
    }
    return f1;
}

breezy_t factor(breezy_t *line, int &i){
    breezy_t r;
	int i;

	switch (line[i].token){
		case TOKEN_NUM:
			r = line[i];
			i++;
			break;
		case TOKEN_VAR:
            Serial.println("ERROR: not implemented");
			return (breezy_t){TOKEN_ERROR, 0};
		case TOKEN_LPAREN:
            Serial.println("ERROR: not implemented");
			return (breezy_t){TOKEN_ERROR, 0};
		case TOKEN_RPAREN:
            Serial.println("ERROR: not implemented");
			return (breezy_t){TOKEN_ERROR, 0};
		default:
            Serial.println("ERROR: parse failed, you suck");
			return (breezy_t){TOKEN_ERROR, 0};
    }
    return r;

void clear() {
    Serial.print(ESC"[2J");
    Serial.print(ESC"[0;0H");
}

void list() {
  for (int i = 0; i < NVARS; i++) {
    Serial.print((char)('A' + i));
    Serial.print(" = ");
    Serial.println(vars[i]);
  }
}

void lock() {
    pinMode(CLK, OUTPUT);
    digitalWrite(CLK, LOW); 
}

void unlock() {
  pinMode(CLK, INPUT);
}



