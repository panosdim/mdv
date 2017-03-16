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
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#define INDENT_SPACES 4
#define NEXT_LIST_PAR 4
#define LIST_INDENT_SPC 2
#define HEADER_SETEXT_1 1
#define HEADER_SETEXT_2 2

static void parse_atx_headers (char *header);
static bool parse_lists (char **mkd, int ln);
static void parse_marks (char *line);
static bool parse_headers (char **mkd, int ln);
static void parse_setext_headers (char *header, int level);
static bool parse_hr (char **mkd, int ln);

/**
 * Parse and render a markdown file stored as array of lines
 * @param mkd An array of lines
 * @param lines Number of lines in the array
 */
void
markdown (char **mkd, int lines) {
  /* Parse every line of markdown file */
  for (int i = 0; i < lines; i++) {
    /* Check for block elements */
    parse_headers (mkd, i) || parse_hr (mkd, i) || parse_lists (mkd, i);
  }
}

/**
 * Identify if line is a header of settext or atx style and parse it.
 * @param line A line of a markdown document.
 * @return true if line is header otherwise false.
 */
static bool
parse_headers (char **mkd, int ln) {
  int i = 0;
  char *line = mkd[ln];

  if (line[0] == '#') {
    parse_atx_headers (line);
    return true;
  }

  /* Don't check for setext header in first line */
  if (ln != 0) {
    /* Check setext header */
    if (line[0] == '=') {
      while (line[i] == '=')
        i++;

      if (i == (strlen (line) - 1)) {
        parse_setext_headers (mkd[ln - 1], HEADER_SETEXT_1);
        return true;
      } else {
        return false;
      }
    }

    i = 0;
    if (line[0] == '-') {
      while (line[i] == '-')
        i++;

      if ((i == strlen (line) - 1)) {
        parse_setext_headers (mkd[ln - 1], HEADER_SETEXT_2);
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

/**
 * Parse atx style header lines
 * @param header The line with the header
 */
static void
parse_atx_headers (char *header) {
  int i = 0;
  int lvl = 0;
  size_t end;
  char *line = NULL;

  /* Find the level of header */
  while (header[i] == '#' && i < 6) {
    lvl++;
    i++;
  }

  /* Remove spaces from beginning of header */
  while (header[i] == ' ')
    i++;

  /* Remove trailing newline character */
  end = strlen (header) - 1;

  if (header[end] == '\n')
    end--;

  /* Remove trailing hashes if exists */
  if (header[end] == '#')
    while (header[--end] == '#');

  /* Print header */
  wattron (p, COLOR_PAIR (lvl));
  /* Allocate memory to copy header string for marks processing */
  line = malloc ((end - i + 2) * sizeof (char));

  if (line == NULL) {
    fprintf (stderr, "\ndynamic memory allocation failed\n");
    exit (EXIT_FAILURE);
  }

  memcpy (line, header + i, end - i + 1);
  line[end - i + 1] = '\0';
  parse_marks (line);
  free (line);
  waddch (p, '\n');
  wattroff (p, COLOR_PAIR (lvl));
}

static void
parse_setext_headers (char *header, int level) {
  int y, x;

  /* Clear previous line and print it again with header style */
  getyx (p, y, x);

  if (y > 0)
    wmove (p, y - 1, 0);

  clrtoeol();

  if (level == HEADER_SETEXT_1) {
    wattron (p, COLOR_PAIR (HEADER_1));
    waddstr (p, header);
    wattroff (p, COLOR_PAIR (HEADER_1));
  } else if (level == HEADER_SETEXT_2) {
    wattron (p, COLOR_PAIR (HEADER_2));
    waddstr (p, header);
    wattroff (p, COLOR_PAIR (HEADER_2));
  }
}

/**
 * Parse line for emphasis, inline code, escapable characters and links.
 * @param line A line of the markdown file
 */
static void
parse_marks (char *line) {
  char *emp = NULL;

  /* Check for emphasis characters in line */
  if ((emp = strchr (line, '*')) != NULL || (emp = strchr (line, '_')) != NULL) {
    /* Check for emphasis characters at the beginning of line */
    if (emp == line) {
      /* Check for space after emphasis characters */
      if (emp[1] == ' ') {
        /* Parse rest of line */
        wprintw (p, "%.*s", 1, emp);
        parse_marks (emp + 1);
        return;
      }
    }

    /* Check if we have an escape char before or surrounded space */
    if (emp[-1] == '\\' || (emp[-1] == ' ' && emp[1] == ' ')) {
      if (emp[-1] == '\\') {
        /* Print until '*' or '_' char, remove backslash and parse rest of line */
        wprintw (p, "%.*s", emp - line - 1, line);
        wprintw (p, "%.*s", 1, emp);
        parse_marks (emp + 1);
        return;
      } else {
        /* Print until '*' or '_' char and parse rest of line */
        wprintw (p, "%.*s", emp - line + 1, line);
        parse_marks (emp + 1);
        return;
      }
    } else {
      wprintw (p, "%.*s", emp - line, line);
      char *emp_end;

      if (emp[1] == '*' || emp[1] == '_') {
        wattron (p, A_BOLD);
        (emp_end = strchr (emp + 2, '*')) || (emp_end = strchr (emp + 2, '_'));
        wprintw (p, "%.*s", emp_end - (emp + 2), emp + 2);
        wattroff (p, A_BOLD);
        /* Parse rest of line */
        parse_marks (emp_end + 2);
        return;
      } else {
        wattron (p, A_UNDERLINE);
        (emp_end = strchr (emp + 1, '*')) || (emp_end = strchr (emp + 1, '_'));
        wprintw (p, "%.*s", emp_end - (emp + 1), emp + 1);
        wattroff (p, A_UNDERLINE);
        /* Parse rest of line */
        parse_marks (emp_end + 1);
        return;
      }
    }
  } else
    waddstr (p, line);
}

/**
 * Identify if a line is a horizontal rule and parse it otherwise it use parse_marks function
 * @param line A line of the markdown document
 * @return true if line is horizontal rule otherwise false.
 */
static bool
parse_hr (char **mkd, int ln) {
  char *line = mkd[ln];
  int i = 0;

  /* Check if line starts with * or - or _ */
  if (line[i] == '*' || line[i] == '-' || line[i] == '_') {
    /* Check for at least three * or - or _ */
    int hr_marks = 1;
    size_t ln_length = strlen (line);
    i++;
    while (i < ln_length && (line[i] == ' ' || (line[i] == line[0] && hr_marks++)))
      i++;

    if (hr_marks < 3 || i != ln_length - 1) {
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

/**
 * Identify if a line is a list and parse it otherwise it use parse_marks function
 * @param line A line of the markdown document
 * @return true if line is list otherwise false.
 */
static bool
parse_lists (char **mkd, int ln) {
  static int lvl = 0;
  static bool in_list = false;
  char *line = mkd[ln];
  int i = 0;
  char list_markup;

  /* Check for spaces at beginning */
  while (line[i] == ' ')
    i++;

  if ((line[i] == '*' || line[i] == '+' || line[i] == '-') && (line[i + 1] == ' ' || line[i + 1] == '\t')) {
    /* Check that we until three spaces before list markup character */
    if (!in_list && i < 4) {
      /* Set flag that we are in list */
      in_list = true;
    }
    if (in_list) {
      /* Find level of list */
      lvl = i / 4;
      switch (lvl % 3) {
        case 0:
          list_markup = '*';
          break;
        case 1:
          list_markup = '+';
          break;
        case 2:
          list_markup = '-';
          break;
        default:
          list_markup = '*';
      }

      /* Remove space after list markup character */
      i++;
      while (line[i] == ' ')
        i++;

      /* Print list item */
      int spaces = lvl * INDENT_SPACES;
      while (spaces-- > 0)
        waddch (p, ' ');
      waddch (p, list_markup | COLOR_PAIR (LIST));
      waddch (p, ' ');
    }
  } else {
    /* Next paragraph on same list item must be start with one tab or 4 spaces */
    if (ln != 0 && !(i == NEXT_LIST_PAR || line[0] == '\t')) {
      /* Remove space before new line character */
      int j = 0;
      while (mkd[ln - 1][j] == ' ' || mkd[ln - 1][j] == '\t')
        j++;
      if (mkd[ln - 1][j] == '\n') {
        in_list = false;
        lvl = 0;
      }
    }

    if (in_list) {
      /* Check for correct indent of paragraph lines */
      int spaces = (lvl * INDENT_SPACES) + LIST_INDENT_SPC;
      if (i != spaces) {
        while (spaces-- > 0)
          waddch (p, ' ');
      }
    }
  }

  /* Check for inline markups */
  parse_marks (line + i);
  return false;
}

#pragma clang diagnostic pop