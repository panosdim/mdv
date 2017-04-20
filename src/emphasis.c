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
#include "emphasis.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
/**
 * Parse line for emphasis, inline code, escape characters and links.
 * @param line A line of the markdown file
 */
void
parse_marks(char *line) {
    char *emp = NULL;

    /* Check for emphasis characters in line */
    if ((emp = strchr(line, '*')) != NULL || (emp = strchr(line, '_')) != NULL) {
        /* Check for emphasis characters at the beginning of line */
        if (emp == line) {
            /* Check for space after emphasis characters */
            if (emp[1] == ' ') {
                /* Parse rest of line */
                wprintw(p, "%.*s", 1, emp);
                parse_marks(emp + 1);
                return;
            }
        }

        /* Check if we have an escape char before or surrounded space */
        if (emp[-1] == '\\' || (emp[-1] == ' ' && emp[1] == ' ')) {
            if (emp[-1] == '\\') {
                /* Print until '*' or '_' char, remove backslash and parse rest of line */
                wprintw(p, "%.*s", emp - line - 1, line);
                wprintw(p, "%.*s", 1, emp);
                parse_marks(emp + 1);
                return;
            } else {
                /* Print until '*' or '_' char and parse rest of line */
                wprintw(p, "%.*s", emp - line + 1, line);
                parse_marks(emp + 1);
                return;
            }
        } else {
            wprintw(p, "%.*s", emp - line, line);
            char *emp_end;

            if (emp[1] == '*' || emp[1] == '_') {
                wattron (p, A_BOLD);
                (emp_end = strchr(emp + 2, '*')) || (emp_end = strchr(emp + 2, '_'));
                wprintw(p, "%.*s", emp_end - (emp + 2), emp + 2);
                wattroff (p, A_BOLD);
                /* Parse rest of line */
                parse_marks(emp_end + 2);
                return;
            } else {
                wattron (p, A_UNDERLINE);
                (emp_end = strchr(emp + 1, '*')) || (emp_end = strchr(emp + 1, '_'));
                wprintw(p, "%.*s", emp_end - (emp + 1), emp + 1);
                wattroff (p, A_UNDERLINE);
                /* Parse rest of line */
                parse_marks(emp_end + 1);
                return;
            }
        }
    } else
        waddstr (p, line);
}

#pragma clang diagnostic pop