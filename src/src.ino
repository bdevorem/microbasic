#define CLK P1_4
#define DAT P1_5
#include "lut.h"
#include "token.h"

#define NVARS (10)
#define MAX_LEN (40)
#define STR_TABL_W (10)
#define STR_TABL_H (5)

#define ESC "\033"

int count = 0;
int data = 0;
int o = 0;

int line_len = 0; 

int str_ptr = 0;

char STR_TABL[STR_TABL_W][STR_TABL_H];

int vars[NVARS];
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
			len++;
		}
	}
	line_tokens[token_num].token = TOKEN_CR;
	return 0;
}

void _print(breezy_t e){
	if (e.token == TOKEN_ERROR)
		Serial.println("ERROR: parse failed, you suck");
	else 
		Serial.print(e.value);
}

void _println(breezy_t e){
	if (e.token == TOKEN_ERROR)
		Serial.println("ERROR: parse failed, you suck");
	else 
		Serial.println(e.value);
}

int parser(breezy_t *l) {
	// parse and execute one line at a time
	int i = 1;
	breezy_t _var;
	breezy_t _expr;

	switch (l[0].token) {
		case TOKEN_NUM:
			Serial.println("ERROR: not implemented");
			return 1;
		case TOKEN_PRINT:
			do {
				if (l[i].token == TOKEN_STR){
					Serial.print(STR_TABL[l[i].value]);
					i++; // next token
				} else if (l[i].token == TOKEN_COMMA){
					Serial.print(" ");
					i++;
				} else if (l[i].token == TOKEN_ID){
					_print(expr(l, i));
					//i++;
				} else if (l[i].token == TOKEN_NUM){
					_print(expr(l, i));
					//i++;
				} else {
					Serial.println("ERROR: parse failed, you suck");
					return 1; //error
				}
			} while (l[i].token != TOKEN_CR);
			Serial.println();
			break;
		case TOKEN_IF:
			break;
		case TOKEN_GOTO:
			break;
		case TOKEN_INPUT:
			break;
		case TOKEN_LET:
			_var = l[i];
			i++;
			if (_var.token == TOKEN_ID && l[i].token == TOKEN_EQ){
				Serial.println((char)('A'+l[1].value));
				i++;
				_expr = expr(l, i);
				if (_expr.token == TOKEN_ERROR){
					Serial.println("ERROR: parse failed, you suck");
					return 1;
				} else
					vars[_var.value] = _expr.value;
			} else {
				Serial.println("ERROR: parse failed, you suck");
				return 1;
			}
			break;
		case TOKEN_CLEAR:
			Serial.print(ESC"[2J");
			Serial.print(ESC"[0;0H");
			break;
		case TOKEN_LIST:
			for (int i = 0; i < NVARS; i++) {
				Serial.print((char)('A' + i));
				Serial.print(" = ");
				Serial.println( (vars[i]>>15)? STR_TABL[vars[i]&~(1<<15)] : vars[i] );
			}
			break;
	} 
}

breezy_t expr(breezy_t *line, int &i){
	breezy_t t1, t2;
	token_t op;
	t1 = term(line, i); //all muls and divs
	op = line[i].token;

	while (op == TOKEN_ADD || 
			op == TOKEN_SUB ||
			op == TOKEN_AND ||
			op == TOKEN_OR) {

		i++;
		t2 = term(line, i);
		if (t1.token == TOKEN_ERROR || t2.token == TOKEN_ERROR)
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

breezy_t term(breezy_t *line, int &i) {
	breezy_t f1, f2;
	token_t op;

	f1 = factor(line, i); //vars, numbers
	op = line[i].token;

	while (op == TOKEN_MUL || op == TOKEN_DIV) {
		i++;
		f2 = factor(line, i);
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
	switch (line[i].token){
		case TOKEN_NUM:
			r = line[i];
			i++;
			break;
		case TOKEN_ID:
			r = (breezy_t){TOKEN_NUM, vars[line[i].value]};
			i++;
			break;
			//Serial.println("ERROR: not implemented");
			//return (breezy_t){TOKEN_ERROR, 0};
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




