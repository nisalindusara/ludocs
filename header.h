#ifndef HEADER_H
#define HEADER_H

// Include necessary standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Declarations

// Structure declaration
typedef struct
{
    char piece_name[4];
    char owner[7]; 
    short on_base;
    short on_cells;
    short on_home;
    int position;
    short direction;    //1 for clockwise, 0 for counter-clockwise
} Piece;

typedef struct
{
    char player_name[7];
    short pieces_in_base;
    short pieces_in_std_cells;
    short pieces_in_colored_cells;
    short pieces_in_home;
    short roll_value;
    Piece player_pieces[4];
} Player;

typedef struct
{
    short squareID;
    char type[15];
    int state;
} Cell;

// Enum declarations
enum cell_state
{
    EMPTY,
    OCCUPIED
};

enum cell_type
{
    NORMAL,
    MYSTERY
};

enum direction
{
    DIR_NONE,
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

// Array declarations
Player player_order[4];
Piece green_pieces[4], yellow_pieces[4], blue_pieces[4], red_pieces[4];
Cell cells[52];
// Array containing pointers, which points to another array with data type of Piece

// Shared function declarations
int die_roll();
void init_players();
void init_pieces();
void create_cells();
void init_player_order();
void player_chance(short index);

#endif // HEADER_H
