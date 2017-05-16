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

#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "hr.h"


/**
 * Identify if a line is a horizontal rule and parse it otherwise it use parse_marks function
 * @param line A line of the markdown document
 * @return true if line is horizontal rule otherwise false.
 */
bool
identify_hr(char **mkd, int ln) {
    char *line = mkd[ln];
    int i = 0;

    /* Check if line starts with * or - or _ */
    if (line[i] == '*' || line[i] == '-' || line[i] == '_') {
        /* Check for at least three * or - or _ */
        int hr_marks = 1;
        size_t ln_length = strlen (line);
        i++;
        while (i < ln_length) {
            if (line[i] == line[0]) {
                hr_marks++;
                i++;
                continue;
            }
            /* Check for spaces between * or - */
            if (line[i] == ' ' && line[i-1] == line[0]) {
                i++;
                continue;
            }
            /* Check for last newline character */
            if (i == ln_length - 1 && line[i] == '\n') {
                i++;
                continue;
            }
            return false;
        }

        if (hr_marks < 3) {
            return false;
        } else {
            /* Print horizontal rule */
            int clns = COLS;
            while (clns-- > 0)
                waddch (p, '-' | COLOR_PAIR (HR));
            return true;
        }
    } else
        return false;
}