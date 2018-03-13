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

#include "display.h"
#include "lists.h"
#include "span.h"
#include "mdv.h"

/**
 * Identify if a line is a list and parse it otherwise it use parse_span function
 * @param mkd An array of lines
 * @param ln The line containing a list markup
 */
bool parse_lists(char **mkd, int ln)
{
    static int lvl = 0;
    static bool in_list = false;
    char *line = mkd[ln];
    int i = 0;

    /* Check for spaces at beginning */
    while (line[i] == ' ')
        i++;

    /* TODO: Support ordered lists */

    if ((line[i] == '*' || line[i] == '+' || line[i] == '-') && (line[i + 1] == ' ' || line[i + 1] == '\t'))
    {
        /* Check that there is until three spaces before list markup character */
        if (!in_list && i < 4)
        {
            /* Set flag that we are in list */
            in_list = true;
        }
        if (in_list)
        {
            /* Find level of list */
            lvl = i / 4;
            char list_markup;
            int list_lvl = lvl % 3;
            if (list_lvl == 0)
                list_markup = '*';
            else if (list_lvl == 1)
                list_markup = '+';
            else if (list_lvl == 2)
                list_markup = '-';
            else
                list_markup = '*';

            /* Remove space after list markup character */
            i++;
            while (line[i] == ' ')
                i++;

            /* Print list item */
            int spaces = lvl * INDENT_SPACES;
            while (spaces-- > 0)
                waddch(p, ' ');
            waddch(p, list_markup | COLOR_PAIR(LIST));
            waddch(p, ' ');
        }
    }
    else
    {
        /* Next paragraph on same list item must be start with one tab or 4 spaces */
        if (ln != 0 && !(i == NEXT_LIST_PAR || line[0] == '\t'))
        {
            /* Remove space before new line character */
            int j = 0;
            while (mkd[ln - 1][j] == ' ' || mkd[ln - 1][j] == '\t')
                j++;
            if (mkd[ln - 1][j] == '\n')
            {
                in_list = false;
                lvl = 0;
            }
        }

        if (in_list)
        {
            /* Check for correct indent of paragraph lines */
            int spaces = (lvl * INDENT_SPACES) + LIST_INDENT_SPC;
            if (i != spaces)
            {
                while (spaces-- > 0)
                    waddch(p, ' ');
            }
        }
    }

    /* Check for inline markups */
    if (in_list)
    {
        parse_span(line + i);
        return true;
    }
    else
    {
        return false;
    }
}