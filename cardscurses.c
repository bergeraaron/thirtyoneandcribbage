#include <stdio.h>
#include <string.h>
#include "cardscurses.h"

void scr_init(int * n_row,int * n_col)
{
        //start curses
        initscr();
        noecho();
        //turn keypad on
        keypad(stdscr, TRUE);

        //get max size of std window
        getmaxyx(stdscr,*n_row,*n_col);

        if(*n_row > MAXROW)
        {*n_row=MAXROW;}
        if(*n_col > MAXCOL)
        {*n_col=MAXCOL;}

}

void printtemplate(int row,int col)
{
        for(int i=0;i < col;i++)
        {
                mvaddch(0,i,'-');
                mvaddch(row-1,i,'-');
        }

        for(int i=0;i < row;i++)
        {
                mvaddch(i,0,'|');
                mvaddch(i,col-1,'|');
        }
}

void draw_deck_discard()
{
	int col = 31;
	int row = 16;
//deck
	int deck[8][2] = {15,31,15,32,18,31,18,32,16,30,17,30,16,33,17,33};

	for(int i=0;i<8;i++)
	{
		if(i < (8/2))
		mvaddch(deck[i][0],deck[i][1],'-');
		else
		mvaddch(deck[i][0],deck[i][1],'|');
	}

//discard
	col = 37;
	row = 16;
/**
        mvaddch(row,col,'1');
        mvaddch(row,col+1,'0');
        mvaddch(row+1,col+1,'H');
/**/
	for(int i=0;i<8;i++)
        {
                if(i < (8/2))
                mvaddch(deck[i][0],deck[i][1]+6,'-');
                else
                mvaddch(deck[i][0],deck[i][1]+6,'|');
        }
}

void draw_player_hand(int col,int row)
{
	int card[8][2];
//difference between cards col = 6
	card[0][0] = row-1;
	card[0][1] = col;
	card[1][0] = row-1;
	card[1][1] = col+1;
	card[2][0] = row+2;
	card[2][1] = col;
	card[3][0] = row+2;
	card[3][1] = col+1;
	card[4][0] = row;
	card[4][1] = col-1;
	card[5][0] = row+1;
	card[5][1] = col-1;
	card[6][0] = row;
	card[6][1] = col+2;
	card[7][0] = row+1;
	card[7][1] = col+2;

        for(int i=0;i<8;i++)
        {
                if(i < (8/2))
                mvaddch(card[i][0],card[i][1],'-');
                else
                mvaddch(card[i][0],card[i][1],'|');
        }
}

void print_string_h(char * string, int x, int y)
{
	mvprintw(y,x,string);
}

void print_string_v(char * string, int x, int y)
{
	int len = strlen(string);
	int offset=0;
	char temp;
	for(int i=0;i<len;i++)
	{
		offset = y + i;
		temp = string[i];
		//mvprintw(offset,x,&temp);
		mvaddch(offset,x,temp);
	}
}



