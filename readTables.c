/*
 * File: readTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Read from inFile and populate the three hashtables 
 * serialized in writeTables()
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: readTables()
 * Function Prototype: void readTables( FILE * inFile, table_t * htbl,
 *                                      table_t * rtbl, table_t * eotbl ) 
 * Description: Read from inFile and populate the three hashtables
 * serialized in writeTables(). You can assume the inFile is a file of 
 * the same format produced by writeTables() out the result for each search.
 * Parameters: inFile: the input file
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
#define allBits 7
#define byte 8

void readTables( FILE * inFile, table_t * htbl, table_t * rtbl, 
        table_t * eotbl ){
    int sizeToRead;
    int i;
    int j;
    //////////////read the size of hashtables///////
    fread(&sizeToRead, sizeof(int), 1, inFile);
    ///////////////////initialize struct///////////////

    htbl->hashFunction = hash;
    htbl->size = sizeToRead;
    htbl->bitArray = calloc((htbl->size + allBits) /byte,1);

    if(htbl -> bitArray == NULL){
        perror(MEM_ERR);
        return;
    }

    rtbl->hashFunction = revHash;
    rtbl->size = sizeToRead;
    rtbl->bitArray = calloc((rtbl->size + allBits) /byte,1);

    if(rtbl -> bitArray == NULL){
        perror(MEM_ERR);
        free(htbl->bitArray);
        return;
    }

    eotbl->hashFunction = evenOddHash;
    eotbl->size = sizeToRead;
    eotbl->llArray = calloc(eotbl->size, sizeof(struct linkedList_t*));

    if(eotbl -> llArray == NULL){
        perror(MEM_ERR);
        free(htbl->bitArray);
        free(rtbl->bitArray);
        return;
    }
    //////////////read all entries of htbl/////////////
    fread(htbl -> bitArray, sizeof(char), 
            (htbl->size + allBits)/byte, inFile);

    //////////////read all entries of rtbl/////////////
    fread(rtbl -> bitArray, sizeof(char), 
            (rtbl->size + allBits)/byte, inFile);
    ///////////////read the content of eotbl/////////
    char buf[BUFSIZ] = {'\0'};
    int bufSize = 0;
    int numNewBytes = 0;
    int llindex = 0;
    while ((numNewBytes = fread(buf + bufSize, 1, 
                    BUFSIZ - bufSize, inFile)) > 0) {
        bufSize += numNewBytes;
        i = 0;
        char *ptr = buf;
        int temp = bufSize;
        while(i < temp){
            for(j = i; j < temp; j++){
                // case 1: if read null terminator
                //two buckets
                if(buf[i] == '\0'){
                    llindex ++;
                    i++;
                    bufSize --;
                }
                else if(buf[j] == '\0'){
                    ptr = buf + i;
                    prependNode(&eotbl->llArray[llindex], ptr);
                    bufSize = bufSize - (strlen(ptr) + 1);
                    //set the index
                    i = j + 1;
                }
            }
            i++;
        }
        memmove(buf, buf + BUFSIZ - bufSize, bufSize);
    }
}

