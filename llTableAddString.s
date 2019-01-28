/*
 * File: llTableAddString.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can uses the result of hash as the index into 
 * llTable
 * order
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

@ Raspberry Pi directives
        .cpu    cortex-a53              @ Version of our Pis
        .syntax unified                 @ Mordern syntax
@ Space constants
        .equ    FP_OFFSET, 4            @ Offset to set fp to base of saved reg
        
        .equ    LOCAL_VAR_SPACE, 24     @ Allocate 24 bytes of local vars
        .equ    INT_ARRAY_OFFSET, -8    @ store stringlength
        .equ    FUNC_PTR_OFFSET,-12     @ store function ptr
        .equ    MY_LOC_OFFSET, -16      @ this stores my local var
        .equ    HASH_OFFSET,-20         @ this stores hash var
        .equ    SIZE_OFFSET, -24        @ this stores size
        .equ    INDEX_OFFSET,-28        @ this stores remainder

        .equ    PARAM_SPACE, 8          @ Allocate 4 bytes to parameters
        .equ    TABLE_OFFSET, -32       @ 1st Formal param offset from fp
        .equ    STRING_OFFSET, -36      @ 2nd Formal param offset from fp

@ store numbers
        .global llTableAddString        @ Specify llTableAddString as a global
        .equ    FOUR, 4                 @ four: 4
        .equ    leftS,2                 @ lsl: 2
@ Text region   
        .text                           @ Switch to Text segment
        .align 2                        @ Align
/*
 * Function Header: llTableAddString()
 * Function Prototype: void llTableAddString(table_t *table, char* string)
 * Description: This function uses the result of hash as the index into the
 * llTable.
 * Parameters: table* : a pointer to the hash table
 *             string: a string pointer
 * Side Effects: none
 * Return values: void
 * Registers used:
 * r0 - arg 1 & intermiedary usage
 * r1 - arg 2 & intermiedary usage
 * r2 - hash
 * r3 - strlength
 */

llTableAddString:
        push    {fp,lr}                 @ push saved regs
        add     fp, sp, FP_OFFSET       @ set fp to the base
        
        sub     sp,sp,LOCAL_VAR_SPACE   @ allocate local space
        sub     sp,sp,PARAM_SPACE       @ allocate param space
        str     r0, [fp, TABLE_OFFSET]  @ store the table offset 
        str     r1, [fp, STRING_OFFSET] @ store the string offset
        ///////////int hash = table->hashFunction(string)////////
        ldr     r0, [fp, TABLE_OFFSET]  @ get the table offset
        ldr     r1, =HashFunctionOffset @ get the hash function offset
        ldr     r1, [r1]                @ get the content
        ldr     r0, [r0, r1]            @ get the function offset
        str     r0, [fp, FUNC_PTR_OFFSET]
                                        @ store it to local var

        ldr     r0, [fp, STRING_OFFSET] @ load the string offset
        ldr     r1, [fp, FUNC_PTR_OFFSET]  
                                        @ load the function pointer
        blx     r1                      @ get the key

        str     r0, [fp, HASH_OFFSET]   @ store it to hash offset

        //int index = ((hash %table->size)+table->size)%table->size//

        //get table-> size
        ldr     r0, [fp, TABLE_OFFSET]  @ get the table offset
        ldr     r1, =SizeOffset         @ get the size offset
        ldr     r1, [r1]                @ get the actually size

        ldr     r0, [r0, r1]            @ get table -> size
        str     r0, [fp, SIZE_OFFSET]   @ get the size offset
        //hash % table -> size
        ldr     r0, [fp, HASH_OFFSET]   @ get hash offset
        ldr     r1, [fp, SIZE_OFFSET]   @ get size offset
        bl      getRemainder            @ call get remainder
        str     r0, [fp, INDEX_OFFSET]  @ store remainer

        ldr     r0, [fp, INDEX_OFFSET]  @ get remainder
        ldr     r1, [fp, SIZE_OFFSET]   @ get size
        add     r0, r0,r1               @ store this temp number

        //temp % table->size
        ldr     r1, [fp, SIZE_OFFSET]   @ get size
        bl      getRemainder            @ call getremainder

        str     r0, [fp, INDEX_OFFSET]  @ store this to index offset

        /////prependNode(&(table->llArray[index]), string)/////
        //get table -> llArray[index]
        ldr     r0, [fp, TABLE_OFFSET]  @ load table offset
        ldr     r1, =ArrayOffset        @ get array offset 
        ldr     r1, [r1]                @ get the content of the array
        ldr     r1, [r0, r1]            @ load table -> llArray

        ldr     r2, [fp, INDEX_OFFSET]  @ get the index offset
        lsl     r2, r2,leftS            @ convert index from pointer to bytes
        add     r0,r1,r2                @ r0: table -> llArray[index]

        str     r0, [fp, MY_LOC_OFFSET] @ r0: my local offset

        ldr     r1, [fp, STRING_OFFSET] @ get string offset
        ldr     r0, [fp, MY_LOC_OFFSET] @ get the address of my_loc_offset

        bl      prependNode             @ call prependNode
        

        //standard exit
        sub     sp,fp,FP_OFFSET         @ deallocate vars
        pop     {fp,pc}                 @ pop registers




