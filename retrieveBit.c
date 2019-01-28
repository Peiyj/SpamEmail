/*
 * File: retrieveBit.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can call table->hashFunction() to hash string. 
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: retrieveBit()
 * Function Prototype: int retrieveBit( table_t *table, char *string )
 * Description: Call table->hashFunction() to hash string. Note that 
 * the hashkey returned by each of the hash functions will not necessarily
 * be an index within the size of the hash table.  
 * Parameters: head: a new node head
 *             str: the string 
 * Side Effects: dymanic memory allocation
 * Return values: void
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa3.h"
#define MASK 8

int retrieveBit( table_t *table, char *string ){
    int hash = table -> hashFunction(string);
    int index = ((hash % table->size) + table->size) % table->size;
    int countR = index / MASK;
    int countL = index % MASK;

    if(((table -> bitArray[countR]) & (0x1 << countL)) == 0){
        return 0;
    }
    return 1;
}
