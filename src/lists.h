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

#ifndef MDV_LISTS_H
#define MDV_LISTS_H

#include <stdbool.h>
#include "mdv.h"

#define INDENT_SPACES 4
#define NEXT_LIST_PAR 4
#define LIST_INDENT_SPC 2

bool parse_lists(mkd_s *mkd, int ln);

#endif //MDV_LISTS_H
