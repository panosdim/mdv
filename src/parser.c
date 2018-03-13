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

#include "headers.h"
#include "lists.h"
#include "hr.h"
#include "span.h"

/**
 * Parse and render a markdown file stored as array of lines
 * @param mkd An array of lines
 * @param lines Number of lines in the array
 */
void markdown(char **mkd, int lines)
{
    /* Parse every line of markdown file */
    for (int i = 0; i < lines; i++)
    {
        /* Check for block elements and if not just parse for span elements */
        if (!(parse_headers(mkd, i) || parse_hr(mkd, i) || parse_lists(mkd, i)))
            parse_span(mkd[i]);
    }
}