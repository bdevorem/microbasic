# Tiny BASIC Grammar
	
	line ::= number statement CR   
		   | statement CR  

	statement ::= PRINT expr_list
				| IF expression relop expression THEN statement  
				| GOTO expression  
				| INPUT var_list  
				| LET var = expression  
				| GOSUB expression  
				| RETURN  
				| CLEAR
				| LIST  
				| RUN  
				| END  

	expr_list ::= (string|expression) (, (string|expression) )*  

	var_list ::= var (, var)*  

	expression ::= (+|-|ε) term ((+|-) term)*
		  
	term ::= factor ((*|/) factor)*
			   
	factor ::= var | number | (expression)
					
	var ::= A | B | C ... | Y | Z
						 
	number ::= digit digit*
						  
	digit ::= 0 | 1 | 2 | 3 | ... | 8 | 9
								   
	relop ::= < (>|=|ε) | > (<|=|ε) | =
