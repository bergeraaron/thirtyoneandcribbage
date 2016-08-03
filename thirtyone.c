#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

#define CARDS_IN_HAND 		3 
#define NUM_PLAYERS		4

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
	card cards[CARDS_IN_HAND];
	int hand_value;
};

card * initialize_deck(card * deck);
card * shuffle_deck(card * deck);
int score_hand(player_hand * hand);
void player_ai(player_hand * hand, card * deck,int & deckctr, card * discard_deck,int & discardctr);
char get_input();

int main(int argc, char *argv[])
{
	int turn = 0;
	int nextcard = 0;//next card in the deck
	int numdiscard = 0;
	char inc,di,rc;
	//hands
	player_hand hands[NUM_PLAYERS];

	card * deck = new card[52];
	card * discard_deck = new card[52];
#if defined(DEBUG)
	printf("initial deck\n");
#endif
	deck = initialize_deck(deck);
/*
	for(int i=0;i<52;i++)
	{printf("%d %s\n",i,deck[i].card_name);}
*/
#if defined(DEBUG)
	printf("shuffle card\n");
#endif
	deck = shuffle_deck(deck);
/*
        for(int i=0;i<52;i++)
        {printf("%d %s\n",i,deck[i].card_name);}
	printf("cards test\n");
*/
	int cctr=0;
	int hctr=0;
	//deal
	for(int i=0;i<CARDS_IN_HAND*NUM_PLAYERS;i++)
	{
		hands[hctr].cards[cctr] = deck[i];
		hctr++;
		if(hctr == NUM_PLAYERS)
		{
			hctr=0;
			cctr++;
		}
		nextcard++;
	}
/**
	printf("print out hands\n");
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		printf("\n");
		printf("P%d hand\n",i);
	        for(int j=0;j<CARDS_IN_HAND;j++)
        	{printf(" %s ",j,hands[i].cards[j].card_name);}
		printf("Score:%d\n",score_hand(&hands[i]));
	}
/**/
        for(int i=0;i<NUM_PLAYERS;i++)
                hands[i].hand_value = score_hand(&hands[i]);

	//flip the card to the discard deck
	discard_deck[numdiscard] = deck[nextcard];
	nextcard++;
#if defined(DEBUG)
	printf("card on top of discard pile:%d %s next card in deck: %d %s\n",numdiscard,discard_deck[numdiscard].card_name,nextcard,deck[nextcard].card_name);
#endif
	//main loop

	while(true)
	{
	printf("--------------------------------------------------------\n");
        for(int i=0;i<NUM_PLAYERS;i++)
        {
                printf("\n");
                printf("P%d hand\n",i);
                for(int j=0;j<CARDS_IN_HAND;j++)
                {printf(" %s ",hands[i].cards[j].card_name);}
                printf("Score:%d\n",score_hand(&hands[i]));
        }


		printf("Player :%d turn\n",turn);
		//printf("Card on discard pile %s\n",discard_deck[numdiscard].card_name);
#if defined(DEBUG)
		printf("card on top of discard pile:%d %s next card in deck: %d %s\n",numdiscard,discard_deck[numdiscard].card_name,nextcard,deck[nextcard].card_name);
#endif
		printf("(d)raw (p)ickup (k)nock (c)omputer (q)uit\n");
		inc = get_input();
		if(inc == 'd')
		{
			printf("draw\n");
			printf("You drew %s \n",deck[nextcard].card_name);
			printf("(k)eep (d)iscard\n");

			di = get_input();
			if(di == 'k')
			{
				printf("replace which card in hand?\n");
				printf("1 2 3\n");

				rc = get_input();
				if(rc == '1')
				{
					numdiscard++;
					discard_deck[numdiscard] = hands[turn].cards[0];
					hands[turn].cards[0] = deck[nextcard];
					nextcard++;
				}
				else if(rc == '2')
                                {
                                        numdiscard++;
                                        discard_deck[numdiscard] = hands[turn].cards[1];
                                        hands[turn].cards[1] = deck[nextcard];
                                        nextcard++;
                                }
				else if(rc == '3')
                                {
                                        numdiscard++;
                                        discard_deck[numdiscard] = hands[turn].cards[2];
                                        hands[turn].cards[2] = deck[nextcard];
                                        nextcard++;
                                }
			}
			else if(di == 'd')
			{
				numdiscard++;
				discard_deck[numdiscard] = deck[nextcard];
				nextcard++;
			}
		}
		else if(inc == 'p')
		{
			printf("pickup\n");
		}
		else if(inc == 'k')
		{
			printf("knock\n");
		}
		else if (inc == 'c')
		{
			player_ai(&hands[turn],deck,nextcard,discard_deck,numdiscard);
		}
		else if(inc == 'q')
		{break;}

		//score the hand
		hands[turn].hand_value = score_hand(&hands[turn]);

		if(hands[turn].hand_value == 31)
		{
			printf("Player %d WINNER!!!!\n",turn);
			break;
		}

		turn++;
		if(turn == 4)
		{turn=0;}
	}

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
		else if(card_ctr == 1)
			{deck[i].card_points = 11;}
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
	bool allonesuit = false;
	int points_by_suit[4];
	int suits[4] = {0,0,0,0};
	for(int i=0;i<4;i++)
		{points_by_suit[i]=0;}
	//see how many of each value we have
	for(int i=0;i<CARDS_IN_HAND;i++)
		suits[hand->cards[i].card_suit]++;

        for(int i=0;i<4;i++)
        {
                //printf("suit:%d  %d\n",i,suits[i]);
                if(suits[i] == 4)//flush
                {allonesuit = true;}
        }

	if(allonesuit)
	{
        	for(int i=0;i<CARDS_IN_HAND;i++)
	        {
			score+=hand->cards[i].card_points;
	        }
		return score;
	}
	else
	{
                for(int i=0;i<CARDS_IN_HAND;i++)
                {
                        points_by_suit[hand->cards[i].card_suit]+=hand->cards[i].card_points;
                }
	}

	score = -9999999;
	for(int i=0;i<4;i++)
	{
		if(points_by_suit[i] > score)
			score = points_by_suit[i];
	}
	/**
	aces worth 11
	face cards worth 10
	all have to be in the same suit
	/**/
	
	return score;
}

void player_ai(player_hand * hand, card * deck,int & deckctr, card * discard_deck,int & discardctr)
{
	int pickupflag = 0;
	int drawflag = 0;
	int score = 0;
	int bestscore=-9999;
	//player ai
	player_hand temp_hand;
	//check to see if we should pick up the card from the discard pile
	for(int i=0;i < CARDS_IN_HAND;i++)
	{
		for(int j=0;j<CARDS_IN_HAND;j++)
			temp_hand.cards[j] = hand->cards[j];

		temp_hand.cards[i] = discard_deck[discardctr];
#if defined(DEBUG)
printf("1: %s 2: %s 3: %s \n",temp_hand.cards[0].card_name,temp_hand.cards[1].card_name,temp_hand.cards[2].card_name); 
#endif
		score = score_hand(&temp_hand);
#if defined(DEBUG)
		printf("score: %d handscore: %d \n",score,hand->hand_value);
#endif
		if(score > hand->hand_value)
		{
#if defined(DEBUG)
			printf("we should pick up the discard\n");
#endif
			if(score > bestscore)
			{
				bestscore = score;
				pickupflag = i+1;
			}
		}
	}
#if defined(DEBUG)
	printf("pickupflag: %d\n",pickupflag);
#endif
	if(pickupflag > 0)
	{
		pickupflag--;
#if defined(DEBUG)
		printf("pickup the discard and swap the card\n");
#endif
		//swap the card
		card temp_card = discard_deck[discardctr];
                discard_deck[discardctr] = hand->cards[pickupflag];
                hand->cards[pickupflag] = temp_card;
		return;
	}

	//else draw a card and see where we should put it, or discard it
#if defined(DEBUG)
	printf("draw a card\n");
#endif
	bestscore = -9999;
	card drawncard = deck[deckctr];
	deckctr++;//advance the deck
#if defined(DEBUG)
	printf("drawn card %s \n",drawncard.card_name);
#endif
        for(int i=0;i < CARDS_IN_HAND;i++)
        {
                for(int j=0;j<CARDS_IN_HAND;j++)
                        temp_hand.cards[j] = hand->cards[j];

                temp_hand.cards[i] = drawncard;
#if defined(DEBUG)
printf("1: %s 2: %s 3: %s \n",temp_hand.cards[0].card_name,temp_hand.cards[1].card_name,temp_hand.cards[2].card_name);
#endif
                score = score_hand(&temp_hand);
#if defined(DEBUG)
		printf("score: %d handscore: %d \n",score,hand->hand_value);
#endif
                if(score > hand->hand_value)
                {
#if defined(DEBUG)
                        printf("we should keep the card we drew\n");
#endif
                        if(score > bestscore)
                        {
                                bestscore = score;
                                drawflag = i+1;
                        }
                }
        }
#if defined(DEBUG)
	printf("drawflag:%d\n",drawflag);
#endif
	if(drawflag > 0)
	{
		drawflag--;
#if defined(DEBUG)
		printf("keep the drawn card\n");
#endif
                discardctr++;
                discard_deck[discardctr] = hand->cards[drawflag];
                hand->cards[drawflag] = drawncard;
		//deckctr++;
	}
	else
	{
#if defined(DEBUG)
		printf("discard the drawn card\n");
#endif
		//otherwise discard the drawn card
	        discardctr++;
        	discard_deck[discardctr] = drawncard;
	}

}

char get_input()
{
	char temp;

        while(true)
	{
		temp = getchar();
		if(temp != '\n')
		{break;}
	}
	return temp;
}
