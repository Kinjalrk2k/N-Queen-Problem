#include <iostream>
#include <windows.h>

#define N 8

using namespace std;

//  windows handles
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)   //  standard gotoxy function with winAPI
{	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

void print_board(int board[N][N], int x, int y) //  damn stupid print function, beutifies stuffs :*
{
    int s_x = x, s_y = y;

    //  top capping row
    gotoxy(x, y);   cout<<char(218);
    for(int i=0; i<N; i++)
        cout<<char(196)<<char(196)<<char(196)<<char(194);
    cout<<"\b"<<char(191);

    //  intermediate rows
    for(int i=0; i<N-1; i++){
        gotoxy(x, ++y);
        for(int j=0; j<N; j++)
            cout<<char(179)<<"   ";
        cout<<char(179);

        gotoxy(x, ++y);
        cout<<char(195);
        for(int j=0; j<N-1; j++)
            cout<<char(196)<<char(196)<<char(196)<<char(197);
        cout<<char(196)<<char(196)<<char(196)<<char(180);
    }

    //  bottom but row
    gotoxy(x, ++y);
    for(int j=0; j<N; j++)
        cout<<char(179)<<"   ";
    cout<<char(179);

    //  bottom capping row
    gotoxy(x, ++y); cout<<char(192);
    for(int i=0; i<N; i++)
        cout<<char(196)<<char(196)<<char(196)<<char(193);
    cout<<"\b"<<char(217);

    //  printing board
    x = s_x;    y = s_y;
    gotoxy(x+=2, y++);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            gotoxy(x, y);   
            if(board[i][j] == 0)
                cout<<" ";  //  empty
            else if(board[i][j] == 1)
                cout<<char(234);    //  Queen is here! Long live the Queen

            x+=4;
        }
        y+=2;
        x = s_x+2;
    }
    gotoxy(x, y);
}

//  check whether inserting queen at (r,c) is valid or not
bool chk_safe(int board[N][N], int r, int c){
    for(int i = 0; i < c; i++) //   checking left rows
        if (board[r][i] == 1)   //  queen already present
            return false; 

    for(int i=r, j=c; i>=0 && j>=0; i--, j--) //    checking left top diagonal
        if (board[i][j] == 1) 
            return false; 

    for(int i=r, j=c; j>=0 && i<N; i++, j--) // checking right left diagonal
        if (board[i][j] == 1) 
            return false; 
  
    return true; 
}

//  solves the NQueen Problem... Like a Boss >_<
bool NQueenProb(int board[N][N], int col) 
{ 
    if (col >= N) //    if all queens are filled
        return true; // your work is done lil champ!

    for (int i = 0; i < N; i++)     //  iterate over the all the rows
    { 
        if ( chk_safe(board, i, col) )  //  checking for safe position
        { 
            board[i][col] = 1;  //  dummy setting a safe position as queen
  
            if ( NQueenProb(board, col + 1) ) //    recur to the next coloumn
                return true; 
            board[i][col] = 0;  //  if conditions not satisfied, unset the previous location, hence backtrack
        } 
    } 
    return false;  //   triggers backtrack
} 

/*  main    */
int main(int argc, char const *argv[])
{
    int board[N][N] = {0};  //  seeds an empty chessboard

    if(NQueenProb(board, 0))    //  if solution found(hence, solves it)
        print_board(board, 0, 0);
    else    //  sorry homie! its not your day :(
        cout<<"Solution not found!";    //  never saw you come here tho :)

    return 0;
}
