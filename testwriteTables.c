/*
 * Filename: testwriteTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function writeTables().
 * Date: Nov 7th, 2018
 * Sources of Help: Tutor
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "freeLinkedList.c"

/*
 * Unit Test for testwriteTables()
 *
 * void writeTables( FILE *outFile, table_t * htbl, table_t * rtbl, 
 * table_t * eotbl);
 *
 */
static int hashC(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for( int i = 0; i < strLen; i++ ) {
         hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}

static int revHashC(char * str) {
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for(int i = strLen - 1; i >= 0 ; i--){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}

static int evenOddHashC(char* str){
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    int i;
    for(i = 0; i < strLen; i += 2){
        hash = hash * HASH_PRIME + str[i];
    }
    for(i = 1; i < strLen; i += 2){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
 }

void testwriteTables() {
    table_t htbl;
    table_t rtbl;
    table_t eotbl;

    htbl.size = DEFAULT_SIZE;
    rtbl.size = DEFAULT_SIZE;
    eotbl.size = DEFAULT_SIZE;

    htbl.hashFunction = &hashC;
    rtbl.hashFunction = &revHashC;
    eotbl.hashFunction = &evenOddHashC;

    htbl.bitArray = calloc(1, (htbl.size + 7)/8);
    rtbl.bitArray = calloc(1, (rtbl.size + 7)/8);
    eotbl.llArray = malloc(eotbl.size* sizeof(linkedList_t));


    FILE* inFile = fopen("emails_10", "rb");
    populateTables(&htbl, &rtbl, &eotbl, inFile);
    
    ////////////////////test write file//////////////////
    FILE *outFile = fopen("outFile", "wb+");
    writeTables(outFile, &htbl, &rtbl, &eotbl);

    
    ////////////////////free the memory/////////////////
    /*
    free(htbl.bitArray);
    free(rtbl.bitArray);
    for(int i = 0; i < (eotbl.size + 7) /8; i++){
        freeLinkedList(*(eotbl.llArray));
    }
    free(eotbl.llArray);
    fclose(inFile);
    fclose(outFile);*/
}


int main() {
  fprintf( stderr, "Testing writeTable...\n\n" );
  testwriteTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
