/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#define MAXSIZE 10 /* Maxsize for stack */

/* Union definition for data */
typedef union {
    double number;
    char string[16];
} data;

/* Structure definition for stack */
struct stack {
    int top;
    int type;
    data value;
    struct stack *next;
};

typedef struct stack stack;
stack *s;

/* Function type */
typedef double (*func_t) (double);
typedef double (*func_p) (stack*);
     
/* Data type for links in the chain of symbols */
struct symrec
{
    char *name;  /* name of symbol */
    int type;    /* type of symbol: either VAR or FNCT */
    union
    {
      double var;      /* value of a VAR */
      func_t fnctptr;  /* value of a FNCT */
      func_p fncpptr;  /* value of a FNCP */
    } value;
    struct symrec *next;  /* link field */
};
     
typedef struct symrec symrec;
     
/* The symbol table: a chain of `struct symrec' */
extern symrec *sym_table;

symrec *putsym (char const *, int);
symrec *getsym (char const *);

/* Functions to manipulate stack */
void push (int, double);
int pop (void);
void display (void);

/* Functions to handle stack structs */
stack * putitem (int, int);
stack * getitem (int);
void clear_stack (void);
