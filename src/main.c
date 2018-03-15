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
#include <signal.h>
#include <ncurses.h>
#include "display.h"
#include "MdvConfig.h"

void handle_winch(int sig)
{
    endwin();
    // Needs to be called after an endwin() so ncurses will initialize
    // itself with the new terminal dimensions.
    refresh();
    clear();

    display();
    refresh();
}

/**
 * Main function check for passed arguments and render markdown file
 * @param argc Number of arguments
 * @param argv String array with arguments
 * @return 0 on success and -1 on failure
 */
int main(int argc, char *argv[])
{
    /* Check if markdown file passed as argument */
    if (argc != 2)
    {
        fprintf(stderr, "%s Version %d.%d\n",
                argv[0],
                MDV_VERSION_MAJOR,
                MDV_VERSION_MINOR);
        fprintf(stderr, "usage: %s markdown_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* initialize ncurses */
    initialize(argv[1]);
    /* performing markdown parsing */
    display();
    /* Wait for user input */
    handle_input();
}
