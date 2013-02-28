/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#define MAXSIZE 10 /* Maxsize for stack */
#include <Python.h>

typedef struct{
    int cmd_size;
    char *var_name;
    char **cmd_val;
} params;

typedef struct {
    const char* name;
    const char* parent;
    PyObject* py_object;
} NX_object;

typedef NX_object* (*nxfunction)(params);

/* Union definition of data for stack */
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
typedef NX_object* (*func_nx) (stack*);

typedef union { /* TODO: Add lists and dictionaries */
    double num;
    char str[50];
    NX_object *obj;
} varval;

typedef struct {
    int type; /* Type of data: NUM, STR, NXO */
    varval data;
} datatype;

/* Data type for links in the chain of symbols */
struct symrec {
    char *name;  /* name of symbol */
    int type;    /* type of symbol: either VAR, FNCT, FNCP or FNCNX */
    union {
        datatype var;     /* value of a VAR */
        func_t fnctptr;   /* value of a FNCT */
        func_p fncpptr;   /* value of a FNCP */
        func_nx fnxptr;   /* value of a FNCNX*/
    } value;
    struct symrec *next;  /* link field */
};
     
typedef struct symrec symrec;
     
/* The symbol table: a chain of `struct symrec' */
extern symrec *sym_table;

symrec *putsym (char const *, int);
symrec *getsym (char const *);

/* Functions to manipulate stack */
void push (int, datatype);
int pop (void);
void display (void);
void clear_stack (void);

/* Functions to handle stack chain */
stack *putitem (int, int);
stack *getitem (int);
