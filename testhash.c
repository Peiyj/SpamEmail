/*
 * Filename: testhash
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function hash().
 * Date: Nov 7th, 2018
 * Sources of Help: Tutor
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

static int hashC(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for( int i = 0; i < strLen; i++ ) {
         hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}

/*
 * Unit Test for hash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {
  /////////////////////////////Normal cases///////////////////////// 
  char * src = "A"; 
  TEST( hash(src) == hashC(src) );
  src = "AB";
  TEST( hash(src) == hashC(src) );
  src = "ABC";
  TEST( hash(src) == hashC(src) );
  src = "ABCD";
  TEST( hash(src) == hashC(src) );
  src = "ABCDE";
  TEST( hash(src) == hashC(src) );
  src = "ABCDEF";
  TEST( hash(src) == hashC(src) );
  src = "ABCDEFG";
  TEST( hash(src) == hashC(src) );

  ////////////////////////////Abnormal cases: overflow/////////////
  src = "ABwewe1e12e12e21e12e12e";
  TEST( hash(src) == hashC(src) );
  src = "AB1safsffdfdgsregggsregegegC";
  TEST( hash(src) == hashC(src) );
  src = "ABwneifrigsirsnbginernginerignierngCD";
  TEST( hash(src) == hashC(src) );
  src = "ABCwewqewe21e1e12eDE";
  TEST( hash(src) == hashC(src) );
  src = "ABCDEeaeweqweaeqaeaqeaqeaF";
  TEST( hash(src) == hashC(src) );
  src = "ABCDEF@luijinienawrareaqqG";
  TEST( hash(src) == hashC(src) );


  //////////////////////////edge cases//////////////////////////
  src = "";
  TEST( hash(src) == hashC(src) );
  src = "-";
  TEST( hash(src) == hashC(src) );
  src = "@";
  TEST( hash(src) == hashC(src) );

}

int main() {
  fprintf( stderr, "Testing hash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
