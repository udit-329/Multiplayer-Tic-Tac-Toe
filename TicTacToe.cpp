/*
Made by: Udit Kapoor
Run this to play the game AFTER running initiate.cpp

First player to join the game is player 1 and is 'X'.
Second player is 'O'.

Controls:
WASD or arrow keys to select position
Enter to confirm your move
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>

using namespace std;

string path;
string full_path;

//Class for data storage
class gameClass {
    public:
    int player1;
    int player2;

    //Stores the player number whose turn it is
    int currentTurn;
    //2D array to keep track of which boxes are filled
    int place[3][3];
    gameClass() {
        player1 = 0;
        player2 = 0;
        currentTurn = 1;
        // 0 - empty, 1 - player1, 2 - player2
        int place[3][3] = {0,0,0,0,0,0,0,0,0};
    }
    void reset() {
        player1 = 0;
        player2 = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                place[i][j] = 0;
            }
        }
    }
};

//GOTOXY - go to coordinates x, y
void gotoxy(int x, int y) {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

//returns player number if someone has won on the board, 0 if still playing
int checkWin() {

    gameClass checkWinner;
    ifstream ifile;
    ifile.open(full_path);
    ifile.read((char*)&checkWinner, sizeof(checkWinner));
    ifile.close();

	int p1,p2,p3,p4,p5,p6,p7,p8,p9;

	p1 = checkWinner.place[0][0];
	p2 = checkWinner.place[0][1];
	p3 = checkWinner.place[0][2];
	p4 = checkWinner.place[1][0];
	p5 = checkWinner.place[1][1];
	p6 = checkWinner.place[1][2];
	p7 = checkWinner.place[2][0];
	p8 = checkWinner.place[2][1];
	p9 = checkWinner.place[2][2];
    
	if(p1 == p2 && p2 == p3)
	    return p1;
	else if(p4 == p5 && p5 == p6)
	    return p4;
	else if(p7 == p8 && p8 == p9)
	    return p7;
	else if(p1 == p4 && p4 == p7)
	    return p1;
	else if(p2 == p5 && p5 == p8)
	    return p2;
	else if(p3 == p6 && p6 == p9)
	    return p3;
	else if(p1 == p5 && p5 == p9)
	    return p1;
	else if(p3 == p5 && p5 == p7)
	    return p3;
	else
	    return 0;
	}

//check if the player number entered has the current turn (1) or not (0)
int checkCorrectPlayer(int playerNum) {
    gameClass checkPlayer;

    ifstream ifile; 
    ifile.open(full_path);
    ifile.read((char*)&checkPlayer, sizeof(checkPlayer));
    ifile.close();

    if(playerNum == checkPlayer.currentTurn)
        return 1;
    else
        return 0;
}

//Function to prevent overwriting, returns 1 if the location is empty
int isValid(int x, int y) {
	int Xcoor=(x-2)/5;
	int Ycoor=(y-5)/2;

    gameClass checkPlace;

    ifstream ifile; 
    ifile.open(full_path);
    ifile.read((char*)&checkPlace, sizeof(checkPlace));
    ifile.close();

	if(checkPlace.place[Xcoor][Ycoor] == 0) {
        
	    return 1;
    }
	else
	    return 0;
}

//returns the current turn's player number and changes to other player in the data file
int managePlayerTurn() {
    gameClass checkPlayer;

    ifstream ifile;
    ifile.open(full_path);
    ifile.read((char*)&checkPlayer, sizeof(checkPlayer));
    ifile.close();

    int returnVal;

    if(checkPlayer.currentTurn == 1) {
        checkPlayer.currentTurn = 2;
        returnVal = 1;
    }
    else if(checkPlayer.currentTurn == 2) {
        checkPlayer.currentTurn = 1;
        returnVal = 2;
    }

    ofstream ofile;
    ofile.open(full_path);
    ofile.write((char*)&checkPlayer, sizeof(checkPlayer));
    ofile.close();

    return returnVal;
}

void play(int x, int y) {
    gameClass playGame;

    ifstream ifile;
    ifile.open(full_path);
    ifile.read((char*)&playGame, sizeof(playGame));
    ifile.close();

    int Xcoor = (x-2)/5;
	int Ycoor = (y-5)/2;

    int playerTurn = managePlayerTurn();
    if(playerTurn == 1)
        playGame.currentTurn = 2;
    else if(playerTurn == 2)
        playGame.currentTurn = 1;

    char playVal;
    if(playerTurn == 1) {
        playVal = 'X';
        playGame.place[Xcoor][Ycoor] = 1;
    }
    else if(playerTurn == 2) {
        playVal = 'O';
        playGame.place[Xcoor][Ycoor] = 2;
    }

    ofstream ofile;
    ofile.open(full_path);
    ofile.write((char*)&playGame, sizeof(playGame));
    ofile.close();

    gotoxy(x,y);
    cout<<playVal;
}

//returns 0 if all boxes are filled
int checkMovesLeft(int arr[3][3]) {

    int emptyCounter = 0;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(arr[i][j] == 0)
                emptyCounter++;
        }
    }
    if(emptyCounter != 0)
        return 1;
    else
        return 0;
}

//plays the game and determines the winner
void startGame(int playerNumber) {
    system("cls");
    gotoxy(3,3);
    cout<<"You are player "<<playerNumber<<"\n";
    gotoxy(3,4);
    cout<<"Player 1's turn";
    gotoxy(5,5);cout<<"   |   |   ";
	gotoxy(5,6);cout<<"-----------";
	gotoxy(5,7);cout<<"   |   |   ";
	gotoxy(5,8);cout<<"-----------";
	gotoxy(5,9);cout<<"   |   |   ";
    
    int x=6,y=5;
    gotoxy(x,y);
    
    gameClass display;

    int placeLocal[3][3] = {0,0,0,0,0,0,0,0};
    int turnCounter = 0;
    while(checkWin() == 0 && turnCounter < 9) {
        ifstream ifile;
        ifile.open(full_path);
        ifile.read((char*)&display, sizeof(display));
        ifile.close();

        int co = 0;
    
        while(display.currentTurn != playerNumber || co) {
            
            co = 1;

            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(placeLocal[i][j] != display.place[i][j]) {
                        co = 0;
                        placeLocal[i][j] = display.place[i][j];
                        int Xplace = (4 * i) + 6;
                        int Yplace = (2 * j) + 5;
                        gotoxy(Xplace, Yplace);
                        if(display.place[i][j] == 1)
                            cout<<'X';
                        else if(display.place[i][j] == 2)
                            cout<<'O';
                    }
                }
            }
            if(co == 0) {
                gotoxy(10,4);
                cout<<display.currentTurn;
                gotoxy(6,5);
            }
            ifstream turnfile1;          
            turnfile1.open(full_path);
            turnfile1.read((char*)&display, sizeof(display));
            turnfile1.close();

        }
        Sleep(500);
        //if the other player won in the current turn, exit the loop
        
        int test = checkWin();
        if(test != 0) {
            break;
        }
        else if(!checkMovesLeft(placeLocal)) {
            break;
        }
        while(display.currentTurn == playerNumber && checkWin() == 0) {
            //The code for arrow controls starts
            //ASCII numbers:
            //13=Enter,80=DownArrow,72=UpArrow,77=RightArrow,75=LeftArrow
            char mover = '0';
            while(mover != 13) {
        
                mover = getch(); 

                if(mover == 13 && !isValid(x,y)) {
                    mover++;
                }
            
                if(mover == 80 || mover == 's') {
                    y += 2;
                    if(y <= 9)
                        gotoxy(x,y);
                    else
                        y -= 2;
                }
                else if(mover == 72 || mover == 'w') {
                    y -= 2;
                    if(y >= 5)
                        gotoxy(x,y);
                    else
                        y += 2;
                }
                else if(mover == 77 || mover == 'd') {
                    x += 4;
                    if(x <= 14)
                        gotoxy(x,y);
                    else
                        x -= 4;
                }
                else if(mover == 75 || mover == 'a') {
                    x -= 4;
                    if(x >= 6)
                        gotoxy(x,y);
                    else
                        x += 4;
                }
                if(mover == 13 && checkCorrectPlayer(playerNumber)) {
                    play(x,y);
                }
                    
            }
            ifstream turnfile;
            turnfile.open(full_path);
            turnfile.read((char*)&display, sizeof(display));
            turnfile.close();
        }
        Sleep(500);
        turnCounter += 2;
    }
}

//Player stays in wait lobby until the second player joins, max wait time = 30 seconds
void waitLobby(int playerNumber) {
    system("cls");
    
    gotoxy(3,3);
    cout<<"waiting for the other player...\n";
    
    gameClass checkPlayer;
    
    int loop = 1;

    //If no one else joins for 30 seconds, we exit the game
    //This statement creates a value for time, 30 seconds into the future
    time_t endTime = time(NULL) + 30;

    while (loop) {
        
    ifstream ifile;
    ifile.open(full_path);
    ifile.read((char*)&checkPlayer, sizeof(checkPlayer));
    ifile.close();

    if (checkPlayer.player1 == 1 && checkPlayer.player2 == 1) 
        loop = 0;
    if (time(NULL) > endTime)
        loop = 0;
    }
    cout<<"\n\n Entering game...";
    
    Sleep(2000);

}

//player connects and obtains a player number before entering the lobby
int connect() {
    int playNumber = 0;

    //open an input stream, read data
    ifstream ifile;
    gameClass game;
    ifile.open(full_path);
    ifile.read((char*)&game, sizeof(game));
    ifile.close();

    //Assign a player number based on you being the first or second to start game
    if (game.player1 == 0) {
        playNumber = 1;
        game.player1 = 1;
    }
    else if (game.player2 == 0) {
        playNumber = 2;
        game.player2 = 1;
    }

    //Open output stream to write data
    ofstream ofile;
    ofile.open(full_path);
    ofile.write((char*)&game, sizeof(game));
    ofile.close();

    return playNumber;
}

//init runs first to take in path to common network folder and create a 'game file' there
int init() {

    //get the file path
    ifstream ifile;
    ifile.open("path.txt");
    getline(ifile, path);    
    ifile.close();

    full_path = path + "\\XandO.txt";
    
    //check if file exists
    ifstream test_file;
    test_file.open(full_path);
    if(test_file) {
        return 0;
    }

    //create game file at supplied location
    ofstream ofile;
    cout<<full_path;
    gameClass game;
    game.reset();
    ofile.open(full_path);
    ofile.write((char*)&game, sizeof(game));
    
    ofile.close();

    return 0;
}

int main() {
    init();
    
    //Connect with the file, assign a player number (1 or 2)
    int playerNumber = connect();

    //Join the wait lobby and wait for the other person to connect
    waitLobby(playerNumber);

    startGame(playerNumber);
    int winner = checkWin();

    if(winner == 0) {
        gotoxy(3, 15);
        cout<<"The game is a draw.";
    }
    else if(winner == playerNumber) {
        gotoxy(3,15);
        cout<<"You win!";
    }
    else {
        gotoxy(3,15);
        cout<<"You lose :(";
    }    
    
    //create char array of filepath
    int len = full_path.length();
    char path_array[len + 1];

    strcpy(path_array, full_path.c_str());
    //remove file in the end
    
    remove(path_array);
    
    getchar();
    
    return 0;
}