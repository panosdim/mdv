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
#include <string.h>
#include "display.h"
#include "file.h"
#include "parser.h"
#include "mdv.h"

#define MAX_RIGHT_STATUS 25

WINDOW *p;
static char **mkd;
static int ROWS, lines;
static char *filename;
static bool raw_display = false;

static void statusbar();

/**
 * Read markdown file to buffer and initialize ncurses
 * @param mdfile The markdown file
 */
void initialize(char *mdfile)
{
    /* Open markdown file for read only */
    filename = mdfile;
    FILE *fp = fopen(mdfile, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s for reading\n", mdfile);
        exit(EXIT_FAILURE);
    }

    /* initialize ncurses */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    /* Check if terminal support colours */
    if (has_colors() == FALSE)
    {
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
    init_pair(LINK, COLOR_BLUE, COLOR_BLACK);

    /* Find how much rows we need for the pad */
    ROWS = fcntlines(fp, COLS);
    /* Read file in array of string lines */
    mkd = freadlines(fp, &lines);
    /* close markdown file */
    fclose(fp);

    /* create a new pad */
    p = newpad(ROWS, COLS);

    if (p == NULL)
    {
        endwin();
        printf("Unable to create new pad\n");
        exit(EXIT_FAILURE);
    }

    keypad(p, TRUE);
}

/**
 * Process and display markdown file
 */
void display()
{
    wclear(p);
    markdown(mkd, lines);

    wmove(p, 0, 0);
    statusbar();
}

/**
 * Wait for use input after display markdown
 */
void handle_input()
{
    int ch;
    int x = 0;
    int y = 0;
    int padpos = 0;
    prefresh(p, padpos, 0, 0, 0, LINES - 2, COLS - 1);

    while ((ch = wgetch(p)) != 'q')
    {
        if (ch == KEY_HOME)
            x = 0;
        else if (ch == KEY_END)
            x = COLS - 1;
        else if (ch == KEY_LEFT)
            (x > 0) && x--;
        else if (ch == KEY_RIGHT)
            (x < COLS - 1) && x++;
        else if (ch == KEY_UP)
        {
            if (y == 0 && padpos == 0)
                continue;
            (y == padpos) && padpos--;
            y--;
        }
        else if (ch == KEY_DOWN)
        {
            if (y == ROWS - 1)
                continue;
            (y == padpos + LINES - 2) && padpos++;
            y++;
        }
        else if (ch == KEY_SHOME)
        {
            y = 0;
            padpos = 0;
        }
        else if (ch == KEY_SEND)
        {
            y = ROWS - 1;
            padpos = ROWS - LINES + 1;
        }
        else if (ch == 'r')
        {
            if (raw_display)
                display();
            else
            {
                wattrset(p, A_NORMAL);
                raw_data();
            }
            raw_display = !raw_display;
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
void raw_data()
{
    wclear(p);

    for (int i = 0; i < lines; i++)
        if (mkd[i] != NULL)
            waddstr(p, mkd[i]);
}

/**
 * Shows a status bar at the last line of terminal
 */
static void statusbar()
{
    int y, x, rt;
    getyx(p, y, x);
    move(LINES - 1, 0);
    clrtoeol();
    attron(COLOR_PAIR(STATUS));

    int left_part_len = COLS - MAX_RIGHT_STATUS;
    char left_part[left_part_len];
    char *mode = raw_display ? "raw" : "formatted";
    rt = snprintf(left_part, sizeof(left_part), "%s (%s)", filename, mode);
    if (rt > left_part_len)
    {
        char *pos = strrchr(filename, '/');
        if (pos != NULL)
        {
            rt = snprintf(left_part, sizeof(left_part), "%s (%s)", pos + 1, mode);
            if (rt > left_part_len)
            {
                char m = raw_display ? 'r' : 'f';
                snprintf(left_part, sizeof(left_part), "%s (%c)", pos + 1, m);
            }
        }
    }

    char right_part[MAX_RIGHT_STATUS];
    int percentage = (100 * (y + 1) / ROWS);
    snprintf(right_part, sizeof(right_part), "Ln %d, Col %d (%d%%)", y + 1, x + 1, percentage);

    int white_space = COLS - strlen(left_part) - strlen(right_part);
    printw("%s%*c%s", left_part, white_space, ' ', right_part);

    attroff(COLOR_PAIR(STATUS));
    refresh();
}
