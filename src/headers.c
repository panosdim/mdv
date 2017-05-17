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

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"
#include "headers.h"
#include "span.h"

static void
parse_atx_headers(char *header);

static void
parse_setext_headers(char *header, int level);


/**
 * Identify if line is a header of settext or atx style and parse it.
 * @param line A line of a markdown document.
 * @return true if line is header otherwise false.
 */
bool
parse_headers(char **mkd, int ln) {
    int i = 0;
    char *line = mkd[ln];

    if (line[0] == '#') {
        parse_atx_headers(line);
        return true;
    }

    /* Don't check for setext header in first line */
    if (ln != 0) {
        /* Check setext header */
        if (line[0] == '=') {
            while (line[i] == '=')
                i++;

            if (i == (strlen(line) - 1)) {
                parse_setext_headers(mkd[ln - 1], HEADER_SETEXT_1);
                return true;
            } else {
                return false;
            }
        }

        i = 0;
        if (line[0] == '-') {
            while (line[i] == '-')
                i++;

            if ((i == strlen(line) - 1) && mkd[ln - 1][0] != '\n') {
                parse_setext_headers(mkd[ln - 1], HEADER_SETEXT_2);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

/**
 * Parse atx style header lines
 * @param header The line with the header
 */
static void
parse_atx_headers(char *header) {
    int i = 0;
    int lvl = 0;
    size_t end;
    char *line = NULL;

    /* Find the level of header */
    while (header[i] == '#' && i < 6) {
        lvl++;
        i++;
    }

    /* Remove spaces from beginning of header */
    while (header[i] == ' ')
        i++;

    /* Remove trailing newline character */
    end = strlen(header) - 1;

    if (header[end] == '\n')
        end--;

    /* Remove trailing hashes if exists */
    if (header[end] == '#')
        while (header[--end] == '#');

    /* Print header */
    wattron (p, COLOR_PAIR(lvl));
    /* Allocate memory to copy header string for span elements processing */
    line = malloc((end - i + 2) * sizeof(char));

    if (line == NULL) {
        fprintf(stderr, "\ndynamic memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(line, header + i, end - i + 1);
    line[end - i + 1] = '\0';
    parse_span(line);
    free(line);
    waddch(p, '\n');
    wattroff (p, COLOR_PAIR(lvl));
}

/**
 * Parse setext style header lines
 * @param header The line with the header
 */
static void
parse_setext_headers(char *header, int level) {
    int y, x;

    /* Clear previous line and print it again with header style */
    getyx (p, y, x);
    x = 0;

    if (y > 0)
        wmove(p, y - 1, x);

    clrtoeol();

    if (level == HEADER_SETEXT_1) {
        wattron (p, COLOR_PAIR(HEADER_1));
        parse_span(header);
        wattroff (p, COLOR_PAIR(HEADER_1));
    } else if (level == HEADER_SETEXT_2) {
        wattron (p, COLOR_PAIR(HEADER_2));
        parse_span(header);
        wattroff (p, COLOR_PAIR(HEADER_2));
    }
}