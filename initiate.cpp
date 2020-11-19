/*
Made by: Udit Kapoor
Run this file before the first time you play a game.

Enter the path to the common network folder which can be accessed by both players
and where the game file would be saved.
*/

#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

int main()
{
    ofstream ofile;
    ofile.open("path.txt");
    
    char path[256];
    cout<<"Enter path to the folder: ";
    cin.getline(path, sizeof(path));
    cout<<"\nPath entered successfully: "<<path;
    
    ofile<<path;
    
    ofile.flush();
    ofile.close();
    
    return 0;
}