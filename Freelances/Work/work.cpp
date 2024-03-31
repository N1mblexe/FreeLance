#include <iostream>
#include <algorithm>
#include "feedback.cpp"

// Define a linked list node
struct node
{
    int digit;
    node* next;
};

int stringToInt(const std::string& str);
int list_length(node* head);

void Delete_node(node*& head, int digit);
void DeleteNodes(node* head);
void PrintResult(node** possible, node** impossible, int size);
void DeleteFromOthers(node** nodeArray, int nodePos, int value , int nodeSize);
void AddToOthers(node** nodeArray, int nodePos, int value , int nodeSize);

bool isGuessValid(string guess);
bool isPlayerWon(string feedback , node** imps);
bool NodeContains(node* head, int digit);
bool InsertNode(node*& head, int digit);

int main()
{
    // Initialize linked lists for each slot
    node* possibles[3] = { NULL, NULL, NULL }; // list of possible digits for each slot
    node* impossibles[3] = { NULL, NULL, NULL }; // list of impossible digits for each slot

    start:
    // Get game ID from user
    string sGame_id;
    cout << "Please enter a game ID." << endl;
    cin >> sGame_id;

    int game_id;
    try
    {
        game_id = stringToInt(sGame_id); // convert game ID string to integer
    }
    catch(exception e)
    {
        cout << "Invalid game id!!" << endl;
        goto start; // if exception is caught, restart game loop
    }

    // Game Loop
    while (true)
    {
        string guess;
        cout << "Enter your guess." << endl;
        cin >> guess;

        if(!isGuessValid(guess)) // check if guess is valid
        {
            cout << "Invalid guess. ";
            continue; // restart game loop if guess is invalid
        }

        string feedback = get_the_feedback(guess, game_id); // get feedback on the guess from the game

        cout << "Linked lists:" << endl;
        for (int i = 0; i < 3; i++) // for each digit in the guess
        {
            int temp = guess[i] - '0'; // convert digit from char to int

            if(feedback[i] == 'R') // if digit is correct
            {
                //Adding impossibles
                InsertNode(impossibles[0], temp); // add digit to impossibles list for slot 0
                InsertNode(impossibles[1], temp); // add digit to impossibles list for slot 1
                InsertNode(impossibles[2], temp); // add digit to impossibles list for slot 2
            }
            else if (feedback[i] == 'Y') // if digit is incorrect but present in the secret number
            {
                Delete_node(possibles[i], temp); // remove digit from possibles list for the current slot
                if (!NodeContains(impossibles[i], temp)) // if digit is not in impossibles list for current slot
                    AddToOthers(possibles, i, temp, 3); // add digit to possibles list for other slots
            }
            else // if digit is incorrect and not present in the secret number
            {
                InsertNode(possibles[i], temp); // add digit to possibles list for the current slot
                DeleteFromOthers(possibles, i, temp, 3); // remove digit from possibles list for other slots
                AddToOthers(impossibles, i, temp, 3); // add digit to impossibles list for other slots
                for (int j = 0; j < 10; j++) // for each possible digit
                    if (j != i) // if digit is not in current slot
                        InsertNode(impossibles[i], j); // add digit to impossibles list for current slot
            }
        }

        // Print current status
        PrintResult(possibles, impossibles, 3); 

		// if player has correctly guessed the secret number
        if(isPlayerWon(feedback , impossibles)) 
        {
            cout << "The secret number is: " << secretNumber(game_id) << endl;
        	break;
		}
    }

	cout << "Congrats! Now , deleting the lists..." <<endl;
    // Free allocated memory
    for (int i = 0; i < 3; i++)
    {
        DeleteNodes(possibles[i]);
        DeleteNodes(impossibles[i]);
    }

    return 0;
}
// Convert a string to an integer
int stringToInt(const std::string& str) 
{
    int result = 0;
    bool isNegative = false;
    int i = 0;

    // Check for negative sign
    if (str[i] == '-') {
        isNegative = true;
        i++;
    }

    // Convert each character to integer
    for (; i < str.length(); i++) {
        char c = str[i];
        if (c < '0' || c > '9') {
            // Invalid character
            throw exception();
        }
        int digit = c - '0';
        result = result * 10 + digit;
    }

    // Apply negative sign if necessary
    if (isNegative) {
        result = -result;
    }

    return result;
}
// Check if a linked list contains a given digit
bool NodeContains(node* head, int digit)
{
    while (head != NULL)
    {
        if (head->digit == digit)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}
// Insert a node into a linked list in ascending order
bool InsertNode(node*& head, int digit)
{
    if (NodeContains(head, digit)) {
        return false;
    }

    node* new_node = new node;
    new_node->digit = digit;
    new_node->next = NULL;

    if (head == NULL || digit < head->digit) 
    {
        new_node->next = head;
        head = new_node;
        return false;
    }

    node* current = head;
    while (current->next != NULL && current->next->digit < digit) 
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    return true;
}
// Delete a node with a given digit from a linked list
void Delete_node(node*& head, int digit)
{
    if (head == NULL) {
        return;
    }

    if (head->digit == digit) {
        node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    node* current = head;
    while (current->next != NULL && current->next->digit != digit) {
        current = current->next;
    }

    if (current->next != NULL) {
        node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}
// Delete all nodes in a linked list
void DeleteNodes(node* head) 
{
    node* current = head;
    node* temp;
    while (current != NULL) 
	{
        temp = current->next;
        delete current;
        current = temp;
    }
    head = NULL;
}
void PrintResult(node** possible, node** impossible, int size)
{
    // Loop through each slot in the number (3 slots)
    for (int i = 0; i < size; i++)
    {
        // Print the slot number
        cout << "Slot:" << i + 1 << endl;

        // Print the list of impossible digits for this slot
        cout << "Impossibles:";
        node* current_impossible = impossible[i];
        while (current_impossible != NULL)
        {
            cout << " " << current_impossible->digit;
            current_impossible = current_impossible->next;
        }
        cout << endl;

        // Print the list of possible digits for this slot
        cout << "Possibles:";
        node* current_possible = possible[i];
        while (current_possible != NULL)
        {
            cout << " " << current_possible->digit;
            current_possible = current_possible->next;
        }
        cout << endl << endl;
    }
}
void DeleteFromOthers(node** nodeArray, int nodePos, int value , int nodeSize)
{
    // Loop through all the slots in the number
    for (int i = 0; i < nodeSize; i++)
        // Skip the current slot
        if (i != nodePos)
            // Delete the given value from the linked list in this slot
            Delete_node(nodeArray[i], value);
}
void AddToOthers(node** nodeArray, int nodePos, int value , int nodeSize)
{
    // Loop through all the slots in the number
    for (int i = 0; i < nodeSize; i++)
        // Skip the current slot
        if (i != nodePos)
            // Insert the given value into the linked list in this slot
            InsertNode(nodeArray[i], value);
}
int list_length(node* head) 
{
    int count = 0;  // Initialize counter to zero
    node* current = head;  // Start from the beginning of the list

    // Loop through all the nodes in the list and increment the counter for each one
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
bool isGuessValid(string guess)
{
    // Check if the guess is the correct length (3 digits)
    if(guess.length() != 3) return false;

    // Check if any digits are repeated
    if(guess[0] == guess[1] || guess[2] == guess[1] || guess[0] == guess[2]) return false;

    // Check if all characters are digits
    for(int i = 0; i < 3;i++)
        if(guess[i] < '0' || guess[i] > '9') return false;

    return true;
}
bool isPlayerWon(string feedback , node** imps)
{
    // Check if the player has won (all green feedback) or if they have used up all their guesses
    if(feedback == "GGG" || (list_length(imps[0]) >= 9 && list_length(imps[1]) >= 9 && list_length(imps[2]) >= 9))
        return true;
    return false;
}

