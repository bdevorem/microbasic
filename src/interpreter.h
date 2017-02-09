#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "token.h"

void stmt(breezy_t *l, int &i);
breezy_t relop(breezy_t *l, int &i);
breezy_t expr(breezy_t *l, int &i);
breezy_t term(breezy_t *l, int &i);
breezy_t factor(breezy_t *l, int &i);

#endif





