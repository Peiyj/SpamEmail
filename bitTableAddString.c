/*
 * File: bitTableAddString.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can call table-->hashfunction() to has 
 * order
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: bitTableAddString()
 * Function Prototype: void bitTableAddString( table_t* table, char* string);
 * Description: Call table->hashFunction() to hash string. 
 * Parameters: table: the hash table
 *             str: the string to be added
 * Side Effects: dymanic memory allocation
 * Return values: void
 */
#include "pa3.h"
#include <stdlib.h>
#include <string.h>
#define MASK 8
void bitTableAddString( table_t* table, char* string){

    ////////////////////get the hashkey//////////////////
    int hashkey = table -> hashFunction(string);
    ////////////////////get the index////////////////
    int index = (((hashkey % table->size) + table->size) % table->size);

    ///////////////////separate to countR and countL///////////
    int countR = index / MASK;
    int countL = index % MASK;
    ////////////////////set the bitArray to 1/////////////////
    table -> bitArray[countR] = (table -> bitArray[countR]) 
                              | (0x1 << countL);
}
