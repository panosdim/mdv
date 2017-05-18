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

#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "file.h"
#include "parser.h"

WINDOW *p;
char **mkd;
static int ROWS, lines;
static char *filename;
static bool raw_display = false;

static void statusbar();

/**
 * Read markdown file to buffer and initialize ncurses
 * @param mdfile The markdown file
 */
void
initialize(char *mdfile) {
    /* Open markdown file for read only */
    filename = mdfile;
    FILE *fp = fopen(mdfile, "r");

    if (fp == NULL) {
        fprintf(stderr, "Can't open file %s for reading\n", mdfile);
        exit(EXIT_FAILURE);
    }

    /* initialize ncurses */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    /* Check if terminal support colours */
    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(EXIT_FAILURE);
    }

    /* Initialize color pairs */
    start_color();
    init_pair(HEADER_1, COLOR_RED, COLOR_BLACK);
    init_pair(HEADER_2, COLOR_GREEN, COLOR_BLACK);
    init_pair(HEADER_3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(HEADER_4, COLOR_BLUE, COLOR_BLACK);
    init_pair(HEADER_5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(HEADER_6, COLOR_CYAN, COLOR_BLACK);
    init_pair(LIST, COLOR_GREEN, COLOR_BLACK);
    init_pair(HR, COLOR_BLACK, COLOR_WHITE);
    init_pair(CODE_BLOCK, COLOR_BLACK, COLOR_YELLOW);
    init_pair(STATUS, COLOR_WHITE, COLOR_BLUE);

    /* Find how much rows we need for the pad */
    ROWS = fcntlines(fp, COLS);
    /* Read file in array of string lines */
    mkd = freadlines(fp, &lines);
    /* close markdown file */
    fclose(fp);

    /* create a new pad */
    p = newpad(ROWS, COLS);

    if (p == NULL) {
        endwin();
        printf("Unable to create new pad\n");
        exit(EXIT_FAILURE);
    }

    keypad(p, TRUE);
}

/**
 * Process and display markdown file
 */
void
display() {
    wclear(p);
    markdown(mkd, lines);

    wmove(p, 0, 0);
    statusbar();
}

/**
 * Wait for use input after display markdown
 */
void
handle_input() {
    int ch;
    int x = 0;
    int y = 0;
    int padpos = 0;
    prefresh(p, padpos, 0, 0, 0, LINES - 2, COLS - 1);

    while ((ch = wgetch(p)) != 'q') {
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
                } else
                    y--;
                break;
            case KEY_DOWN:
                if (y == ROWS - 1)
                    break;
                else if (y == padpos + LINES - 2) {
                    y++;
                    padpos++;
                } else
                    y++;
                break;
            case 'r':
                if (raw_display) {
                    raw_display = false;
                    display();
                } else {
                    raw_display = true;
                    wattrset(p, A_NORMAL);
                    raw_data();
                }
                break;
            default:
                break;
        }

        wmove(p, y, x);
        statusbar();
        prefresh(p, padpos, 0, 0, 0, LINES - 2, COLS - 1);
    }

    /* cleanup */
    for (int i = 0; i < lines; i++)
        free(mkd[i]);

    free(mkd);
    endwin();
}

/**
 * Print markdown file without any formatting
 */
void
raw_data() {
    wclear(p);

    for (int i = 0; i < lines; i++)
        if (mkd[i] != NULL)
            waddstr (p, mkd[i]);
}

/**
 * Shows a status bar at the last line of terminal
 */
static void
statusbar() {
    int y, x;
    getyx(p, y, x);
    move(LINES - 1, 0);
    clrtoeol();
    attron(COLOR_PAIR(STATUS));
    if (raw_display) {
        printw("%s %s (%d\%) %d:%d", filename, "raw", (100 * (y + 1) / ROWS), y + 1, x + 1);
    } else {
        printw("%s %s (%d\%) %d:%d", filename, "formatted", (100 * (y + 1) / ROWS), y + 1, x + 1);
    }
    attroff(COLOR_PAIR(STATUS));
    refresh();
}