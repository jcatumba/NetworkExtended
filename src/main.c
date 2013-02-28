/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "main.h"

int main ( int argc, char *argv[] ) {
    char cmdStr[256], *cmd_val[10];
    int index=0;
    
    if ( argc > 1 ) {
        printf ("Options given.\n");
    }

    init_table ();
    s = (stack*) malloc (sizeof (stack));
    s->top = -1;

    Py_SetProgramName ("NetworkExtended");
    Py_Initialize ();
    init_networkx ();

    while (1) {
        printf ("[NetworkExtended]: ");
        memset (cmdStr, 0x00, sizeof (cmdStr));
        fgets (cmdStr, 255, stdin);

        yyin = fopen ("cmd", "w+");
        fprintf (yyin, "%s", cmdStr);
        fseek (yyin, 0, SEEK_SET);

        yyparse ();

        remove ("cmd");
    }
    Py_Finalize ();
    return 0;
}
