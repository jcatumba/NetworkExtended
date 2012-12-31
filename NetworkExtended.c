/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <uthash.h>

typedef struct {
    char id[10];
    int value;
    UT_hash_handle hh;
} hashtable;

hashtable *clivariables = NULL;

void add_variable(char repr[10], int amount) {
    hashtable *s;

    s = (hashtable*)malloc(sizeof(hashtable));
    strcpy(s->id, repr);
    s->value = amount;
    HASH_ADD_STR(clivariables, id, s);
}

hashtable *find_variable(char key[10]) {
    hashtable *s;

    HASH_FIND_STR(clivariables, key, s);
    return s;
}

void parsecommand (char *command, char **p_parsed) {
    int i=1,j;
    char *result = NULL;

    result = strtok(command, "=");
    p_parsed[0] = result;
    if (result != NULL) {
        result = strtok(NULL, "(");
        p_parsed[1] = result;
    }
    while (result != NULL ) {
        i++;
        result = strtok(NULL, ",");
        p_parsed[i] = result;
    }
    result = strtok(p_parsed[i-1],")");
    p_parsed[i-1] = result;

    for (j=0;j<i;j++) {
        printf("[%d : %s]\n", j, p_parsed[j]);
    }
}

// Principal

int main( int argc, char *argv[] ) {
    char cmdStr[256], *user, hostname[256], *cmd_val[5];
    int index=0, begin, end;
    
    if ( argc > 1) {
        printf("Options given.\n");
    }

    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));
    user = (char *)getenv("USER");

    if( user == NULL ) {
    	strcpy(user, "unknown");
    }

    while(1) {
        printf("[NetworkExtended]: ");
    	memset(cmdStr, 0x00, sizeof(cmdStr));
	    gets(cmdStr);
	    parsecommand(cmdStr, cmd_val);
	    if ( strncmp("exit", cmd_val[0], 4) == 0 ) {
	        return 0;
	    } else if ( strncmp("add", cmd_val[0], 5) == 0 ) {
	        int result = atoi(cmd_val[1]) + atoi(cmd_val[2]);
	        printf("%d\n", result);
	    } else if ( strncmp("deduct", cmd_val[0], 6) == 0 ) {
	        int result = atoi(cmd_val[1]) - atoi(cmd_val[2]);
	        printf("%d\n", result);
	    } else if ( strncmp("multiply", cmd_val[0], 11) == 0 ) {
	        int result = atoi(cmd_val[1]) * atoi(cmd_val[2]);
	        printf("%d\n", result);
	    } else {
	        printf("Unknown command. Try again.\n");
	    }
    }
    return 0;
}
