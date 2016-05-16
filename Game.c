/*
Ashutosh Verma - ashutoshvrm8@gmail.com
Graphic Era University
2nd year mini project
https://www.codechef.com/users/the_wolverine
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>/*HEADER FILE FOR SETTING UP THE COLOURS FOR TEXT*/
#include<time.h>/*HEADER FILE FOR THE SEEDING OF RANDOM NUMBER GENERATOR*/

#define bg_col 16/*BACKGROUND COLOR*/
#define col1 10/*COLOR 1*/
#define col2 9/*COLOR 2*/
#define col3 11/*COLOR 3*/
#define col4 12/*COLOR 4*/

int ch,i,j,k,n,z=0,x=0,y,freq[40][4],user[40][4],comp[40][4];

void welcome()/*FUNCTION TO WELCOME THE PLAYER(s)*/
{
    set_col(col1,bg_col);
    printf("\n\n\n\t\t\t\tW E L C O M E");
    set_col(col4,bg_col);
    printf("\n\n\n\n\t\tP R E S S   E N T E R   T O   P R O C E E D ....");
    getchar();
    printf("\n\n");
    system("cls");
}

int get_data()/*FUNCTION TO INPUT THE NUMBER OF STICKS*/
{
    int s;
    set_col(col1,bg_col);
    printf("\n\n\n\n\t     Enter the number of sticks between 20 and 40 : ");
    set_col(col3,bg_col);
    scanf("%d", &s);
    if(s>=20 && s<=40)
        return s;
    else
    {
        set_col(col4,bg_col);
        printf("\n\n\n\t\t\t\tT R Y   A G A I N  . . . \n\n\n\n");
        exit(0);
    }
}

void set_col(int ForgC, int BackC)/*FUNCTION TO SET INTERFACE COLOUR*/
{
    WORD wColor =((BackC)<<5) + (ForgC);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
    return;
}

int select_sticks(int sticks)/*FUNCTION TO GENERATE AND SELECT A RANDOM NUMBER ON BEHALF OF COMPUTER PLAYING RANDOMLY*/
{
    int pick=0;
    srand(time(NULL));/*SEEDING OF RANDOM NUMBER GENERATOR*/
    if(sticks>3)
        pick=rand() % 4;
    else if(sticks==3)
        pick=rand() % 3;
    else
        pick=1;
    if(pick==0)
        pick++;
    return pick;
}

void player_vs_player(int sticks)/*FUNCTION FOR CALCULATIONS TO BE MADE IN CASE OF PLAYER VERSUS PLAYER*/
{
    int k=2,pick=0;
    printf("\n\nSticks : %d\n\n", sticks);
    while(sticks>=1)
    {
        if(k%2==0)
        {
            printf("\nEnter the number of sticks you want to pick between 1 to 3 : ");
            scanf("%d", &pick);
            if(pick>=1 && pick<=3)
            {
                sticks-=pick;
                printf("\nPlayer 1 picks %d, %d remains\n",pick,sticks);
            }
            if(sticks==1)
            {
                printf("\nPlayer 1 wins\n");
                exit(0);
            }
        }
        else
        {
            printf("\nEnter the number of sticks you want to pick between 1 to 3 : ");
            scanf("%d", &pick);
            if(pick>=1 && pick<=3)
            {
                sticks-=pick;
                printf("\nPlayer 2 picks %d, %d remains\n",pick,sticks);
            }
            if(sticks==1)
            {
                printf("\nPlayer 2 wins\n");
                exit(0);
            }
        }
        k++;
    }
}

void player_vs_computer()/*FUNCTION FOR CALCULATIONS TO BE MADE IN CASE OF PLAYER VERSUS COMUPER*/
{
    int k=2,pick=0,sticks,game_counter,gc=1,p,q,i,temp1,temp2,temp3;

    set_col(col1,bg_col);
    printf("\nEnter the number of games you want to play : ");
    set_col(col3,bg_col);
    scanf("%d", &game_counter);

    while(game_counter--)
    {
        printf("\n\n\n\t\t\t\tG A M E : %d", gc);
        gc++;
        sticks=get_data();

        for(i=0;i<40;i++)
        {
            for(j=1;j<4;j++)
            {
                user[i][j]=comp[i][j]=0;
            }
        }

        printf("\n\nSticks : %d\n\n", sticks);

        while(1)
        {
            if(k%2==0)
            {
                printf("\nEnter the number of sticks you want to pick between 1 to 3 : ");
                scanf("%d", &pick);

                for(i=2;i<40;i++)
                {
                    if(sticks==i)
                    {
                        user[i-1][pick]=pick;
                        break;
                    }
                }

                if(pick>=1 && pick<=3)
                {
                    sticks-=pick;
                    printf("\nYou pick %d, %d remains\n",pick,sticks);
                }

                if(sticks==1)
                {
                    for(i=0;i<40;i++)
                    {
                        for(j=1;j<4;j++)
                        {
                            if(user[i][j]>0)
                                freq[i][j]=freq[i][j]+1;
                            if(comp[i][j]>0)
                                freq[i][j]=freq[i][j]-1;
                        }
                    }
                    printf("\nYou win\n");
                    Sleep(1000);
                    system("cls");
                    break;
                }
            }

            else
            {
                for(i=2;i<40;i++)
                {
                    if(sticks==i)
                    {
                        if(freq[i-1][1]>freq[i-1][2] && freq[i-1][1]>freq[i-1][3])
                            pick=1;
                        else if(freq[i-1][2]>freq[i-1][1] && freq[i-1][2]>freq[i-1][3])
                            pick=2;
                        else if(freq[i-1][3]>freq[i-1][1] && freq[i-1][3]>freq[i-1][2])
                            pick=3;
                        else
                            pick=select_sticks(sticks);
                    }
                }

                for(i=2;i<40;i++)
                {
                    if(sticks==i)
                    {
                        comp[i-1][pick]=pick;
                        break;
                    }
                }

                sticks-=pick;
                printf("\nComputer picks %d, %d remains\n",pick,sticks);
            }

            if(sticks==1)
            {
                for(i=0;i<40;i++)
                {
                    for(j=1;j<4;j++)
                    {
                        if(comp[i][j]>0)
                            freq[i][j]=freq[i][j]+1;
                    }
                }
                printf("\nComputer wins\n");
                /*Sleep(1000);
                system("cls");*/
                printf("\n\n\n\n\n\n");
                break;
            }
            k++;
        }

        /*for(i=0;i<40;i++)
        {
            for(j=0;j<4;j++)
            {
                printf("%d  ", freq[i][j]);
            }
            printf("\n");*/
        }
    }
}

int main()
{
    int pick,sticks=0,choice,r=1;

    for(i=0;i<40;i++)
    {
        for(j=0;j<4;j++)
        {
            freq[i][j]=user[i][j]=comp[i][j]=0;
        }
    }

    for(i=0;i<40;i++)
    {
        freq[i][0]=user[i][0]=comp[i][0]=r;
        r++;
    }

    welcome();

    set_col(col1,bg_col);
    system("cls");

    printf("\n1. Player 1 vs. Computer");
    printf("\n\n2. Player 1 vs. player 2");
    printf("\n\n3. Exit");

    set_col(col4,bg_col);

    printf("\n\n\n\n\t\t\tEnter your choice from the menu : ");

    set_col(col3,bg_col);

    scanf("%d", &choice);

    system("cls");

    switch(choice)/*INPUT INTERFACE FOR THE USER*/
    {
        case 1:
            player_vs_computer();
            break;

        case 2:
            sticks=get_data();
            player_vs_player(sticks);
            break;

        case 3:
            exit(0);
            break;

        default:
            set_col(col4,bg_col);
            printf("\n\n\n\n\n\t\t\tINVALID CHOICE, TRY AGAIN . . .\n\n\n\n");
    }
    return 0;
}
