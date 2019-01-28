/*
 * Filename: freeLinkedList.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function frees all elements in the input linked list. 
 * Date: Nov 8th. 2018
 * Sources of help: tutor
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa3.h"

/*
 * Function header: freeLinkedList()
 * Function prototype: void freeLinkedList( linkedList_t * head )
 * Description: This function frees all elements in the input linked list. To
 * free a linked list, iterate through the list starting from the head, first
 * free the value of the node, then the node itself, until we reach the end of
 * the list.
 * Parameters: head: a pointer to the head
 * Side effect: memory deallocation
 * Return values: void
 */

void freeLinkedList(linkedList_t * head ){
    linkedList_t *current = head;
    //if head is null, break the loop
    while(current){
        linkedList_t *next = current -> next;
        free(current ->value);
        free(current);  
        current = next;
    }
}
