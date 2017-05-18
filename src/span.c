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
#include <memory.h>
#include "span.h"
#include "display.h"

/**
 * Parse line for span elements
 * @param line The line containing span elements markup
 */
void
parse_span(char *line) {
    size_t len = strlen(line);
    int i = 0;
    char next_ch;
    attr_t attrs = A_NORMAL;
    bool mlt_backtick = false;

    /* Parse line and copy formatted characters to ncurses window */
    while (i < len) {
        switch (line[i]) {
            case '*':
            case '_':
                /* Check if we have an asterisk with surrounded space */
                if ((i > 0 && i < len - 1) && (line[i - 1] == ' ' && line[i + 1] == ' ')) {
                    waddch(p, (const chtype) line[i]);
                    break;
                }

                /* Check if it is ITALIC and BOLD */
                if ((i < len - 2) && (line[i + 1] == line[i] && line[i + 2] == line[i])) {
                    if ((attrs & A_BOLD) && (attrs & A_UNDERLINE)) {
                        wattroff (p, attrs);
                        attrs &= A_NORMAL;
                    } else {
                        attrs |= A_BOLD | A_UNDERLINE;
                        wattron (p, attrs);
                    }
                    i = i + 2;
                    break;
                }
                /* Check if it is BOLD */
                if ((i < len - 1) && line[i + 1] == line[i]) {
                    if (attrs & A_BOLD) {
                        wattroff (p, attrs);
                        attrs &= A_NORMAL;
                    } else {
                        attrs |= A_BOLD;
                        wattron (p, attrs);
                    }
                    i = i + 1;
                    break;

                }
                /* Check if it is ITALIC */
                if (attrs & A_UNDERLINE) {
                    wattroff (p, attrs);
                    attrs &= A_NORMAL;
                } else {
                    attrs |= A_UNDERLINE;
                    wattron (p, attrs);
                }
                break;
            case '\\':
                /* Check if next character is backslash escape */
                if ((i < len - 1) && (next_ch = line[i + 1])) {
                    switch (next_ch) {
                        case '\\':
                        case '`':
                        case '*':
                        case '_':
                        case '{':
                        case '}':
                        case '[':
                        case ']':
                        case '(':
                        case ')':
                        case '#':
                        case '+':
                        case '-':
                        case '.':
                        case '!':
                            waddch(p, (const chtype) next_ch);
                            i++;
                            break;
                        default:
                            waddch(p, (const chtype) line[i]);
                            break;
                    }
                }
                break;
            case '`':
                /* Check if we have multiple backticks */
                if ((i < len - 1) && (line[i + 1] == '`')) {
                    mlt_backtick ? (mlt_backtick = false) : (mlt_backtick = true);
                    i++;
                }
                /* Check for literal backtick character */
                if (mlt_backtick && attrs & A_COLOR) {
                    waddch(p, (const chtype) line[i]);
                    break;
                }
                /* Check if we need to set on or off the color */
                if (attrs & A_COLOR) {
                    wattroff (p, COLOR_PAIR(CODE_BLOCK));
                    attrs &= A_NORMAL;
                } else {
                    attrs |= A_COLOR;
                    wattron (p, COLOR_PAIR(CODE_BLOCK));
                }
                break;
            default:
                waddch(p, (const chtype) line[i]);
        }
        i++;
    }
}