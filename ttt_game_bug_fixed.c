#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_WIDTH_HEIGHT 3
#define CR "\033[1;"
#define WB "\033[0;"

struct Player {
    char save_players;
};

char t_board[MAP_WIDTH_HEIGHT][MAP_WIDTH_HEIGHT] =
{
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' ',
};

void board(char t_board[MAP_WIDTH_HEIGHT][MAP_WIDTH_HEIGHT])
{
    srand(time(NULL));
    int color = (rand() % 6) + 31;

    printf("\n");
    for(int i = 0; i < MAP_WIDTH_HEIGHT; i++)
    {
        for(int j = 0; j < MAP_WIDTH_HEIGHT; j++)
        {
            printf(" %c ", t_board[i][j]);
            if(j <= 1)
                printf("%s%dm|%s0m", CR, color, CR);
        }
        printf("\n");
        if(i >= 0 && i != 2)
            printf("%s%dm-----------%s0m\n", CR, color, CR);
    }
}

char check_win(char t_board[MAP_WIDTH_HEIGHT][MAP_WIDTH_HEIGHT], char player)
{
    for(int i = 0; i < MAP_WIDTH_HEIGHT; i++) {
        if(t_board[i][0] == player && t_board[i][1] == player && t_board[i][2] == player) return 1;
        if(t_board[0][i] == player && t_board[1][i] == player && t_board[2][i] == player) return 1;
    }
    return 0;
}

char check_draw(char t_board[MAP_WIDTH_HEIGHT][MAP_WIDTH_HEIGHT])
{
    for(int i = 0; i < MAP_WIDTH_HEIGHT; i++) {
        for(int j = 0; j < MAP_WIDTH_HEIGHT; j++)
            if(t_board[i][j] == ' ') return 0;
    }

    return 1;
}

char* nomorGa(char* row, char* col)
{
    char *remaining;

    while(1) {
        strtol(row, &remaining, 0);
        if(*remaining != '\0')
        {
            while(getchar() != '\n');
            printf("\n%s31mItu bukan angka mas!%s0m\n", WB, WB);
            return 0;
        }
        else break;
    }

    while(1)
    {
        strtol(col, &remaining, 0);
        if(*remaining != '\0')
        {
            while(getchar() != '\n');
            printf("\n%s31mItu bukan angka tolol!%s0m\n", WB, WB);
            return 0;
        }
        else break;
    }
    return 1;
}

int main()
{
    struct Player* players = (struct Player *) malloc(sizeof(struct Player));

    char players_input[2];
    printf("Pilih player 1: ");
    scanf(" %2s", players_input);
    while(strlen(players_input) > 1 || strcasecmp(players_input, "O") != 0 && strcasecmp(players_input, "X") != 0)
    {
        while(getchar() != '\n');
        printf("\n%s31mYg bener kontol%s0m\nPilih player 1: ", WB, WB);
        scanf(" %2s", &players_input);
    }

    players->save_players = toupper(players_input[0]);

    printf("\nMaka player 2 adalah: %c\n",
           (players->save_players == 'X') ? 'O':'X');
    fflush(stdout);
    sleep(2);

    system("clear");

    /*int ch_players;
    for(int ch_players = 0; ch_players < 3; ch_players++)
    {
        players->save_players[ch_players] = (players->save_players[ch_players] == 'X') ? 'X':'O';
        players->save_players[ch_players] = (players->save_players[ch_players] == 'O') ? 'O': 'X';
    }*/

    int row,
        col;
    char restart[10],
         row_[10],
         col_[10];

    while(1)
    {
        board(t_board);
        printf("\nPlayer %s34m'%c'%s0m masukkan baris 1-3, dan kolom 1-3: ", WB, players->save_players, WB);
        scanf(" %9s %9s", row_, col_);

        while(!nomorGa(row_, col_)) {
            printf("\nPlayer %c masukkan baris 1-3, dan kolom 1-3: ", players->save_players);
            scanf(" %9s %9s", row_, col_);
        }

        while(getchar() != '\n'); //clear buffering input

        row = atoi(row_);
        col = atoi(col_);

        while(row <= 0 || row > 3 || col <= 0 || col > 3)
        {
            printf("\n%s35mHanya bisa 1-3 saja mas?%s0m\nPlayer %c masukkan baris 1-3, dan kolom 1-3: ",
                   WB, WB, players->save_players);
            scanf(" %9s %9s", row_, col_);

            while(!nomorGa(row_, col_)) {
                printf("\nPlayer %c masukkan baris 1-3, dan kolom 1-3: ", players->save_players);
                scanf(" %9s %9s", row_, col_);
            }

            while(getchar() != '\n');

            row = atoi(row_);
            col = atoi(col_);
        }

        while(t_board[row - 1][col - 1] != ' ')
        {
            printf("\n%s31mitu udah keisi!%s0m\nPlayer %c masukkan baris 1-3, dan kolom 1-3: ",
                   WB, WB, players->save_players);
            scanf(" %9s %9s", row_, col_);

            while(!nomorGa(row_, col_)) {
                printf("\nPlayer %c masukkan baris 1-3, dan kolom 1-3: ", players->save_players);
                scanf(" %9s %9s", row_, col_);
            }

            while(getchar() != '\n');

            row = atoi(row_);
            col = atoi(col_);
        }

        t_board[row - 1][col - 1] =  (players->save_players);

        if(check_win(t_board, players->save_players)) {
            system("clear");
            board(t_board);

            printf("\n%s32mANJAY %s33m'%c' %s32mMENANG COY!!!%s0m\n",
                   WB, CR, players->save_players, WB, WB);
            printf("\nWanna restart? ('t' for tidak): ");
            scanf(" %10s", &restart);

            if(strcmp(restart, "t") != 0)
            {
                for(int i = 0; i < MAP_WIDTH_HEIGHT; i++)
                    for(int j = 0; j < MAP_WIDTH_HEIGHT; j++)
                        t_board[i][j] = ' ';

                system("clear");
            }
        }

        if(check_draw(t_board)) {
            system("clear");
            board(t_board);

            printf("\n%s31mTie!%s0m\n",
                   WB, WB);
            printf("\nWanna restart? ('t' for tidak): ");
            scanf(" %10s", &restart);

            if(strcmp(restart, "t") != 0)
            {
                for(int i = 0; i < MAP_WIDTH_HEIGHT; i++)
                    for(int j = 0; j < MAP_WIDTH_HEIGHT; j++)
                        t_board[i][j] = ' ';

                system("clear");
            }
        }
        if(strcmp(restart, "t") == 0) break;

        players->save_players = (players->save_players == 'X') ? 'O':'X';
        system("clear");
    }

    printf("\n%s34mThank you bro, telah memainkan game watashi ini >.<%s0m\n",
           WB, WB);
    fflush(stdout);
    sleep(1);
    return 0;
}