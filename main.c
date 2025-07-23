#include "header.h"

int main()
{
    int round = 0;

    srand(time(NULL));

    init_players();

    init_pieces();
    
    init_player_order();

    int i = 0;
    while ( 1 )                   // Circulating the player order array until all the players win. | Switch-case is better for scalabilty and readability than a nested if-else
    {
        switch (i % 4)
        {
            case 0:
                player_chance(0);
                break;
            case 1:
                player_chance(1);
                break;
            case 2:
                player_chance(2);
                break;
            case 3:
                player_chance(3);
                break;
        }
        
        i += 1;
        round += 1;
        printf("Round: %d\n", round);

        if (round == 10) break;
    }
}
