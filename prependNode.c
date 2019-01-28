/*
 * File: prependNode.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can prepend a 
 * order
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

/*
 * Function Header: prependNode()
 * Function Prototype: void prependNode(linkedList_t ** head, char* str);
 * Description: This function takes in a pointer to the head of a linked 
 * list (i.e. a pointer to a pointer to a linkedList_t) and a string to
 * insert and then pushes the element onto the front of the linked list. 
 * Parameters: head: a new node head
 *             str: the string 
 * Side Effects: dymanic memory allocation
 * Return values: void
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa3.h"

void prependNode(linkedList_t** head, char* str){
    //////////////////allocate newNode/////////////////
    linkedList_t* newNode = (struct llist*)malloc(sizeof(linkedList_t) + 1);
    ////////////////if malloc fails////////////////////
    if(newNode == NULL){
        perror(MEM_ERR);
        return;
    }
    /////////allocate memory for the string////////
    char* newString = (char*)malloc(strlen(str) + 1);
    ////////////////if malloc fails/////////////////////
    if(newString == NULL){
        free(newNode);
        perror(MEM_ERR);
        return;
    }
    strncpy(newString, str, strlen(str));
    newNode->value = newString;
    ////////////////////case 1: empty linkedlist/////////
    if(*head == NULL){
        *head = newNode;
    }
    ///////////////////case 2: non empty linkedlist//////
    else{
        newNode -> next = *head;
        *head = newNode; 
    }
}
