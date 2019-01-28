/*
 * File: launchUserQuery.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function handles user interaction to search the tables
 * and prints out the result for each search.
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: launchUserQuery()
 * Function Prototype: void launchUserQuery(table_t * htbl, table_t * rtbl, 
 *                                          table_t * eotbl)
 * Description:This function handles user interaction to search the tables and prints 
 * out the result for each search.
 * for each of the 3 tables.
 * Parameters: htbl: htbl table
 *             rtbl: rtbl table
 *             eotble: eotble table
 * Side Effects: none
 * Return values: void
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "pa3Strings.h"
#include "pa3.h"
#define USER_TWO 2
#define USER_THREE 3
#define newL '\n'

void launchUserQuery(table_t * htbl, table_t * rtbl, table_t * eotbl){
    char buf[BUFSIZ];
    printf(USER_PROMPT);
    while(fgets(buf,BUFSIZ,stdin)){
        //First, start by printing out a prompt for the user to input the string. 
        //if user did not enter any string, reprompt
        if(buf[0] == newL){
            printf(USER_PROMPT);
            continue;
        }
        char * ret;
        ret = strchr(buf, newL);
        *ret = '\0';
        for(int i = 0; i < strlen(buf); i++){
            buf[i] = tolower(buf[i]);
            //printf("lower case %c\n", buf[i]);
        }
        //if user entered anything, we check table
        int count = checkTables(buf, htbl, rtbl, eotbl);
        if(count == 0){
            printf(WORD_NOT_FOUND, buf);
        }
        else if(count == 1){
            printf(FOUND_IN_SOME, buf, 1);

        }
        else if(count == USER_TWO){
            printf(FOUND_IN_SOME, buf, USER_TWO);
        }
        else if(count == USER_THREE){
            printf(FOUND_IN_SOME, buf, USER_THREE);
        }
        else{
            printf(FOUND_IN_ALL, buf);
        }
        printf(USER_PROMPT);

    }
    printf("%c", newL);
}
