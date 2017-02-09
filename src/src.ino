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

int line_len = 0;

String vars[NVARS];
char line[MAX_LEN+1];

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
            if (line_len < MAX_LEN || toAdd == '\b') {
                if (toAdd != 0) {
                    if (toAdd == 'B')
                        Serial.print(ESC"[32m");
                    Serial.print(toAdd);
                    if (toAdd =='B')
                        Serial.print(ESC"[0m");
                }
                switch (toAdd) {
                  case 0: break;
                  case '\b': Serial.print(" \b"); line_len--; break;
                  case '\n': 
                      Serial.print('\r');
                      ret_val = scanner(line, line_tokens);
                      if (ret_val == 1) Serial.println("ERROR: scan failed, you suck"); 
                      else parser(line_tokens);
                      line_len = 0;
                      break;
                  default: line[line_len++] = toAdd; break;
              }
            }
            count = 0;
            data = 0;  
            unlock();
        }
    }
    o = n;
}

int scanner(char* l, breezy_t *line_tokens) {
    char* wordle = l;
    int len = 0;
    int token_num = 0;
    token_t type;
    line[line_len] = ' ';
    for (int i = 0; i <= line_len; i++) {
      char c = line[i];
      if (c == ' ') {
        wordle[len] = 0;
        Serial.println(wordle);
        type = scan_token(wordle, len);
        if (type == TOKEN_NUM)
            line_tokens[token_num] = (breezy_t){type, atoi(wordle)};
        else if (type == TOKEN_STR || type == TOKEN_ID)
            line_tokens[token_num] = (breezy_t){type, i};
        else if (type == TOKEN_ERROR) return 1;
        else line_tokens[token_num] = (breezy_t){type, 0};
        token_num++;
        wordle+=len+1;
        len=0;
      } else {
         len++;
      }
    }
    line_tokens[token_num].token = TOKEN_CR;
    return 0;
}

int parser(breezy_t *line) {
    // parse and execute one line at a time
    int i = 0;
    switch (line[i].token) {
        i++;
        case TOKEN_NUM:
            // TODO: implement this 
            break;
        case TOKEN_PRINT:
            do {
                if (line[i].token == TOKEN_STR){
                    Serial.println(line[1].value);
                    i++; // next token
                } else if (line[i].token == TOKEN_COMMA){
                    Serial.println(" ");
                    i++;
                } else if (line[i].token == TOKEN_ID){
                } else if (line[i].token == TOKEN_NUM){
                    Serial.println(expr(line, i).value);
                } else {
                    return 1; //error
                }
            } while (line[i].token != TOKEN_CR);
            // print new line
            break;
        case TOKEN_IF:
            break;
        case TOKEN_GOTO:
            break;
        case TOKEN_INPUT:
            break;
        case TOKEN_LET:
            break;
        case TOKEN_CLEAR:
            Serial.print(ESC"[2J");
            Serial.print(ESC"[0;0H");
            break;
        case TOKEN_LIST:
          for (int i = 0; i < NVARS; i++) {
            Serial.print((char)('A' + i));
            Serial.print(" = ");
            Serial.println(vars[i]);
          }
            break;
    } 
}

breezy_t expr(breezy_t *line, int &i){
    breezy_t t1, t2;
    token_t op;

    t1 = term(i); //all muls and divs
    op = line[i].token;

    while (op == TOKEN_ADD || 
        op == TOKEN_SUB ||
        op == TOKEN_AND ||
        op == TOKEN_OR) {
        
        i++;
        t2 = term(i);
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

breezy_t term(int &i){
}

void lock() {
    pinMode(CLK, OUTPUT);
    digitalWrite(CLK, LOW); 
}

void unlock() {
  pinMode(CLK, INPUT);
}




