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

#ifndef MDV_H
#define MDV_H

#include <ncurses.h>

typedef struct mkd_s
{
    char **lines;
    int len;
    int rows;
    char *filename;
    WINDOW *p;
} mkd_s;

enum
{
    HEADER_1 = 1,
    HEADER_2 = 2,
    HEADER_3 = 3,
    HEADER_4 = 4,
    HEADER_5 = 5,
    HEADER_6 = 6,
    LIST = 7,
    HR = 8,
    CODE_BLOCK = 9,
    STATUS = 10,
    LINK = 11
};

#endif //MDV_H