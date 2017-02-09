#include "interpreter.h"
#include "dumb.h"  
void stmt(breezy_t *l, int &i){
	breezy_t _var;
	breezy_t _expr;

	token_t stmt_type = l[i].token;
	i++;
	switch (stmt_type) {
		case TOKEN_NUM:
			Serial.println(ERR": not implemented");
			return;
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
				} else if (l[i].token == TOKEN_NUM || l[i].token == TOKEN_LPAREN){
					_print(expr(l, i));
				} else {
					Serial.println(ERR": parse failed, you suck");
					return;
				}
			} while (l[i].token != TOKEN_CR);
			Serial.println();
			break;
		case TOKEN_IF:
			breezy_t r;
			r = relop(l, i);

			if (l[i].token == TOKEN_THEN) i++;
			else {
				Serial.println(ERR": parse failed, you suck");
				return; //error
			}
			if (r.value) stmt(l, i);
			else {
				do { i++; } while (l[i].token != TOKEN_CR);
				if (l[i].token == TOKEN_CR) i++;
			}	
			break;
		case TOKEN_LET:
			_var = l[i];
			i++;
			if (_var.token == TOKEN_ID && l[i].token == TOKEN_EQ){
				Serial.println((char)('A'+l[1].value));
				i++;
				_expr = expr(l, i);
				if (_expr.token == TOKEN_ERROR){
					Serial.println(ERR": parse failed, you suck");
					return;
				} else
					vars[_var.value] = _expr.value;
			} else {
				Serial.println(ERR": parse failed, you suck");
				return;
			}
			break;
		case TOKEN_CLEAR:
			Serial.print(ESC"[2J"ESC"[0;0H");
			break;
		case TOKEN_LIST:
			for (int i = 0; i < NVARS; i++) {
				Serial.print((char)('A' + i));
				Serial.print(" = ");
                Serial.println(vars[i]);
			}
			break;
		case TOKEN_GOTO:
		case TOKEN_GOSUB:
		case TOKEN_RUN:
		case TOKEN_END:
		case TOKEN_INPUT:
			break;
	} 
}

breezy_t relop(breezy_t *l, int &i) {
	breezy_t r1, r2;
	token_t op;
	
	r1 = expr(l, i);
	op = l[i].token;

	while (op == TOKEN_LT ||
			op == TOKEN_GT ||
			op == TOKEN_EQ ||
			op == TOKEN_LE ||
			op == TOKEN_GE ||
			op == TOKEN_NEQ) {

		i++;
		r2 = expr(l, i);
		switch (op) {
			case TOKEN_LT:
				r1.value = r1.value < r2.value;
				break;
			case TOKEN_GT:
				r1.value = r1.value > r2.value;
				break;
			case TOKEN_EQ:
				r1.value = r1.value == r2.value;
				break;
			case TOKEN_LE:
				r1.value = r1.value <= r2.value;
				break;
			case TOKEN_GE:
				r1.value = r1.value >= r2.value;
				break;
			case TOKEN_NEQ:
				r1.value = r1.value != r2.value;
				break;
		}
		op = l[i].token;
	}
	return r1;
}

breezy_t expr(breezy_t *l, int &i){
	breezy_t t1, t2;
	token_t op;
	t1 = term(l, i); //all muls and divs
	op = l[i].token;

	while (op == TOKEN_ADD || 
			op == TOKEN_SUB ||
			op == TOKEN_AND ||
			op == TOKEN_OR) {

		i++;
		t2 = term(l, i);
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
		op = l[i].token;
	}
	return t1;
}

breezy_t term(breezy_t *l, int &i) {
	breezy_t f1, f2;
	token_t op;

	f1 = factor(l, i); //vars, numbers
	op = l[i].token;

	while (op == TOKEN_MUL || op == TOKEN_DIV) {
		i++;
		f2 = factor(l, i);
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
		op = l[i].token;
	}
	return f1;
}

breezy_t factor(breezy_t *l, int &i){
	breezy_t r;
	switch (l[i].token){
		case TOKEN_NUM:
			r = l[i];
			i++;
			break;
		case TOKEN_ID:
			r = (breezy_t){TOKEN_NUM, vars[l[i].value]};
			i++;
			break;
			//Serial.println(ERR": not implemented");
			//return (breezy_t){TOKEN_ERROR, 0};
		case TOKEN_LPAREN:
			i++;
			r = expr(l, i);
			if (l[i].token == TOKEN_RPAREN) i++;
			else r = (breezy_t){TOKEN_ERROR, 0};
                        break;
		default:
			Serial.println(ERR": parse failed, you suck");
			return (breezy_t){TOKEN_ERROR, 0};
	}
	return r;
}
