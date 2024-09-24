#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//declare functions
void header();
int playerTurn(int ships, int numIndex, int letterIndex, char array[5][5], char arrayDos[5][5]);
int computerTurn(int ships, int numIndex, int letterIndex,char array[5][5]);
int processRowInput(char userInput[3]);
int processColInput(char userInput[3], int letterIndex);
void displayBoards(int numIndex, int letterIndex, char array[5][5],char arrayDos[5][5]);
void setBoard(char array[5][5]);

//main game function
int main()
{
    //initalize necessary variables
    char targetBoard[5][5];
    char oceanBoard[5][5];
    char computerBoard[5][5];
    char userInput[10];
    int numIndex;
    int letterIndex;
    int playerShips = 5;
    int computerShips = 5;
    int prevNumIndex, prevLetIndex;

    //print header
    header();

    //loop through rows
    for(numIndex = 0; numIndex < 5; numIndex++)
    {
        //loop through columns
        for(letterIndex = 0; letterIndex < 5; letterIndex++)
        {
            //set each position to the period
            targetBoard[numIndex][letterIndex] = '.';
            oceanBoard[numIndex][letterIndex] = '.';
            computerBoard[numIndex][letterIndex] = '.';
        }
    }

    //set computer board
    setBoard(computerBoard);
    //display boards
    displayBoards(numIndex, letterIndex, targetBoard, oceanBoard);

    //set first ship cords
    cout<<"\nWhere do you want to place ship 1? (Coordinates: 0-4 A-E):";
    //don't put space or it won't work ex:a0
    cin.getline(userInput,3);
    numIndex = processRowInput(userInput);
    letterIndex = processColInput(userInput, letterIndex);
    //make sure cords are in bounfd
    while(numIndex > 4 || letterIndex < 0)
    {
        //ask for cords again if out of bounds
        cout<<"Out of bounds. Where do you want to place ship 1? (Coordinates: 0-4 A-E):";
        cin.getline(userInput,3);
        numIndex = processRowInput(userInput);
        letterIndex = processColInput(userInput, letterIndex);
    }
    //set index to ship spot
    oceanBoard[numIndex][letterIndex] = '+';
    //prevent repeats
    prevNumIndex = numIndex;
    prevLetIndex = letterIndex;

    
    //set second ship cords
    cout<<"Where do you want to place ship 2? (Coordinates: 0-4 A-E):";
    //don't put space or it won't work ex:a0
    cin.getline(userInput,3);
    numIndex = processRowInput(userInput);
    letterIndex = processColInput(userInput, letterIndex);
    //check for bounds and repetitioj
    while(numIndex > 4 || letterIndex < 0 || (numIndex == prevNumIndex && letterIndex == prevLetIndex))
    {
        //reset
        if(numIndex > 4 || letterIndex < 0)
        {
            cout<<"Out of bounds. Where do you want to place ship 2? (Coordinates: 0-4 A-E):";
        }
        else
        {
            cout<<"Already used. Where do you want to place ship 2? (Coordinates: 0-4 A-E):";
        }
        cin.getline(userInput,3);
        numIndex = processRowInput(userInput);
        letterIndex = processColInput(userInput, letterIndex);
    }
    //set ship
    oceanBoard[numIndex][letterIndex] = '+';
    //update repetiton
    prevNumIndex = numIndex;
    prevLetIndex = letterIndex;


    //same as previous logics
    cout<<"Where do you want to place ship 3? (Coordinates: 0-4 A-E):";
    //don't put space or it won't work ex:a0
    cin.getline(userInput,3);
    numIndex = processRowInput(userInput);
    letterIndex = processColInput(userInput, letterIndex);
    while(numIndex > 4 || letterIndex < 0 || (numIndex == prevNumIndex && letterIndex == prevLetIndex))
    {
        if(numIndex > 4 || letterIndex < 0)
        {
            cout<<"Out of bounds. Where do you want to place ship 3? (Coordinates: 0-4 A-E):";
        }
        else
        {
            cout<<"Already used. Where do you want to place ship 3? (Coordinates: 0-4 A-E):";
        }
        cin.getline(userInput,3);
        numIndex = processRowInput(userInput);
        letterIndex = processColInput(userInput, letterIndex);
    }
    oceanBoard[numIndex][letterIndex] = '+';
    prevNumIndex = numIndex;
    prevLetIndex = letterIndex;


    //same as previous logics
    cout<<"Where do you want to place ship 4? (Coordinates: 0-4 A-E):";
    //don't put space or it won't work ex:a0
    cin.getline(userInput,3);
    numIndex = processRowInput(userInput);
    letterIndex = processColInput(userInput, letterIndex);
    while(numIndex > 4 || letterIndex < 0 || (numIndex == prevNumIndex && letterIndex == prevLetIndex))
    {
        if(numIndex > 4 || letterIndex < 0)
        {
            cout<<"Out of bounds. Where do you want to place ship 4? (Coordinates: 0-4 A-E):";
        }
        else
        {
            cout<<"Already used. Where do you want to place ship 4? (Coordinates: 0-4 A-E):";
        }
        cin.getline(userInput,3);
        numIndex = processRowInput(userInput);
        letterIndex = processColInput(userInput, letterIndex);
    }
    oceanBoard[numIndex][letterIndex] = '+';
    prevNumIndex = numIndex;
    prevLetIndex = letterIndex;

    //same as previous logics
    cout<<"Where do you want to place ship 5? (Coordinates: 0-4 A-E):";\
    //don't put space or it won't work ex:a0
    cin.getline(userInput,3);
    numIndex = processRowInput(userInput);
    letterIndex = processColInput(userInput, letterIndex);
    while(numIndex > 4 || letterIndex < 0 || (numIndex == prevNumIndex && letterIndex == prevLetIndex))
    {
        if(numIndex > 4 || letterIndex < 0)
        {
            cout<<"Out of bounds. Where do you want to place ship 5? (Coordinates: 0-4 A-E):";
        }
        else
        {
            cout<<"Already used. Where do you want to place ship 5? (Coordinates: 0-4 A-E):";
        }
        cin.getline(userInput,3);
        numIndex = processRowInput(userInput);
        letterIndex = processColInput(userInput, letterIndex);
    }
    oceanBoard[numIndex][letterIndex] = '+';


    //start game
    cout<<"\n\nStart game!\n";

    //display boards
    displayBoards(numIndex, letterIndex, targetBoard, oceanBoard);


    //continue playing til someone has 0 live ships
    while(playerShips != 0 || computerShips != 0)
    {
        //holds payer turn
        computerShips = playerTurn(computerShips, numIndex, letterIndex,targetBoard, computerBoard);
        //kills if computer ships are all dead
        if(computerShips = 0)
        {
            //indicate win
            cout<<"You Win! You hit all of the computer ships.";
            return 0;
        }
        //does computer turn
        playerShips =computerTurn(playerShips, numIndex,letterIndex,oceanBoard);
        //display after each round
        displayBoards(numIndex, letterIndex, targetBoard, oceanBoard);
    }
    
    //indicate loss
    cout<<"You lost. The computer hit all your ships.";       

    //return 0
    return 0;
    
}


//header function
void header()
{
    //output header
    cout<<"Battleship Game\n";
    cout<<"—---------------\n\n";
}

//this function handles the player turn
int playerTurn(int computerShips, int numIndex, int letterIndex, char targetBoard[5][5], char computerBoard[5][5])
{
    char hitInput[3];

    //takes input don't put space between characters or it won't work...I couldn't figure that out
    cout<<"Where do you want to hit? (Coordinates: 0-4 A-E): ";
    cin.getline(hitInput,3);
    //functions to convert user characters to index numbers
    numIndex = processRowInput(hitInput);
    letterIndex = processColInput(hitInput, letterIndex);

    //signal for a hit
    if(computerBoard[numIndex][letterIndex] == '+')
    {
        //mark a hit and update the target board
        cout<<"\n\nYou guessed "<<hitInput[0]<<' '<<hitInput[1]<<"...You hit!\n\n";
        targetBoard[numIndex][letterIndex] = 'X';
        computerShips = computerShips - 1;
    }
    else
    {
        //mark miss and update target board
        cout<<"\n\nYou guessed "<<hitInput[0]<<' '<<hitInput[1]<<"...You missed.\n\n";
        targetBoard[numIndex][letterIndex] = 'O';
    }

    //returns total living ships
    return computerShips;
}

//this function controls the computers turn
int computerTurn(int playerShips, int numIndex, int letterIndex,char oceanBoard[5][5])
{
    //initalize varianles
    char outputLet;

    //get random guess
    numIndex = rand() % 5;
    letterIndex = rand() % 5;

    //computer turn header
    cout<<"Computer's Turn\n";

    //make sure computer guess is unused
    while(oceanBoard[numIndex][letterIndex] == 'X' || oceanBoard[numIndex][letterIndex] == 'O')
    {
        //try again if it is
        numIndex =  rand() % 5;
        letterIndex = rand() % 5;
    }

    //number to letter conversions
    if(letterIndex == 0)
    {
        outputLet = 'A';
    }
    else if(letterIndex == 1)
    {
        outputLet = 'B';
    }
    else if(letterIndex == 2)
    {
        outputLet = 'C';
    }
    else if(letterIndex == 3)
    {
        outputLet = 'D';
    }
    else
    {
        outputLet = 'E';
    }

    //calculate for hit
    if(oceanBoard[numIndex][letterIndex] == '+')
    {
        //output hit
        cout<<"The Computer guessed "<<numIndex<<' '<<outputLet<<"...they hit you.\n\n";
        oceanBoard[numIndex][letterIndex] = 'X';
        //update lve player ships
        playerShips = playerShips - 1;
    }
    else
    {
        //output miss
        cout<<"The Computer guessed "<<numIndex<<' '<<outputLet<<"...They missed.\n\n";
        oceanBoard[numIndex][letterIndex] = 'O';
    }
    
    //return total live player ships
    return playerShips;
}

//process char number input
int processRowInput(char userInput[3])
{
    //return ascii math
    return userInput[0] - '0';
}

//processes letter out put
int processColInput(char userInput[3], int letterIndex)
{
    //set index
    int index = 1;
    
        //check index
        if(index == 1)
        {
            //set number according to letter
            if(userInput[index] == 'A'|| userInput[index] == 'a')
            {
                return 0;
            }
            else if(userInput[index] == 'B'|| userInput[index] == 'b')
            {
                return 1;
            }
            else if(userInput[index] == 'C'|| userInput[index] == 'c')
            {
                return 2;
            }
            else if(userInput[index] == 'D'|| userInput[index] == 'd')
            {
                return 3;
            }
            else if(userInput[index] == 'E' || userInput[index] == 'e')
            {
                return 4;
            }
        }
    //return -1 if number isn't in bounds
    return -1;
}

void displayBoards(int numIndex, int letterIndex, char targetBoard[5][5],char oceanBoard[5][5])
{
    //display board title
    cout<<"Target Board\n  A B C D E\n";
    //loop through rows
    for(numIndex = 0; numIndex < 5; numIndex++)
    {
        //print space
        cout<<numIndex<<' ';
        //loop through columns
        for(letterIndex = 0; letterIndex < 5; letterIndex++)
        {
            //print current index and spacing
            cout<<targetBoard[numIndex][letterIndex]<<" ";
        }
        //new row
        cout<<'\n';
    }
    
    //display board title
     cout<<"\n\nOcean Board\n  A B C D E\n";
     //loop through rows
    for(numIndex = 0; numIndex < 5; numIndex++)
    {
        //print space
        cout<<numIndex<<' ';
        //loop through columns
        for(letterIndex = 0; letterIndex < 5; letterIndex++)
        {
            //print current index and spacing
            cout<<oceanBoard[numIndex][letterIndex]<<' ';
        }
        //new row
        cout<<'\n';
    }
    //print end line
    cout<<"\n";
}

void setBoard(char computerBoard[5][5])
{
    //initialize ships and indexes
    int numIndex = rand() % 5;
    int letIndex = rand() % 5;
    int neededShips = 5;

    //make enough ship positions
    while(neededShips != 0)
    {
        //prevents copies
        while(computerBoard[numIndex][letIndex] == '+')
        {
            //redoes indexes if they're a copy
            numIndex = rand() % 5;
            letIndex = rand() % 5;
        }
        //marks ship spot
        computerBoard[numIndex][letIndex] = '+';
        //updates ship amount
        neededShips= neededShips - 1;

    }

}