#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include "doublelinklist.h"
#include "objects.h"

using namespace std;

int main() {
    // Create initial game state
    GameState game;
    game.create_init_state();

    // DFS stack to store the state of the game
    DoublyList<int> actionStack;
    DoublyList<int> objectStack;

    // Creating and initializing variables for actions and objects 
    int currentAction = 1; 
    int currentObject = 0; 

    //Seeding the rand() function to generate random number
    srand(0);

    // Perform DFS until winning state is achieved
    while (!game.win) {
        // Perform the action on the current object
        int effectID = game.advance(currentAction, currentObject);

        if (effectID == -1) {
            // Backtrack to the previous state
            actionStack.removeBack();
            objectStack.removeBack();

            // If the stack is not empty, retrieve the previous action and object
            if (actionStack.elemcount > 0) {
                currentAction = actionStack.get(actionStack.elemcount - 1);
                currentObject = objectStack.get(objectStack.elemcount - 1);

                // Revert the game state to the previous state
                game.advance(currentAction, currentObject);
            }
        }

        // If the game is won, break out of the loop
        if (game.win)
            break;

        // If the action was successful, push action and object onto the stack
        if (effectID > 0) {
            actionStack.addBack(currentAction);
            objectStack.addBack(currentObject);
        }

        currentAction = rand() % 5 + 1;
        currentObject = rand() % (game.rooms.get(game.room_id)->room_objects.elemcount);         
    }

    return 0;
}
