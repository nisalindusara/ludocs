#include "header.h"

const char *player_colors[] = {"Green", "Yellow", "Blue", "Red"};     

int die_roll()
{
    int random_number = rand();
    return ( random_number % 6 ) + 1;
}

void init_players()
{
    do
    {
        for (int i = 0; i < 4; i++)
        {
            strcpy(player_order[i].player_name, player_colors[i]);
            player_order[i].pieces_in_base = 4;
            player_order[i].pieces_in_base = 0;
            player_order[i].pieces_in_base = 0;
            player_order[i].pieces_in_base = 0;
            player_order[i].roll_value = die_roll();
        }
    } 
    while (
        player_order[0].roll_value == player_order[1].roll_value &&     //checking if all the players have the same initial roll value and if so they all will be recreated with a re-roll
        player_order[0].roll_value == player_order[2].roll_value &&
        player_order[0].roll_value == player_order[3].roll_value
    );
    
    for (int i = 0; i < 4; i++)
    {
        printf("%s rolls %d\n", player_order[i].player_name, player_order[i].roll_value);
    }
}

void init_pieces()
{
    const char *piece_names[4][4] = {              
        {"G1", "G2", "G3", "G4"},
        {"Y1", "Y2", "Y3", "Y4"},
        {"B1", "B2", "B3", "B4"},
        {"R1", "R2", "R3", "R4"}
    };

    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            Piece *current_piece = &player_order[i].player_pieces[j]; 
            strcpy( current_piece -> piece_name, piece_names[i][j] );
            strcpy( current_piece -> owner, player_colors[i] );
            current_piece -> direction = DIR_NONE;
            current_piece -> on_base = 1;
            current_piece -> on_cells = 0;
            current_piece -> on_home = 0;
            current_piece -> position = 0;
        }
    }
}

void create_cells()
{
    for (int i = 0; i < 52; i++)
    {
        cells[i].squareID = i;
        cells[i].state = EMPTY;
        strcpy(cells[i].type, NORMAL);
    }
}

short highest_roll(Player order[])              // Pass by value because we don't do any modifications within the function
{
    Player temp;
    for(int i = 3; i > 0; i--)                  // Bubble sort to order the array in ascending order
    {
        for(int j = 0; j < i; j++)
        {
            if(order[j].roll_value > order[j+1].roll_value)
            {
                temp = order[j];
                order[j] = order[j+1];
                order[j+1] = temp;
            }
        }
    }
    if(order[3].roll_value == order[2].roll_value)            // Check if 2 players gets the same result 
    {
        printf("\n%s and %s both rolled the same value of %d and will re roll\n", order[3].player_name, order[2].player_name, order[3].roll_value);
        for(int i = 2; i < 4; i++)
        {
            order[i].roll_value = die_roll();
            printf("%s rolls %d\n", order[i].player_name, order[i].roll_value);
        }
        if (order[3].roll_value < order[2].roll_value)
        {
            temp = order[3];
            order[3] = order[2];
            order[2] = temp;
        }
    }
    if(order[3].roll_value == order[2].roll_value && order[2].roll_value == order[1].roll_value)        // Check if 3 players gets the same highest result
    {
        printf("%s, %s and %s rolled the same value of %d and will re roll\n", order[3].player_name, order[2].player_name, order[1].player_name, order[3].roll_value);
        for(int i = 1; i < 4; i++)
        {
            order[i].roll_value = die_roll();
            printf("%s rolls %d\n", order[i].player_name, order[i].roll_value);
        }

        for(int i = 2; i > 0; i--)                  // Bubble sort to order the last 3 players from previous order in the ascending order
        {
            for(int j = 0; j < i; j++)
            {
                if(order[j].roll_value > order[j+1].roll_value)
                {
                    temp = order[j];
                    order[j] = order[j+1];
                    order[j+1] = temp;
                }
            }
        }
    }

    printf("\n%s player has the highest roll and will begin the game.\n", order[3].player_name);
    
    for(int i = 0; i < 4; i++)
    {
        if(order[3].player_name == player_order[i].player_name)
        {
            return i;
        }
    }
}

void init_player_order()
{
    short highest_index = highest_roll(player_order);

    Player temp_order[4];       // Creates a temporary array

    for (int i = 0; i < 4; i++)         // Clockwise ordering from the highest roller
    {
        temp_order[i] = player_order[(highest_index + i) % 4];
        temp_order[i].roll_value = 0; // Reset roll value to 0
    }

    for (int i = 0; i < 4; i++)         // Copy the reordered list back to player_order
    {
        player_order[i] = temp_order[i];
    }
    printf("\nThe order of a single round is %s, %s, %s, and %s\n", player_order[0].player_name, player_order[1].player_name, player_order[2].player_name, player_order[3].player_name);
}

short piece_to_x(Player *plyr)
{
    if(plyr->roll_value == 6)
    {
        printf("The condition reahced\n");
        for (int i = 0; i < 4; i++)
        {
            if(plyr -> player_pieces[i].on_base == 1)
            {
                printf("The inner condidtion in being reached\n");
                plyr -> player_pieces[i].on_base = 0;
                plyr -> player_pieces[i].on_cells = 1;
                plyr -> player_pieces[i].position = 0;
                printf("The %s piece has been moved to x from base.\n", plyr-> player_pieces[i].piece_name);
                return 1;
            }
        }
        return 0;
    }
}

void red_player(short index)
{
    player_order[index].roll_value = 6;
    piece_to_x(&player_order[index]);
}

void player_chance(short index)
{
    if (strcmp(player_order[index].player_name, "Red") == 0)
    {
        printf("The Red player has the chance\n");
        red_player(index);
    }
    else if (strcmp(player_order[index].player_name, "Blue") == 0)
    {
        printf("The Blue player has the chance\n");
    }
    else if (strcmp(player_order[index].player_name, "Yellow") == 0)
    {
        printf("The Yellow player has the chance\n");
    }
    else if (strcmp(player_order[index].player_name, "Green") == 0)
    {
        printf("The Green player has the chance\n");
    }
}