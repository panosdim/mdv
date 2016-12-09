/*
 * mdp - Colorful viewer of markdown files in terminal
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

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"

static void parse_atx_headers (char *header);
static void parse_emphasis (char *line);
static void parse_marks (char *line);
static void parse_list (char *list);
static int identify_headers (char *line);

enum {
    NO_HEADER = 1,
    HEADER_ATX = 2,
    HEADER_SETEXT_1 = 3,
    HEADER_SETEXT_2 = 4
};

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  markdown
 *  Description:  Parse and render a markdown file stored as array of lines.
 * =====================================================================================
 */
void
markdown (char **mkd, int lines) {
    char *pch;
    int is_header;
    int is_list;
    int y, x;

    /* Check for markers in lines */
    for (int i = 0; i < lines; i++) {
        /* Check for header markups */
        is_header = identify_headers (mkd[i]);

        if (is_header == HEADER_ATX)
            parse_atx_headers (mkd[i]);
        else if (is_header == HEADER_SETEXT_1) {
            /* Clear previous line and print it again with header style */
            getyx (p, y, x);

            if (y > 0)
                wmove (p, y - 1, 0);

            clrtoeol();
            wattron (p, COLOR_PAIR (HEADER_1));
            waddstr (p, mkd[i - 1]);
            wattroff (p, COLOR_PAIR (HEADER_1));
        } else if (is_header == HEADER_SETEXT_2) {
            /* Clear previous line and print it again with header style */
            getyx (p, y, x);

            if (y > 0)
                wmove (p, y - 1, 0);

            clrtoeol();
            wattron (p, COLOR_PAIR (HEADER_2));
            waddstr (p, mkd[i - 1]);
            wattroff (p, COLOR_PAIR (HEADER_2));
        } else
            /* Check for inline markups */
            parse_marks (mkd[i]);
    }
}   /* -----  end of function markdown  ----- */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_atx_headers
 *  Description:  Parse atx style header lines.
 * =====================================================================================
 */
static void
parse_atx_headers (char *header) {
    int thash = 1;
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
    end = strlen (header) - 1;

    if (header[end] == '\n')
        end--;

    /* Remove trailing hashes if exists */
    if (header[end] == '#')
        while (header[--end] == '#');

    /* Print header */
    wattron (p, COLOR_PAIR (lvl));
    /* Allocate memory to copy header string for marks processing */
    line = malloc ((end - i + 2) * sizeof (char));

    if (line == NULL) {
        fprintf (stderr, "\ndynamic memory allocation failed\n");
        exit (EXIT_FAILURE);
    }

    memcpy (line, header + i, end - i + 1);
    line[end - i + 1] = '\0';
    parse_marks (line);
    free (line);
    line  = NULL;
    waddch (p, '\n');
    wattroff (p, COLOR_PAIR (lvl));
}   /* -----  end of function parse_atx_headers  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_marks
 *  Description:  Parse line for emphasis, inline code, escapable characters
 *                and links.
 * =====================================================================================
 */
static void
parse_marks (char *line) {
    char *emp;

    /* Check for emphasis characters in line */
    if ((emp = strchr (line, '*')) != NULL || (emp = strchr (line, '_')) != NULL) {
        /* Check for emphasis characters at the beginning of line */
        if (emp == line) {
            /* Check for space after emphasis characters */
            if (emp[1] == ' ') {
                /* Parse rest of line */
                wprintw (p, "%.*s", 1, emp);
                parse_marks (emp + 1);
                return;
            }
        }

        /* Check if we have an escape char before or surrounded space */
        if (emp[-1] != '\\' || emp[-1] == ' ') {
            wprintw (p, "%.*s", emp - line, line);
            char *emp_end;

            if (emp[1] == '*' || emp[1] == '_') {
                wattron (p, A_BOLD);
                (emp_end = strchr (emp + 2, '*')) || (emp_end = strchr (emp + 2, '_'));
                wprintw (p, "%.*s", emp_end - (emp + 2), emp + 2);
                wattroff (p, A_BOLD);
                /* Parse rest of line */
                parse_marks (emp_end + 2);
                return;
            } else {
                wattron (p, A_UNDERLINE);
                (emp_end = strchr (emp + 1, '*')) || (emp_end = strchr (emp + 1, '_'));
                wprintw (p, "%.*s", emp_end - (emp + 1), emp + 1);
                wattroff (p, A_UNDERLINE);
                /* Parse rest of line */
                parse_marks (emp_end + 1);
                return;
            }
        } else {
            /* Print until '*' or '_' char, remove backslash and parse rest of line */
            wprintw (p, "%.*s", emp - line - 1, line);
            wprintw (p, "%.*s", 1, emp);
            parse_marks (emp + 1);
            return;
        }
    } else
        waddstr (p, line);
}   /* -----  end of static function parse_marks  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_list
 *  Description:  Parse list lines.
 * =====================================================================================
 */
static void
parse_list (char *list) {
    int i = 2;

    /* Remove whitespace */
    while (list[i] == ' ')
        i++;

    /* Print list item */
    waddch (p, '*' | COLOR_PAIR (LIST));
    waddch (p, ' ');
    wprintw (p, "%s", list + i);
}   /* -----  end of static function parse_list  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  identify_headers
 *  Description:  Identify if line is a header of settext or atx style.
 * =====================================================================================
 */
static int
identify_headers (char *line) {
    int i = 0;

    if (line[0] == '#')
        return HEADER_ATX;

    if (line[0] == '=') {
        while (line[i] == '=')
            i++;

        if (i == (strlen (line) - 1))
            return HEADER_SETEXT_1;
    }

    i = 0;

    if (line[0] == '-') {
        while (line[i] == '-')
            i++;

        if ((i == strlen (line) - 1))
            return HEADER_SETEXT_2;
    }

    return NO_HEADER;
}   /* -----  end of static function identify_headers  ----- */