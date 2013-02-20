/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

/* Function type */
typedef double (*func_t) (double);
     
/* Data type for links in the chain of symbols */
struct symrec
{
    char *name;  /* name of symbol */
    int type;    /* type of symbol: either VAR or FNCT */
    union
    {
      double var;      /* value of a VAR */
      func_t fnctptr;  /* value of a FNCT */
    } value;
    struct symrec *next;  /* link field */
};
     
typedef struct symrec symrec;
     
/* The symbol table: a chain of `struct symrec' */
extern symrec *sym_table;
     
symrec *putsym (char const *, int);
symrec *getsym (char const *);
