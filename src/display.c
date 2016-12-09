//
// Created by padi on 12/7/16.
//

/*
 * =====================================================================================
 *
 *       Filename:  display.c
 *
 *    Description:  Use ncurses to display the rendered markdown file in terminal.
 *
 *        Version:  1.0
 *        Created:  24/11/2016 12:59:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Panagiotis Dimopoulos, panosdim@gmail.com
 *        License:  GNU General Public License
 *
 * =====================================================================================
 */

/* #####   HEADER FILE INCLUDES   ################################################### */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "file.h"
#include "parser.h"

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ################################ */
WINDOW *p;
char **mkd;
static int ROWS, lines;

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  initialize
 *  Description:  Read markdown file to buffer and initialize ncurses
 * =====================================================================================
 */
void
initialize (char *mdfile) {
    int ret;
    /* Open markdown file for read only */
    FILE *fp = fopen (mdfile, "r");

    if (fp == NULL) {
        fprintf (stderr, "Can't open file %s for reading\n", mdfile);
        exit (EXIT_FAILURE);
    }

    /* initialize ncurses */
    initscr();
    noecho();
    cbreak();
    keypad (stdscr, TRUE);

    /* Check if terminal support colours */
    if (has_colors() == FALSE) {
        endwin();
        fprintf (stderr, "Your terminal does not support color\n");
        exit (EXIT_FAILURE);
    }

    /* Initialize color pairs */
    start_color();
    init_pair (HEADER_1, COLOR_RED, COLOR_BLACK);
    init_pair (HEADER_2, COLOR_GREEN, COLOR_BLACK);
    init_pair (HEADER_3, COLOR_YELLOW, COLOR_BLACK);
    init_pair (HEADER_4, COLOR_BLUE, COLOR_BLACK);
    init_pair (HEADER_5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair (HEADER_6, COLOR_CYAN, COLOR_BLACK);
    init_pair (LIST, COLOR_GREEN, COLOR_BLACK);
    /* Find how much rows we need for the pad */
    ROWS = cnt_col_lines (fp, COLS);
    /* Read file in array of string lines */
    mkd = read_lines (fp, &lines);
    /* close markdown file */
    fclose (fp);
    /* create a new pad */
    p = newpad (ROWS, COLS);

    if (p == NULL) {
        endwin();
        printf ("Unable to create new pad\n");
        exit (EXIT_FAILURE);
    }

    keypad (p, TRUE);
}       /* -----  end of function initialize  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  display
 *  Description:  Process and display markdown file
 * =====================================================================================
 */
void
display() {
    wclear (p);
    markdown (mkd, lines);
}       /* -----  end of function display  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  handle_input
 *  Description:  Wait for use input after display markdown
 * =====================================================================================
 */
void
handle_input() {
    int ch;
    int x = 0;
    int y = 0;
    int padpos = 0;
    int raw_display_flag = false;
    prefresh (p, padpos, 0, 0, 0, LINES - 1, COLS - 1);

    while ((ch = wgetch (p)) != 'q') {
        switch (ch) {
            case KEY_HOME:
                x = 0;
                break;

            case KEY_END:
                x = COLS - 1;
                break;

            case KEY_LEFT:
                if (x > 0)
                    x--;

                break;

            case KEY_RIGHT:
                if (x < COLS - 1)
                    x++;

                break;

            case KEY_UP:
                if (y == 0 && padpos == 0)
                    break;
                else if (y == padpos) {
                    y--;
                    padpos--;
                    prefresh (p, padpos, 0, 0, 0, LINES - 1, COLS - 1);
                } else
                    y--;

                break;

            case KEY_DOWN:
                if (y == ROWS - 1)
                    break;
                else if (y == padpos + LINES - 1) {
                    y++;
                    padpos++;
                    prefresh (p, padpos, 0, 0, 0, LINES - 1, COLS - 1);
                } else
                    y++;

                break;

            case 'r':
                if (raw_display_flag) {
                    raw_display_flag = false;
                    display();
                } else {
                    raw_display_flag = true;
                    raw_data();
                }

                break;
        }

        wmove (p, y, x);
        prefresh (p, padpos, 0, 0, 0, LINES - 1, COLS - 1);
    }

    /* cleanup */
    for (int i = 0; i < lines; i++)
        free (mkd[i]);

    free (mkd);
    endwin();
}       /* -----  end of function handle_input  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  raw_data
 *  Description:  Print markdown file without any formating
 * =====================================================================================
 */
void
raw_data() {
    wclear (p);

    for (int i = 0; i < lines; i++)
        if (mkd[i] != NULL)
            waddstr (p, mkd[i]);
}       /* -----  end of function raw_data  ----- */
