//
// Created by padi on 12/7/16.
//

/*
 * =====================================================================================
 *
 *       Filename:  file.c
 *
 *    Description:  Helper functions to work with text files.
 *
 *        Version:  1.0
 *        Created:  24/11/2016 11:30:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Panagiotis Dimopoulos, panosdim@gmail.com
 *        License:  GNU General Public License
 *
 * =====================================================================================
 */

/* #####   HEADER FILE INCLUDES   ################################################### */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "getline.h"

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
/* Always add at least this many bytes when extending the buffer.  */
#define MIN_CHUNK 64

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cnt_col_lines
 *  Description:  Count the number of lines that a pad of cols columns can
 *                display.
 * =====================================================================================
 */
unsigned long
cnt_col_lines(FILE *fp, int cols) {
    fseek(fp, 0, SEEK_SET);  /* Rewind file position */
    char line[cols];
    unsigned long nr_lines = 0;

    while (fgets(line, cols, fp) != NULL)
        nr_lines++;

    return nr_lines;
}       /* -----  end of function cnt_col_lines  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  read_lines
 *  Description:  Read file and store lines in array.
 * =====================================================================================
 */
char **
read_lines(FILE *fp, int *lines) {
    size_t len = 0;
    size_t asize = MIN_CHUNK;
    int i = 0;
    int nl_avail = MIN_CHUNK;
    char *line = NULL;
    char **mkd = NULL;
    fseek(fp, 0, SEEK_SET);                      /* Rewind file position */
    /* Allocate space to hold pointers to lines of markdown file */
    mkd = malloc(sizeof(char *) * asize);

    if (mkd == NULL) {
        fprintf(stderr, "Can't allocate memory for storing lines of file\n");
        errno = ENOMEM;
        exit(EXIT_FAILURE);
    }

    while (fgetline(&line, &len, fp) != -1) {
        if (nl_avail < 2) {
            asize += MIN_CHUNK;
            mkd = realloc(mkd, sizeof(char *) * asize);

            if (mkd == NULL) {
                fprintf(stderr, "Can't allocate memory for storing lines of file\n");
                errno = ENOMEM;
                exit(EXIT_FAILURE);
            }

            nl_avail += MIN_CHUNK;
        }

        mkd[i] = malloc(len + 1);

        if (mkd[i] == NULL) {
            fprintf(stderr, "Can't allocate memory for storing lines of file\n");
            errno = ENOMEM;
            exit(EXIT_FAILURE);
        }

        memcpy(mkd[i], line, len);
        mkd[i][len + 1] = '\0';
        i++;
        nl_avail--;
    }
    /* Free line */
    free(line);
    line = NULL;
    len = 0;

    *lines = i;
    return mkd;
}   /* -----  end of function read_lines  ----- */
