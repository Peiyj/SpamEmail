/*
 * File: searchEC.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function performs the functionality for the search
 * program. It starts by parsing the command line arguments, handling 
 * any errors encountered in the process 
 * Date: Nov 7, 2018
 * Source of Help: Tutor
 */
/*
///////////prepare the array of option structs for getopt_long////////
struct option {
const char* name,//the long name of the flag
int has_arg,//indicates if the flag requires an arg after it
int *flag,//enables advanced parsing
int val,//the short version of the flag 
};*/
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
 *
 * Function Header: main()
 * Function Prototype: int main( int argc, char * argv[] ); 
 * Description: This function performs the functionality for the search 
 * program. It starts by parsing the command line arguments, handling 
 * any errors encountered in the process
 * Parameters: argc: number of arguments
 *             argv[]: the array form of the arguments
 * Side Effects: none
 * Return values: void
 */

int main( int argc, char * argv[] ){
    //declare necessary variables
    int opt;
    errno = 0;
    FILE *myinput;
    int bitmap = 0;

    //parse command line arguments
    // int getopt_long(int argc, char *const * argv, const char *shortopts,
    // const struct option *longopts, int *indexptr

    ///////////////if there are no arguments//////////
    if(argc == 1){
        fprintf(stderr, MISSING_INFILE);
        fprintf(stderr, SHORT_SEARCH_USAGE);
        return EXIT_FAILURE;
    }
    ///////////////if there are more arguments/////////
    while ((opt = getopt(argc, argv, SEARCH_FLAGS))!= -1){
        switch (opt) {
            case HELP_FLAG:
                fprintf(stdout, LONG_SEARCH_USAGE);
                return EXIT_SUCCESS;
            case INFILE_FLAG:
                errno = 0;
                myinput = fopen(optarg, "rb");
                ///files do not exit/
                if(errno != 0){
                    perror(RTABLE_FILE_ERR);
                    fprintf(stderr, SHORT_SEARCH_USAGE);
                    return EXIT_FAILURE;
                }
                bitmap = 1;
                break;
            default:
                fprintf(stderr, SHORT_SEARCH_USAGE);
                return EXIT_FAILURE;
        }
    }
    //if there is no input file
    if(bitmap != 1){
        fprintf(stderr, MISSING_INFILE);
        fprintf(stderr, SHORT_SEARCH_USAGE);
        return EXIT_FAILURE;
    }

    //extra arguments error//

    if(optind != argc){
        fprintf(stderr, EXTRA_ARGS,argv[0]);
        fprintf(stderr, SHORT_SEARCH_USAGE);
        fclose(myinput);
        return EXIT_FAILURE;
    }

    table_t htbl;
    table_t rtbl;
    table_t eotbl;
    //Next call readTables()
    readTables(myinput, &htbl, &rtbl, &eotbl);
    //call launchUserQuery() to search
    launchUserQueryEC(&htbl, &rtbl, &eotbl);
    free(htbl.bitArray);
    free(rtbl.bitArray);
    for(int i = 0; i < eotbl.size; i++){
        freeLinkedList(eotbl.llArray[i]);
    }
    free(eotbl.llArray);
    fclose(myinput);
    return EXIT_SUCCESS;
}
