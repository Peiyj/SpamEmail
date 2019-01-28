/*
 * Filename: testprependNode
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function prependNode().
 * Date: Nov 7th, 2018
 * Sources of Help: Tutor
 */

#include <string.h>
#include <stdlib.h>
#include "freeLinkedList.c"
#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*
 * Unit Test for prependNode
 *
 * void prependNode( linkedList_t** head,  char* str );
 *
 */

void testprependNode(){
    ////////////////////Empty cases///////////////////
    //case 1: 
    linkedList_t* head = malloc(sizeof(linkedList_t));
    prependNode(&head, "ab");
    TEST(head != NULL);
    TEST(strcmp(head -> value,"ab")==0);

    //case 2: 
    linkedList_t* head2 = malloc(sizeof(linkedList_t));
    prependNode(&head2, "abcdef");
    TEST(head2 != NULL);
    TEST(strcmp(head2 -> value,"abcdef")==0);

    //case 3: 
    linkedList_t* head3 = malloc(sizeof(linkedList_t));
    prependNode(&head3, "");
    TEST(head3 != NULL);
    TEST(strcmp(head3 -> value,"")==0);

    //case 4: 
    linkedList_t* head4 = malloc(sizeof(linkedList_t));
    prependNode(&head4, "123g&");
    TEST(head4 != NULL);
    TEST(strcmp(head4 -> value,"123g&")==0);
    
    //case 5: 
    linkedList_t* head5 = malloc(sizeof(linkedList_t));
    prependNode(&head5, "123sdf");
    TEST(head5 != NULL);
    TEST(strcmp(head5 -> value,"123sdf")==0);

    ////////////////////nonempty cases///////////////////
    //check head: 
    linkedList_t* headAll = malloc(sizeof(linkedList_t));
    prependNode(&headAll, "ab");
    TEST(headAll != NULL);
    TEST(strcmp(headAll -> value,"ab")==0);

    //check second: 
    prependNode(&headAll, "abcdef");
    TEST(headAll != NULL);
    TEST(headAll -> next != NULL);
    TEST(strcmp(headAll -> value,"abcdef")==0);
    TEST(strcmp(headAll -> next -> value,"ab")==0);

    //check third: 
    prependNode(&headAll, "");
    TEST(headAll != NULL);
    TEST(headAll -> next != NULL);
    TEST(headAll -> next -> next != NULL);
    TEST(strcmp(headAll -> value,"")==0);
    TEST(strcmp(headAll -> next -> value,"abcdef")==0);
    TEST(strcmp(headAll -> next -> next -> value, "ab") == 0);

    freeLinkedList(headAll);
    freeLinkedList(head);
    freeLinkedList(head2);
    freeLinkedList(head3);
    freeLinkedList(head4);
    freeLinkedList(head5);
}

int main() {
  fprintf( stderr, "Testing prependNode...\n\n" );
  testprependNode();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
