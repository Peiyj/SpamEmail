/*
 * Filename: testpopulateTables.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function populateTables().
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
 * Unit Test for testpopulateTables()
 *
 * void populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl, 
 * FILE * dataFile );
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

void testpopulateTables() {
    table_t htbl;
    table_t rtbl;
    table_t eotbl;

    htbl.size = 50;
    rtbl.size = 50;
    eotbl.size = 50;


    htbl.hashFunction = &hashC;
    rtbl.hashFunction = &revHashC;
    eotbl.hashFunction = &evenOddHashC;

    htbl.bitArray = calloc(1,(htbl.size + 7)/8); //ceiling of size/8
    rtbl.bitArray = calloc(1,(rtbl.size + 7)/8); //ceiling of size/8
    eotbl.llArray = malloc((eotbl.size + 7)/8 * sizeof(linkedList_t));

    FILE* inFile = fopen("readFile", "rb");
    populateTables(&htbl, &rtbl, &eotbl, inFile);
   
    ///////////////////test size////////////////
    TEST(htbl.size == 50);
    TEST(rtbl.size == 50);
    TEST(eotbl.size == 50);

    /////////////////test bitArray/////////////
    TEST(*(htbl.bitArray) == 0x30);
    TEST(*(rtbl.bitArray) == 0x30);
   
    /////////////////test llArray///////////// 
    TEST(strcmp(eotbl.llArray[4] -> value, "a") == 0);
    TEST(strcmp(eotbl.llArray[5] -> value, "b") == 0);
    

    ////////////////free the value////////////
    free(htbl.bitArray);
    free(rtbl.bitArray);
    for(int i = 0; i < (eotbl.size + 7)/8; i++){
        //free each linkedlist
        freeLinkedList((eotbl.llArray[i]));    
    }
    //free(eotbl.llArray);
    fclose(inFile);
}


int main() {
  fprintf( stderr, "Testing populateTable...\n\n" );
  testpopulateTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
