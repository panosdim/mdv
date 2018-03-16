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
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "display.h"
#include "fallback.h"
#include "file.h"
#include "mdv.h"

// Always add at least this many bytes when extending the buffer.
#define MIN_CHUNK 64

/**
 * Read file and store lines in array of strings.
 * @param mdfile Name of file to open
 * @return A mkd struct
 */
mkd_s freadlines(char *mdfile)
{
    FILE *fp = fopen(mdfile, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s for reading\n", mdfile);
        exit(EXIT_FAILURE);
    }

    size_t n = 0;
    size_t array_size = MIN_CHUNK;
    ssize_t len = 0;
    int i = 0;
    int nl_avail = MIN_CHUNK;
    char *line = NULL;
    int nr_lines = 0;

    fseek(fp, 0, SEEK_SET); // Rewind file position
    // Allocate space to hold pointers to lines of file
    char **flp = malloc(sizeof(char *) * array_size);

    if (flp == NULL)
    {
        endwin();
        fprintf(stderr, "Can't allocate memory for storing lines of file\n");
        errno = ENOMEM;
        exit(EXIT_FAILURE);
    }

    // Read file line by line in array
    while ((len = getline(&line, &n, fp)) != -1)
    {
        if (len > COLS)
        {
            int nrl = ceil((double)len / (double)(COLS - 1));
            nr_lines += nrl;
        }
        else
        {
            nr_lines++;
        }
        if (nl_avail < 2)
        {
            array_size += MIN_CHUNK;
            char **tmp = realloc(flp, sizeof(char *) * array_size);

            if (tmp == NULL)
            {
                endwin();
                free(flp);
                fprintf(stderr, "Can't reallocate memory for storing lines of file\n");
                errno = ENOMEM;
                exit(EXIT_FAILURE);
            }
            else
            {
                flp = tmp;
            }

            nl_avail += MIN_CHUNK;
        }

        flp[i] = malloc((size_t)len + 1);
        if (flp[i] == NULL)
        {
            endwin();
            fprintf(stderr, "Can't allocate memory for storing a line of file\n");
            for (int j = i - 1; j >= 0; j--)
            {
                free(flp[j]);
            }
            free(flp);
            errno = ENOMEM;
            exit(EXIT_FAILURE);
        }
        memcpy(flp[i], line, (size_t)len + 1);
        i++;
        nl_avail--;

        // Free line
        free(line);
        line = NULL;
        n = 0;
    }

    // Close markdown file
    fclose(fp);

    mkd_s mkd = {.lines = flp, .len = i, .rows = nr_lines, .filename = mdfile};

    return mkd;
}
