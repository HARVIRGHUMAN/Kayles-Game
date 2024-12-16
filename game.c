#include <stdio.h>
#include "ansi-colors.h" // string color

int getInt(char prompt[], int min, int max);
void fillBoard(char arr[], int len);
void printBoard(char arr[], int len);
int allPinsKnocked(char arr[], int len);
int knockOver(char arr[],int len, int pin, int amtToKnock);

int main()
{
    // display game rules for user
    printf("                        Kayles \n\n");    
    printf("To start the game input the number of pins to play with.(2-30)\n"); 
    printf("Then you will get to choose between knocking down 1 pin or 2 pins.\n");
    printf("You can only knockdown 2 pins that are adjacent to eachother. \n");
    printf("A player wins by leaving their opponent without any pins to knock over.\n\n");
    
    // Prompt user for number of pins, from 3-30
    int pinAmt = getInt("Enter the number of pins", 3, 30);
    printf("\n");

    // Create pins
    char board[pinAmt];

    // Fill board in order with pins as | with pinAmt.
    fillBoard(board, pinAmt);

    // Print pins
    printBoard(board, pinAmt);

    int gameOver = 0;
    int playerTurn = 1;
    while (!gameOver)
    {
        //print player # to show whos turn it is
        if(playerTurn == 1)
        {
            printf("%sPlayer %d's turn\n", BLU, playerTurn);
        }
        else if(playerTurn == 2)
        {
            printf("%sPlayer %d's turn\n", RED, playerTurn);
        }
        
        // Ask user for amount to remove
        int amtToRemove = getInt("Knock over 1 or 2 pins", 1, 2);
        // ask user which pin to remove
        int pinToRemove = getInt("Choose pin to knock down", 1, pinAmt);
        printf("\n");
        // Knock over pins with error checking
        if (!knockOver(board, pinAmt, pinToRemove, amtToRemove))
        {
             printf("Try again.\n\n");
            continue;
        }
        
        // Print the board
        printBoard(board, pinAmt);
        
        // Check to see if the game is over
        gameOver = allPinsKnocked(board, pinAmt);
        //display player who one
        if (gameOver)
        {
            printf("%sPlayer %d wins!\n", BHMAG, playerTurn);
        }
        //change to other player turn
        else
        {
            playerTurn = (playerTurn == 1) ? 2 : 1;
        } 
    }
}


// getint function with error checking
int getInt(char prompt[], int min, int max)
{
    int input = 0;
    int result;
    do
    {
        printf("%s: ", prompt);
        scanf("%d", &input);
        
        if (input < min || input > max)
        {
            printf("Value must be in the range of %d-%d\n", min, max);
        }
    } 
    while (input < min || input > max);
    return input;  
}

// Fill array with '|' as pins
void fillBoard(char arr[], int len)
{
    for(int i=0; i < len; i++)
    {
        arr[i] = '|';
    }

}

// Display the array
void printBoard(char arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s%3c ", BLK, arr[i]);
    }
    printf("\n");
    for(int i=0; i < len; i++)
    {
        printf("%3d ", i+1);
    }
    printf("\n\n");
}

// check if all pins are knocked
int allPinsKnocked(char arr[], int len)
{
    for(int i=0; i < len; i++)
    {
        if(arr[i] == '|')
        {
            return 0;
        }
    }
    return 1;
}

// knockover pin function with error checking for adjacent pin returns boolean
int knockOver(char arr[],int len, int pin, int amtToKnock)
{
    if(arr[pin - 1] != '|')
    {
        return 0;
    }

    arr[pin - 1] = 'X';

    if(amtToKnock == 2)
    {
        int secondPin = 0;
        if(pin < len && arr[pin] == '|')
        {
            secondPin = pin + 1;
        }
        else if (pin > 1 && arr[pin -2] == '|')
        {
            secondPin = pin - 1;
        }
        if (secondPin != 0)
        {
            arr[secondPin - 1] = 'X';
        }
        else
        {
            printf("Invalid move second pin is not adjacent and standing.\n");
            arr[pin - 1] = '|';
            return 0;
        }
    }
    return 1;
}


