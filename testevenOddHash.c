/*
 * Filename: testevenOddHash
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function evenOddHash().
 * Date: Nov 7th, 2018
 * Sources of Help: Tutor
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*
 * Unit Test for evenOddHash()
 *
 * long evenOddHash( char * src );
 *
 */
void testevenOddHash() {
  /////////////////////////////Normal cases///////////////////////// 
  char * src = "A"; 
  TEST(evenOddHash(src) == 472);

  src = "AB";
  TEST(evenOddHash(src) == 17530);

  src = "ABC";
  TEST(evenOddHash(src) == 648713);

  src = "ABCD";
  TEST(evenOddHash(src) == 24002449);

  src = "ABCDE";
  TEST(evenOddHash(src) == 888094714);


  //////////////////////////edge cases//////////////////////////
  src = "";
  TEST( evenOddHash(src) == 11 );

  src = "-";
  TEST( evenOddHash(src) == 452 );

  src = "+";
  TEST( evenOddHash(src) == 450 );

  src = "0";
  TEST( evenOddHash(src) == 455 );

  src = "~";
  TEST( evenOddHash(src) == 533 );


}

int main() {
  fprintf( stderr, "Testing evenOddHash...\n\n" );
  testevenOddHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
