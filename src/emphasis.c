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
#include "display.h"

/**
 * Parse line for emphasis, inline code, escape characters and links.
 * @param line A line of the markdown file
 * @param pos Position in line to continue parsing
 */
void
parse_marks(char *line, char *pos) {
    char *emp = NULL;

    /* Check for emphasis characters in line */
    if ((emp = strchr(pos, '*')) != NULL || (emp = strchr(pos, '_')) != NULL) {
        /* Check for emphasis characters at the beginning of line */
        if (emp == line) {
            /* Check for space after emphasis characters */
            if (emp[1] == ' ') {
                /* Parse rest of line */
                wprintw(p, "%.*s", 1, emp);
                parse_marks(line, emp + 1);
                return;
            }
        }

        /* Check if we have an escape char before or surrounded space */
        if (emp > line) {
            if (emp[-1] == '\\') {
                /* Print until '*' or '_' char, remove backslash and parse rest of line */
                wprintw(p, "%.*s", emp - pos - 1, pos);
                wprintw(p, "%.*s", 1, emp);
                parse_marks(line, emp + 1);
                return;
            }
            if (emp[-1] == ' ' && emp[1] == ' ') {
                /* Asterisk surrounded by spaces. Print and parse rest of line */
                wprintw(p, "%.*s", emp - pos + 1, pos);
                parse_marks(line, emp + 1);
                return;
            }
        }

        wprintw(p, "%.*s", emp - pos, pos);
        char *emp_end;

        if (emp[1] == '*' || emp[1] == '_') {
            if ((emp_end = strchr(emp + 2, '*')) != NULL || (emp_end = strchr(emp + 2, '_')) != NULL) {
                wattron (p, A_BOLD);
                wprintw(p, "%.*s", emp_end - (emp + 2), emp + 2);
                wattroff (p, A_BOLD);
                /* Parse rest of line */
                parse_marks(line, emp_end + 2);
            }
        } else {

            if ((emp_end = strchr(emp + 1, '*')) != NULL || (emp_end = strchr(emp + 1, '_')) != NULL) {
                wattron (p, A_UNDERLINE);
                wprintw(p, "%.*s", emp_end - (emp + 1), emp + 1);
                wattroff (p, A_UNDERLINE);
                /* Parse rest of line */
                parse_marks(line, emp_end + 1);
            }
        }

    } else
        waddstr (p, pos);
}