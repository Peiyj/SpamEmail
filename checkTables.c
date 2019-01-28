/*
 * File: checkTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Perform the check in each table by calling retrieveBit() or 
 * retrieveLinkedList() on each table as appropriate.
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: checkTables()
 * Function Prototype: int checkTables( char * str, table_t * htbl, 
 *                                      table_t * rtbl, table_t * eotbl ) 
 * Description: Perform the check in each table by calling retrieveBit() or 
 * retrieveLinkedList() on each table as appropriate. 
 * out the result for each search.
 * for each of the 3 tables.
 * Parameters: str: the string to be searched
 *             htbl: htbl table
 *             rtbl: rtbl table
 *             eotble: eotble table
 * Side Effects: none
 * Return values: int
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pa3.h"
//#include "retrieveBit.c"
int checkTables( char * str, table_t * htbl, table_t * rtbl, table_t * eotbl ){
    int count = 0;
    //Perform the check in htbl, rtbl table by calling retrieveBit()
    if(retrieveBit(htbl, str) == 1){
        count ++;
        if(retrieveBit(rtbl, str) == 1){
            count ++;
            // Perform the check in eotbl by calling retrieveLinkedList()
            linkedList_t *myll = retrieveLinkedList(eotbl ,str);
            if(myll != NULL){
                count++;
                while(myll){
                    if(strcmp(str, myll->value) == 0){
                        return EXACT_MATCH;
                    }
                    myll = myll -> next;
                }
            }
        }
    }
    return count;
}


