#define CLK P1_4
#define DAT P1_5
#include "dumb.h"
#include "lut.h"
#include "token.h"
#include "interpreter.h"

int str_ptr = 0;
char STR_TABL[STR_TABL_H][STR_TABL_W];
int vars[NVARS];
char line[MAX_LEN+1];
breezy_t BREEZYXR[MAX_LOOP_TOKENS];
int _loop = 0;
int pc = 0;

int count = 0;
int data = 0;
int o = 0;
int line_len = 0; 


void setup() {
	Serial.begin(9600);
	Serial.println(ESC"[1;37mREADY"ESC"[0;37m");
	pinMode(DAT, INPUT);
	lock();
	sleep(3);
	unlock();
}

void loop() {
	int n = digitalRead(CLK);
	breezy_t line_tokens[20];
	int ret_val;

	if ((!n)&&(n!=o)) {
		data|=digitalRead(DAT)<<(count++);
		if (count >= 11) {
			lock();
			data = data>>1; //kill stop bit
			data &= ~0x100; //kill start bit
			char toAdd = doLut(data);
			if (line_len < MAX_LEN || toAdd == '\b' || toAdd == '\n') {
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
							   if (ret_val == 1) Serial.println(ERR": scan failed, you suck"); 
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
        char inQuote = 0;
	token_t type;
	line[line_len] = ' ';
	for (int i = 0; i <= line_len; i++) {
		char c = line[i];
		if (c == ' ' && !inQuote) {
			wordle[len] = 0;
			type = scan_token(wordle, len);
			if (type == TOKEN_NUM)
				line_tokens[token_num] = (breezy_t){type, atoi(wordle)};
			else if (type == TOKEN_STR) {
				wordle[len-1] = 0;
				strcpy(wordle+1, STR_TABL[cycle_str_ptr()]);
				line_tokens[token_num] = (breezy_t){type, str_ptr};
			}
			else if (type == TOKEN_ID)
				line_tokens[token_num] = (breezy_t){type, (*wordle)-'A'};
			else if (type == TOKEN_ERROR) return 1;
			else line_tokens[token_num] = (breezy_t){type, 0};
			token_num++;
			wordle+=len+1;
			len=0;
		} else {
                        if (c == '"') inQuote = !inQuote;
			len++;
		}
	}
	line_tokens[token_num].token = TOKEN_CR;
	return 0;
}

void parser(breezy_t *l) {
	// parse and execute one line at a time
	int i = 0;
	int j = 0;
	if (l[0].token == TOKEN_NUM || _loop) {
                do {
		    BREEZYXR[pc] = l[j];
                    pc++; //add to program counter to keep track of loops
                    j++;
	        } while (l[j].token != TOKEN_CR);
		i += 1 - _loop; //move past TOKEN_NUM if we are on a label
                _loop = 1;
	}
	stmt(l, i);
}

void lock() {
	pinMode(CLK, OUTPUT);
	digitalWrite(CLK, LOW); 
}

void unlock() {
	pinMode(CLK, INPUT);
}

int cycle_str_ptr() {
	return str_ptr = (str_ptr + 1) % STR_TABL_H;
}








