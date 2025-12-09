#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "main_functions.h"
#include "helper_functions.h"



/*

File that contains all the main functions for the Wifi Collector lab project

Assignment 3:
quit() - a function that prompts the user to quit the program - note that the dynamic memory is freed here
collect() - a function that gets the user input, reads from that line and assigns values in the linked list read from the file
delete_net() - a function that deletes a network with a matching ESSID by moving the entries up and clearing the last cell
display() - a function that, given user input, displays the cells with the matching ID
display_all() - displays all the cells in the list

*/


int quit() {
    /*

    Asks the user if they want to quit - if they want to quit return true(1) or return false(0)

    Args:
    n/a

    Returns:
    int : integer representation of a bool representing if the user want to quit or stay in the program

    */

    char user_input[MAX];
    for(;;) {
        char *user_input = get_user_input("Are ypu sure you want to exit? [y/N]: ");
        if(tolower(user_input[0]) == 'n') {
            return 0;
        } else{
            return 1;
        }

    }
    
}

void collect(CellNode **head, int *length) {
    /*

    A function that takes in the  a double pointer of the linked list and the current index and inserts cells, requested by the user, into the list at the next available cell.
    It gets the contents of these cells by reading from the specific file.
    */

    for(;;) {
        
        // getting user input
        char *user_input = get_user_input("What cell do you want to collect? (1 - 21): ");
        int choice = atoi(user_input);

        printf("\n");
        
        // checking if the choice is valid
        if (choice >= 1 && choice <= 21) {
            
            // convert the number to a string
            char user_number[MAX];
            sprintf(user_number, "%d", choice);

            // getting the filename
            char filename[MAX] = "cells/info_cell_";
            strcat(filename, user_number);
            strcat(filename, ".txt");

        
            create_cells_from_file(filename, head, length);
           
            // see if the user wants to add more cells
            strcpy(user_input, get_user_input("Do you want to add another access point? [y:N]: "));
            if(tolower(user_input[0]) == 'n') {
                return;
            }

            printf("\n");
    
        }
          
    }

}

void delete_net(CellNode **head, int *length) {
    /*

    Asks the user for the the ESSID that they want to remove - it then uses linear search to find and remove the cell if it exists
    
    */
    
    // getting the user input
    char *user_input = get_user_input("Indicate the ESSID (use \"\"): ");
    user_input[strlen(user_input)-1] = '\0';

    //Setup the search 
    CellNode *curr = *head;
    CellNode *prev = NULL;
    int index = 0;
    int found_any = 0;


        // need to format the ESSID to have the speech marks
        while (curr != NULL) {
        char first[MAX] = "\"";
        char second[MAX] = "\"";

        strcat(first, curr->data.ESSID);
        strcat(first, second);
        //Checking for a match in ESSID and proceding with linear search 
        if (strcmp(first, user_input) == 0) {
            found_any = 1;

            if (prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }

            CellNode *to_free = curr;
            curr = curr->next;
            free(to_free);
            (*length)--;

            printf("Found ESSID %s at position %d... deleting\n", first, index);
            continue;
        }
        
        prev = curr;
        curr = curr->next;
        index++;
    }

    if (!found_any) {
        printf("No matching ESSID found.\n");
    }

    printf("\n");
}

void display(CellNode *head) {
    /*

    A function that asks the user for the integer ID of the cell they want to display. If the cell is in the array it will print the contents. 
    The function uses linear search since the list is unsorted. If the cell is not found then we print an error message
    
    */

    for (;;) {
        
        // getting user input
        char *user_input = get_user_input("Indicate the number of the cell for which you want to know its information (1 - 21): ");
        int choice = atoi(user_input);

        printf("\n");

        int found = 0;
        CellNode *curr = head;
        
        // using linear search to find the corresponding cell (if it exists) 
        while (curr != NULL) {
            if (curr->data.id == choice) {
                print_cell(&curr->data);
                found = 1; // marking the cell as found
            }
            curr = curr->next; 
        }

        // if we did not find the cell we print a message to the user
        if (found == 0) {
            printf("Cell not found\n");

        }

        printf("\n");

        // ask the user if they want to quit or not
        strcpy(user_input, get_user_input("Do you want to print the information of another cell? [y/N]: "));
        if(tolower(user_input[0]) == 'n') {
            return;
        }

        printf("\n");

    }
   
}

void display_all(CellNode *head, int length) {
    /*
    
    A function that displays all the cells currently in the list and prints out a formatted version of them
    */

    CellNode *curr = head;
    while (curr != NULL) {
        print_cell(&curr->data);
        curr = curr->next;
    }
    printf("\n");

}

