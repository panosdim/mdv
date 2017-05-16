/*
 * mdv - Colorful viewer of markdown files in terminal
 * Copyright (C) 2016  Panagiotis Dimopoulos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "display.h"
#include "fallback.h"

/* Always add at least this many bytes when extending the buffer. */
#define MIN_CHUNK 64

/**
 * Count the number of lines that a pad of cols columns can display.
 * @param fp    Pointer to file
 * @param cols  Number of columns in ncurses pad
 * @return Number of lines
 */
int
fcntlines(FILE *fp, int cols) {
    fseek(fp, 0, SEEK_SET);  /* Rewind file position */
    char line[cols];
    int nr_lines = 0;

    while (fgets(line, cols, fp) != NULL)
        nr_lines++;

    return nr_lines;
}

/**
 * Read file and store lines in array of strings.
 * @param fp    Pointer to file
 * @param lines Number of lines that stored in array of strings
 * @return The pointer to the array of strings
 */
char **
freadlines(FILE *fp, int *lines) {
    size_t n = 0;
    size_t array_size = MIN_CHUNK;
    ssize_t len = 0;
    int i = 0;
    int nl_avail = MIN_CHUNK;
    char *line = NULL;
    char **mkd = NULL;
    fseek(fp, 0, SEEK_SET);  /* Rewind file position */
    /* Allocate space to hold pointers to lines of markdown file */
    mkd = malloc(sizeof(char *) * array_size);

    if (mkd == NULL) {
        endwin();
        fprintf(stderr, "Can't allocate memory for storing lines of file\n");
        errno = ENOMEM;
        exit(EXIT_FAILURE);
    }

    /* Read file line by line in array */
    while ((len = getline(&line, &n, fp)) != -1) {
        if (nl_avail < 2) {
            array_size += MIN_CHUNK;
            mkd = realloc(mkd, sizeof(char *) * array_size);

            if (mkd == NULL) {
                endwin();
                fprintf(stderr, "Can't reallocate memory for storing lines of file\n");
                errno = ENOMEM;
                exit(EXIT_FAILURE);
            }

            nl_avail += MIN_CHUNK;
        }

        mkd[i] = malloc((size_t) len + 1);
        if (mkd[i] == NULL) {
            endwin();
            fprintf(stderr, "Can't allocate memory for storing lines of file\n");
            errno = ENOMEM;
            exit(EXIT_FAILURE);
        }
        memcpy(mkd[i], line, (size_t) len + 1);
        i++;
        nl_avail--;

        /* Free line */
        free(line);
        line = NULL;
        n = 0;
    }

    *lines = i;
    return mkd;
}
