/*
 * Filename: testrevHash
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function revHash().
 * Date: Nov 7th, 2018
 * Sources of Help: Tutor
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

static int revHashC(char * str) {
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for(int i = strLen - 1; i >= 0 ; i--){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}

/*
 * Unit Test for revHash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {

  /////////////////////////////Normal cases///////////////////////// 
  char * src = "A"; 
  TEST( revHash(src) == revHashC(src) );
  src = "AB";
  TEST( revHash(src) == revHashC(src) );
  src = "ABC";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCD";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCDE";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCDEF";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCDEFG";
  TEST( revHash(src) == revHashC(src) );

  ////////////////////////////Abnormal cases: overflow/////////////
  src = "ABwewe1e12e12e21e12e12e";
  TEST( revHash(src) == revHashC(src) );
  src = "AB1safsffdfdgsregggsregegegC";
  TEST( revHash(src) == revHashC(src) );
  src = "ABwneifrigsirsnbginernginerignierngCD";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCwewqewe21e1e12eDE";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCDEeaeweqweaeqaeaqeaqeaF";
  TEST( revHash(src) == revHashC(src) );
  src = "ABCDEF@luijinienawrareaqqG";
  TEST( revHash(src) == revHashC(src) );


  //////////////////////////edge cases//////////////////////////
  src = "";
  TEST( revHash(src) == revHashC(src) );
  src = "-";
  TEST( revHash(src) == revHashC(src) );
  src = "@";
  TEST( revHash(src) == revHashC(src) );

}

int main() {
  fprintf( stderr, "Testing revHash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
