//
// Created by padi on 12/7/16.
//

#ifndef MDP_DISPLAY_H
#define MDP_DISPLAY_H
/* #####   HEADER FILE INCLUDES   ################################################### */
#include <ncurses.h>

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
void initialize(char *mdfile);
void display();
void handle_input();
void raw_data();

/* #####   EXPORTED VARIABLES   ##################################################### */
extern WINDOW *p;
extern char **mkd;
enum {
    HEADER_1 = 1,
    HEADER_2 = 2,
    HEADER_3 = 3,
    HEADER_4 = 4,
    HEADER_5 = 5,
    HEADER_6 = 6,
    LIST = 7,
    EMPHASIS_2 = 8,
    CODE_BLOCK = 9
};
#endif //MDP_DISPLAY_H
