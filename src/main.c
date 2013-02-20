/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yyparse(void);

int main( int argc, char *argv[] ) {
    char cmdStr[256], *cmd_val[10];
    int index=0;
    
    if ( argc > 1 ) {
        printf("Options given.\n");
    }

    add_function("add", &add);
    add_function("deduct", &deduct);
    add_function("multiply", &multiply);
    add_function("exit", &exit_cli);
    add_function("value", &value);
    add_function("Graph", &Graph);
    add_function("DiGraph", &DiGraph);
    add_function("MultiGraph", &MultiGraph);
    add_function("MultiDiGraph", &MultiDiGraph);
    add_function("len", &len);
    add_function("add_node", &add_node);
    add_function("add_edge", &add_edge);
    add_function("order", &order);

    Py_SetProgramName("NetworkExtended");
    Py_Initialize();
    NX_object* nx_module = load_networkx();
    load_objects(nx_module);

    while(1) {
        printf("[NetworkExtended]: ");
        memset(cmdStr, 0x00, sizeof(cmdStr));
        fgets(cmdStr, 255, stdin);

        yyin = fopen("cmd", "w+");
        fprintf(yyin, "%s", cmdStr);
        fseek(yyin, 0, SEEK_SET);

        yyparse();

        /*
        char *p;
        int index, j=0;
        params pmain;

        p = strchr(cmdStr, '=');
        if (p != NULL) {
            index = 2;
        } else {
            index = 1;
        }

        int size_cmd = index-1;
        parsecommand(cmdStr, cmd_val, &size_cmd);

        if ( index == 2 ) {
            pmain.var_name = cmd_val[0];
        } else {
            pmain.var_name = "ans";
        }

        int margc = size_cmd-index;

        pmain.cmd_size = margc;
        if ( margc != 0 ) {
            char *cmd_val_tmp[8];
            for ( j=0; j<margc; j++ ) {
                cmd_val_tmp[j] = cmd_val[j+index];
            }
            pmain.cmd_val = cmd_val_tmp;
        }

        hash_func *instance = find_function(cmd_val[index-1]);
        NX_object* nx_obj;

        if ( instance != NULL ) {
            int output = compute(instance->func_call, pmain);
        } else {
            printf("Command not found. Try again.\n");
        }
        */
        remove ("cmd");
    }
    Py_Finalize();
    return 0;
}
