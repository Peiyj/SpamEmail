/*
 * File: writeTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that writes 3 hash tables by writing in dataFule
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: writeTables()
 * Function Prototype: void writeTables( FILE* dataFile, table_t* htbl, 
 *                                       table_t* rtbl,
 *                                       table_t* eotbl) 
 * Description: This function writes 3 hash tables by writing in dataFile,
 * It writes the size of the tables, all entries of htbl, rtbl and strings in
 * eotbl for each of the 3 tables.
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

#define allBits 7
#define byte 8
#define nullP '\0'

void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl, 
                  table_t * eotbl ){
    int i;
    //////////////Write the size of the tables///////////
    int sizeToWrite = htbl -> size;
    //FILE *outputFile = fopen("outFile", "wb");
    fwrite(&sizeToWrite, sizeof(int),1, outFile);

    //////////////Write all entries of htbl/////////////
    fwrite(htbl -> bitArray, sizeof(char), 
        (htbl->size + allBits)/byte, outFile);

    /////////////Write all entries of rtbl/////////////
    fwrite(rtbl -> bitArray, sizeof(char), 
        (rtbl->size + allBits)/byte, outFile);


    ////////////Write the strings in each bucket of eotbl///////
    for(i = 0; i < htbl -> size; i++){
        linkedList_t *ptr = eotbl -> llArray[i];
        while(ptr){
            fputs(ptr->value, outFile);
            ptr = ptr -> next;
            fputc(nullP,outFile);
        }
        fputc(nullP, outFile);   
    }
}

