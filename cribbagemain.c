#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

#define CARDS_IN_HAND 4
#define CARDS_DEALT_TO_HAND 6
#define POSSIBLE_HANDS 15

struct card
{
	unsigned char num;
	char card_name[16];
	unsigned char card_value;
	unsigned char card_points;
	unsigned char card_suit;
};

struct player_hand
{
	card cards[6];
};

int p_hands[POSSIBLE_HANDS][CARDS_IN_HAND] = {{1,2,3,4},{1,2,3,5},{1,2,3,6},{1,2,4,5},
					      {1,2,4,6},{1,2,5,6},{1,3,4,5},{1,3,4,6},
					      {1,3,5,6},{1,4,5,6},{2,3,4,5},{2,3,4,6},
					      {2,3,5,6},{2,4,5,6},{3,4,5,6}};

int hand_scores[POSSIBLE_HANDS];

card * initialize_deck(card * deck);
card * shuffle_deck(card * deck);
int score_hand(player_hand * hand);

int main(int argc, char *argv[])
{
	//hands
	player_hand p1_hand;
	player_hand p2_hand;

	player_hand analyse_hand;

	int p1ctr=0;
	int p2ctr=0;

	card * deck = new card[52];

	printf("initial deck\n");
	deck = initialize_deck(deck);
/*
	for(int i=0;i<52;i++)
	{printf("%d %s\n",i,deck[i].card_name);}
*/
	printf("shuffle card\n");
	deck = shuffle_deck(deck);
/*
        for(int i=0;i<52;i++)
        {printf("%d %s\n",i,deck[i].card_name);}
	printf("cards test\n");
*/
	//deal
	for(int i=0;i<CARDS_DEALT_TO_HAND*2;i++)
	{
		if(i % 2 == 0)
		{
			//p1
			p1_hand.cards[p1ctr]=deck[i];
			p1ctr++;
		}
		else
		{
			//p2
			p2_hand.cards[p2ctr]=deck[i];
			p2ctr++;
		}
	}

	printf("P1 hand\n");
	for(int i=0;i<CARDS_DEALT_TO_HAND;i++)
	{printf("%d %s\n",i,p1_hand.cards[i].card_name);}
	printf("\n");
	int best_hand=-1;
	int best_hand_value=-1;
	for(int i=0;i<POSSIBLE_HANDS;i++)
	{
		for(int x=0;x<CARDS_IN_HAND;x++)
		{analyse_hand.cards[x] = p1_hand.cards[p_hands[i][x]-1];}

		hand_scores[i] = score_hand(&analyse_hand);
		if(hand_scores[i] >= best_hand_value)
		{best_hand = i;best_hand_value = hand_scores[i];}
	}

	printf("best hand\n");
	for(int i=0;i<CARDS_IN_HAND;i++)
        {printf("%d %s\n",i,p1_hand.cards[p_hands[best_hand][i]-1].card_name);}
        printf("hand score:%d\n",best_hand_value);

/**
	printf("P2 hand\n");
	for(int i=0;i<CARDS_IN_HAND;i++)
	{printf("%d %s\n",i,p2_hand.cards[i].card_name);}
	int p2score = score_hand(&p2_hand);
	printf("p2score:%d\n",p2score);
/**/
	free(deck);
	return 0;

}

card * shuffle_deck(card * deck)
{
	int temp_deck_ctr=0;
	card * temp_deck = new card[52];
  	srand(time(NULL));
	int sel_card; 

	while(temp_deck_ctr < 52)
	{
		sel_card = (rand() % 52);
		if(deck[sel_card].num != 0)
		{
			temp_deck[temp_deck_ctr] = deck[sel_card];
			deck[sel_card].num=0;
		//	printf("sel card: %d ctr %d\n",sel_card,temp_deck_ctr);	
			temp_deck_ctr++;

		}
	}

	deck = temp_deck;
	return deck;
}

card * initialize_deck(card * deck)
{
	int i=0;

	int suit_ctr=0;
	int card_ctr=1;

	char suit[4][16];
	sprintf(suit[0],"heart");//heart
	sprintf(suit[1],"diamond");//diamond
	sprintf(suit[2],"club");//club
	sprintf(suit[3],"spade");//spade

	for(i=0;i<52;i++)
	{
		deck[i].num=i+1;
		if(card_ctr == 1)
		{sprintf(deck[i].card_name,"A %s",suit[suit_ctr]);}
		else if(card_ctr > 1 && card_ctr < 11)
		{sprintf(deck[i].card_name,"%d %s",card_ctr,suit[suit_ctr]);}
		else if(card_ctr == 11)
		{sprintf(deck[i].card_name,"J %s",suit[suit_ctr]);}
                else if(card_ctr == 12)
                {sprintf(deck[i].card_name,"Q %s",suit[suit_ctr]);}
                else if(card_ctr == 13)
                {sprintf(deck[i].card_name,"K %s",suit[suit_ctr]);}

		if(card_ctr > 10)
			{deck[i].card_points = 10;}
		else
			{deck[i].card_points = card_ctr;}
		deck[i].card_value = card_ctr;
		deck[i].card_suit = suit_ctr;

		card_ctr++;
		if(card_ctr == 14)
		{card_ctr=1;suit_ctr++;}
	}

	return deck;
}

int score_hand(player_hand * hand)
{
	int score = 0;
	int handpoints = 0;
	int values[14];
	int points[14];
	int suits[4] = {0,0,0,0};
	for(int i=0;i<14;i++)
		{values[i]=0;points[i]=0;}
	//see how many of each value we have
	for(int i=0;i<CARDS_IN_HAND;i++)
	{
		values[hand->cards[i].card_value]++;
		points[hand->cards[i].card_points]++;
		suits[hand->cards[i].card_suit]++;
	}
	for(int i=0;i<4;i++)
	{
		//printf("suit:%d  %d\n",i,suits[i]);
		if(suits[i] == 4)//flush
		{score+=4;}
	}
//	printf("score after flush:%d\n",score);
	//pairs
	for(int i=0;i<14;i++)
	{
		if(values[i] == 4)
		{score += 12;}
		else if (values[i] == 3)
		{score += 6;}
		else if (values[i] == 2)
		{score += 2;}
	}
//	printf("score after pairs:%d\n",score);
	//runs
	for(int i=0;i<14;i++)
	{
		if((i + 4) < 13)
		if(values[i] == 1 && values[i+1] == 1  && values[i+2] == 1  && values[i+3] == 1)
		{score += 4;}

		if((i + 3) < 13)
		{
			if(values[i] == 1 && values[i+1] == 1  && values[i+2] == 1)
			{score += 3;}
			if(values[i] > 1 && values[i+1] == 1  && values[i+2] == 1)
			{score += 3 * 2;}
			if(values[i] == 1 && values[i+1] > 1  && values[i+2] == 1)
			{score += 3 * 2;}
			if(values[i] == 1 && values[i+1] == 1  && values[i+2] > 1)
			{score += 3 * 2;}
		}
	}
//	printf("score after runs:%d\n",score);

	if((hand->cards[0].card_points + hand->cards[1].card_points) == 15)
	score += 2;
	if((hand->cards[0].card_points + hand->cards[2].card_points) == 15)
	score += 2;
	if((hand->cards[0].card_points + hand->cards[3].card_points) == 15)
	score += 2;

	if((hand->cards[1].card_points + hand->cards[2].card_points) == 15)
	score += 2;
	if((hand->cards[1].card_points + hand->cards[3].card_points) == 15)
	score += 2;

	if((hand->cards[2].card_points + hand->cards[3].card_points) == 15)
	score += 2;

	if((hand->cards[0].card_points + hand->cards[1].card_points + hand->cards[2].card_points) == 15)
	score += 2;
	if((hand->cards[1].card_points + hand->cards[2].card_points + hand->cards[3].card_points) == 15)
	score += 2;
	if((hand->cards[0].card_points + hand->cards[2].card_points + hand->cards[3].card_points) == 15)
	score += 2;
	if((hand->cards[0].card_points + hand->cards[1].card_points + hand->cards[3].card_points) == 15)
	score += 2;

	if((hand->cards[0].card_points + hand->cards[1].card_points + hand->cards[2].card_points + hand->cards[3].card_points) == 15)
	score += 2;

//	printf("score after 15s:%d\n",score);

	return score;
}




