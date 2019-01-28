/*
 * File: evenOddHash.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can create the hask key of a string in alternating
 * order
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: evenOddHash()
 * Function Prototype: int evenOddHash(char *str);
 * Description: This function creates an integer hash key from str with the 
 *              hashing algorithm. 
 * Parameters: str* = a pointer to a string
 * Side Effects: increment i++
 * Return values: int hash key: the key value of the hash
 */
#include <string.h>
#include <stdlib.h>

#include "pa3.h"
#define alterIndex 2


 int evenOddHash(char* str){
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    int i;
    for(i = 0; i < strLen; i += alterIndex){
        hash = hash * HASH_PRIME + str[i];
    }
    for(i = 1; i < strLen; i += alterIndex){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
 }
