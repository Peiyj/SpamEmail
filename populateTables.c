/*
 * File: populateTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that populates 3 hash tables by reading in dataFule
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: populateTables()
 * Function Prototype: void bitTableAddString( table_t* htbl, table_t* rtbl,
 *                                             table_t* eotbl, FILE* dataFile)
 * Description: This function populates 3 hash tables by reading in dataFile, 
 * grabbing each line using fgets(), and calling the proper addString function
 * for each of the 3 tables.
 * Parameters: htbl: htbl table
 *             rtbl: rtbl table
 *             eotble: eotble table
 *             dataFile: the data file
 * Side Effects: none
 * Return values: void
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa3.h"
#define newL '\n'

void populateTables( table_t * htbl, table_t * rtbl, 
                     table_t * eotbl, FILE * dataFile ){
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, dataFile)){ 
        /////////////////declare a char array to store the read value///////////
        char *ret;
        /////////////////////put the string in into buf[BUFSIZ]/////////////
        ret = strchr(buf, newL);
        *ret = '\0';
        ///////////////////now find '\n' and convert to '\0'///////////////
        for(int i = 0; i < strlen(buf); i++) {            
            buf[i] = tolower(buf[i]);
        }
        bitTableAddString(htbl, buf);
        bitTableAddString(rtbl, buf);
        llTableAddString(eotbl, buf);
    }
}
