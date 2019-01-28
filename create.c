/*
 * File: create.c
 *
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This is the main driver for the create portion of your 
 * program. Its main tasks are to parse the command line arguments, 
 * build the hashtables of email data, and serialize the hashtables 
 * to a file.
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <errno.h>
#include <unistd.h>

#define SHORT_HELP_FLAG "h"
#define SHORT_SIZE_FLAG "s"
#define SHORT_INFILE_FLAG "i"
#define SHORT_OUTPUT_FLAG "o"

#define TWO 2
#define SIZE_1 0x1
#define INPUT_2 0x2
#define OUTPUT_4 0x4
#define VALID_1 0x6
#define VALID_2 0x7

#define bits 7
#define ceiling 8

/*
///////////prepare the array of option structs for getopt_long////////
struct option {
const char* name,//the long name of the flag
int has_arg,//indicates if the flag requires an arg after it
int *flag,//enables advanced parsing
int val,//the short version of the flag 
};*/

static struct option getopt_longOpts[] = {
    {
        LONG_HELP_FLAG, no_argument, 0, HELP_FLAG
    },
    {
        LONG_SIZE_FLAG, required_argument, 0, SIZE_FLAG
    },
    {
        LONG_INFILE_FLAG, required_argument, 0, INFILE_FLAG
    },
    {
        LONG_OUTPUT_FLAG, required_argument, 0, OUTPUT_FLAG
    },

    {
        SHORT_HELP_FLAG, no_argument, 0, HELP_FLAG
    },
    {
        SHORT_SIZE_FLAG, required_argument, 0, SIZE_FLAG
    },
    {
        SHORT_INFILE_FLAG, required_argument, 0, INFILE_FLAG
    },
    {
        SHORT_OUTPUT_FLAG, required_argument, 0, OUTPUT_FLAG
    },
    {
        NULL, 0, NULL, 0
    },
};

////////////////////////////hash//////////////////////////
/*
 * Function Header: hashC()
 * Function Prototype: int hashC( char * str); 
 * Description: Its main tasks are to give the address of hash
 * Parameters: str: a string 
 * Side Effects: none
 * Return values: int hashkey
 */

static int hashC(char * str){
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for(int i = 0; i < strLen; i++){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}
/*
 * Function Header: revHashc()
 * Function Prototype: int revHashC( char * str); 
 * Description: Its main tasks are to give the address of hash
 * Parameters: str: a string 
 * Side Effects: none
 * Return values: int hashkey
 */

static int revHashC(char * str){
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for(int i = strLen - 1; i >= 0; i--){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}
/*
 * Function Header: evenOddHashC()
 * Function Prototype: int evenOddHashC( char * str); 
 * Description: Its main tasks are to give the address of hash
 * Parameters: str: a string 
 * Side Effects: none
 * Return values: int hashkey
 */

static int evenOddHashC(char * str){
    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for(int i = 0; i < strLen; i+= TWO){
        hash = hash * HASH_PRIME + str[i];
    }
    for(int i = 1; i < strLen; i+= TWO){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}
////////////////////////////main//////////////////////////
/*
 * Function Header: main()
 * Function Prototype: int main( int argc, char * argv[] ); 
 * Description: Its main tasks are to parse the command line arguments,
 * build the hashtables of email data, and serialize the hashtables to 
 * a file.
 * Parameters: argc: number of arguments
 *             argv[]: the array form of the arguments
 * Side Effects: none
 * Return values: void
 */

int main( int argc, char * argv[] ){
    //declare necessary variables
    int opt;
    int mysize = DEFAULT_SIZE;
    char* endptr;
    errno = 0;
    int bitmap = 0;
    FILE *myinput;
    FILE *myoutput;

    //parse command line arguments
    // int getopt_long(int argc, char *const * argv, const char *shortopts,
    // const struct option *longopts, int *indexptr

    ///////////////if there are no arguments//////////
    if(argc == 1){
        fprintf(stderr, ARG_ERR);
        fprintf(stderr, SHORT_CREATE_USAGE);
        return EXIT_FAILURE;
    }

    ///////////////if there are more arguments/////////
    while ((opt = getopt_long(argc, argv, CREATE_FLAGS, 
                    getopt_longOpts, 0))!= -1){
        switch (opt) {
            case HELP_FLAG:
                fprintf(stdout, LONG_CREATE_USAGE);
                return EXIT_SUCCESS;
            case SIZE_FLAG:
                ///////do some error checking/////
                errno = 0;
                //convert the table size to string
                mysize = strtol(optarg, &endptr, MIN_SIZE);
                //if parsing the number succeeds
                if(*endptr == '\0' && errno == 0){
                    //error case 1: if the number not in range
                    if(mysize > MAX_SIZE || mysize < MIN_SIZE){
                        fprintf(stderr,TABLE_SIZE_ERR,MIN_SIZE,MAX_SIZE); 
                        fprintf(stderr, SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                }
                //error case 2: error converting to long: overflow
                if(errno != 0){
                    char buffArray[BUFSIZ];
                    //error case 3: overflow size contains non-numeric 
                    if(*endptr != '\0'){
                        snprintf(buffArray, BUFSIZ, INVALID_NUM, optarg);
                        perror(buffArray);
                        fprintf(stderr, SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                    else{
                        snprintf(buffArray, BUFSIZ, TOO_LARGE_NUM, optarg, 0);
                        perror(buffArray);
                        fprintf(stderr, SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                }
                //error case 4: size contains non-numeric characters
                if(*endptr != '\0'){
                    fprintf(stderr, INVALID_NUM, optarg);
                    fprintf(stderr, SHORT_CREATE_USAGE);
                    return EXIT_FAILURE;
                }
                bitmap |= SIZE_1;
                break;
            case INFILE_FLAG:
                errno = 0;
                myinput = fopen(optarg, "rb");
                ///files do not exit/
                if(errno != 0){
                    perror(FILTER_ERR);
                    fprintf(stderr, SHORT_CREATE_USAGE);
                    return EXIT_FAILURE;
                } 
                bitmap |= INPUT_2;
                break;
            case OUTPUT_FLAG:
                errno = 0;
                myoutput = fopen(optarg, "wb");
                ///files do not exit//
                if(errno != 0){
                    perror(WTABLE_FILE_ERR);
                    fprintf(stderr, SHORT_CREATE_USAGE);
                    return EXIT_FAILURE;
                } 
                bitmap |= OUTPUT_4;
                break;
            default:
                fprintf(stderr, SHORT_CREATE_USAGE);
                return EXIT_FAILURE;
        }
    }

    //check if either of input and output is missing  
    if(bitmap != VALID_1 && bitmap != VALID_2 ){
        fprintf(stderr, ARG_ERR);
        fprintf(stderr, SHORT_CREATE_USAGE);
        return EXIT_FAILURE;
    }

    //extra arguments error//
    if(optind != argc){
        fprintf(stderr, EXTRA_ARGS,argv[0]);
        fprintf(stderr, SHORT_CREATE_USAGE);
        return EXIT_FAILURE;
    }

    //if all flags are parsed without error
    //Build the hashtables and write to file
    table_t htbl = {
        .hashFunction = &hashC,
        .size = mysize,
        .bitArray = calloc(1,(mysize + bits) /ceiling) //ceiling of size 8
    };
    if(htbl.bitArray == NULL){
        perror(MEM_ERR);
        return EXIT_FAILURE;
    }
    table_t rtbl = {
        .hashFunction = &revHashC,
        .size = mysize,
        .bitArray = calloc(1,(mysize + bits) /ceiling) //ceiling of size 8

    };
    if(rtbl.bitArray == NULL){
        free(htbl.bitArray);
        perror(MEM_ERR);
        return EXIT_FAILURE;
    }
    table_t eotbl = {
        .hashFunction = &evenOddHashC,
        .size = mysize,
        .llArray = malloc(eotbl.size * sizeof(linkedList_t))
    };
    if(eotbl.llArray == NULL){
        free(htbl.bitArray);
        free(rtbl.bitArray);
        perror(MEM_ERR);
        return EXIT_FAILURE;
    }
    //Next call populateTables()
    populateTables(&htbl, &rtbl, &eotbl, myinput);
    //call writeTables() to write to the file
    writeTables(myoutput, &htbl, &rtbl, &eotbl);
    free(htbl.bitArray);
    free(rtbl.bitArray);
    for(int i = 0; i < eotbl.size; i++){
        freeLinkedList(eotbl.llArray[i]);
    }
    free(eotbl.llArray);
    fclose(myinput);
    fclose(myoutput);
    return EXIT_SUCCESS;
}
