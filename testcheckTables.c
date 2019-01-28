/*
 * Filename: testcheckTables.c
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
//include "freeLinkedList.c"
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

void testcheckTables(){
    FILE *myinput = fopen("emails_10", "rb");
     ////////////////////////INITIALIZING TABLES////////////////
     table_t htbl = {
        .hashFunction = &hashC,
        .size = DEFAULT_SIZE,
        .bitArray = calloc(1,(DEFAULT_SIZE + 7) /8) //ceiling of size 8
    };
   
    table_t rtbl = {
        .hashFunction = &revHashC,
        .size = DEFAULT_SIZE,
        .bitArray = calloc(1,(DEFAULT_SIZE + 7) /8) //ceiling of size 8
       
    };
   
    table_t eotbl = {
        .hashFunction = &evenOddHashC,
        .size = DEFAULT_SIZE,
        .llArray = malloc(eotbl.size * sizeof(linkedList_t))
    };
    
    //Next call populateTables()
    populateTables(&htbl, &rtbl, &eotbl, myinput);
    int myval = checkTables("horizontal@hack.co", &htbl, &rtbl, &eotbl);
    TEST(myval == 4); 

}


int main() {
  fprintf( stderr, "Testing checkTables...\n\n" );
  testcheckTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}

