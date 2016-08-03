#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cardscurses.h"


int main(int argc, char *argv[])
{
	int card_col[4] = {28,6,28,63};
	int card_row[4] = {35,14,3,14};

        int row,col=0;
	scr_init(&row,&col);
        printtemplate(row,col);

	print_string_h("Player 1", 31, 38);
	print_string_v("Player 2", 2,16);
	print_string_h("Player 3", 31, 1);
	print_string_v("Player 4", 68,16);

	draw_deck_discard();

	for(int i=0;i<4;i++)
	{
		if(i == 0 || i == 2)//players 1 and 3
		{
			draw_player_hand(card_col[i],card_row[i]);
        		draw_player_hand(card_col[i]+6,card_row[i]);
        		draw_player_hand(card_col[i]+12,card_row[i]);
		}
		else if(i == 1 || i == 3)
		{
			draw_player_hand(card_col[i],card_row[i]);
			draw_player_hand(card_col[i],card_row[i]+5);
			draw_player_hand(card_col[i],card_row[i]+10);
		}
	}
        refresh();

	getch();

	endwin();

	return 0;
}
