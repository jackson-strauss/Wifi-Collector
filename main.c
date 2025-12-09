#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "main_functions.h"
#include "helper_functions.h"
#include "cell.h"



int main() {
    CellNode *head = NULL;     // start with empty list
    int length = 0;
    int *p_length = &length;

   
    // the main loop
    for(;;) {


        // display the main message
        main_display(); 

        // getting the user input
        char *user_input = get_user_input("Option: ");
        int choice = atoi(user_input); // convert the input to an int

        printf("\n");
        
        switch(choice) {
            case 1:
                int val = quit();
                // quit early
                if (val == 1) {
                    free_list(head); // Free all nodes
                    printf("\nGoodbye !\n");

                    return 0;
                }
            break;

            case 2:
                collect(&head, p_length);

            break;

            case 4:

            break;

            case 5:
                delete_net(&head, p_length);

            break;


            case 6:

            break;

            case 7:

            break;

            case 8:

            break;


            case 9:
                display(head);
            break;


            case 10:
                display_all(head, length);
            break;



            default:
                break;


        }

      
    }
   
    return 0;
}
