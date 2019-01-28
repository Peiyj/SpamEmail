/*
 * File: revHash.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can create the hask key of a string in reverse
 * order
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

@ Raspberry Pi directives
        .cpu    cortex-a53              @ Version of our Pis
        .syntax unified                 @ Mordern syntax
@ Space constants
        .equ    FP_OFFSET, 4            @ Offset to set fp to base of saved reg
        
        .equ    LOCAL_VAR_SPACE, 16     @ Allocate 16 bytes of local vars
        .equ    StrLen_OFFSET, -8       @ store stringlength
        .equ    hashP_OFFSET, -12       @ store hashPrime
        .equ    startV_OFFSET,-16       @ store hash start val
        .equ    temp_OFFSET, -20        @ this stores temp hash value

        .equ    PARAM_SPACE, 8          @ Allocate 4 bytes to parameters
        .equ    StrPtr_OFFSET, -24      @ 1st Formal param offset from fp
@ Local space constants

@ store numbers
        .global revHash                    @ Specify hash as a global symbol
@ Text region   
        .text                           @ Switch to Text segment
        .align 2                        @ Align
/*
 * Function Header: revHash()
 * Function Prototype: int revHash(char *str);
 * Description: This function creates an integer hash key from str with the 
 *              hashing algorithm. 
 * Parameters: str* = a pointer to a string
 * Side Effects: increment i++
 * Return values: int hash key: the key value of the hash
 * Registers used:
 * r0 - arg 1 & intermiedary usage  
 * r1 - index i
 * r2 - hash
 * r3 - strlength
 */

revHash:
        push    {fp, lr}                @ push saved regs
        add     fp, sp, FP_OFFSET       @ set fp to the base
        
        sub     sp,sp, LOCAL_VAR_SPACE  @ allocate local space
        sub     sp,sp, PARAM_SPACE      @ allocate param space
        str     r0, [fp, StrPtr_OFFSET] @ store this to strptr param offset

        ////////////////int hash = hashStartVal/////////
        ldr     r0, =HashStartVal       @ store the address of hashStartVal
        ldr     r0, [r0]                @ store the content of hashstartval
        str     r0, [fp, startV_OFFSET] @ store startvalue 
        ldr     r2, [fp, startV_OFFSET] @ load startvalue
        str     r2, [fp, temp_OFFSET]   @ store to temp hash value

        ////////////////int strLen = strlen(str)/////////
        ldr     r0, [fp, StrPtr_OFFSET] @ get string pointer
        bl      strlen                  @ call string length
        str     r0, [fp, StrLen_OFFSET] @ store string length
        ldr     r3, [fp, StrLen_OFFSET] @ load string length

        ///////////////////negative logic to skip the loop///////////
        mov     r1, r3                  @ i = strlen
        sub     r1, r1, 1               @ i = strlen - 1
        mov     r3, 0                   @ r3: 0
        cmp     r1, r3                  @ compare i to strlength
        blt     end                     @ branch if i < 0
loop:
        ////////////////////for loop///////////////////
        ////////////////////body of for loop////////////
        ldr     r0, =HashPrime          @ load address of hashprime
        ldr     r0, [r0]                @ get the content of hashprime
        str     r0, [fp, hashP_OFFSET]  @ store it to hash prime offset
        ldr     r0, [fp, hashP_OFFSET]  @ r0: hashPrime offset
        ldr     r2, [fp, temp_OFFSET]   @ get temp offset
        mul     r2,r2,r0                @ hash = hash * hashprime
        str     r2, [fp, temp_OFFSET]   @ store hash to temp hash value 

        ldr     r0, [fp, StrPtr_OFFSET] @ get string pointer
        add     r0,r0,r1                @ get pointer to str[i]
        ldrb    r0, [r0]                @ load the content of str[i]

        ldr     r2, [fp, temp_OFFSET]   @ get temp hash value
        add     r2,r2,r0                @ hash = hash + str[i]
        str     r2, [fp, temp_OFFSET]   @ store it back to temp hash value
        sub     r1,r1,1                 @ i--
        mov     r3, 0                   @ r3:0
        cmp     r1, r3                  @ positive logic to loop back
        bge     loop
end:
        ldr     r2, [fp, temp_OFFSET]   @ get the hash value
        mov     r0, r2                  @ move hash key to r0
        
        sub     sp,fp,FP_OFFSET         @ deallocate vars
        pop     {fp,pc}                 @ pop returns address lr into pc





