#include <ncurses.h>

#define MAXROW 40
#define MAXCOL 70

void scr_init(int * n_row,int * n_col);
void printtemplate(int row,int col);
void print_string_h(char * string, int x, int y);
void print_string_v(char * string, int x, int y);
void draw_deck_discard();
void draw_player_hand(int row, int col);
