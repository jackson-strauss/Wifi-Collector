#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H


#include "cell.h"

int quit();
void collect(CellNode **head, int *length);
void delete_net(CellNode **head, int *length);
void display(CellNode *head);
void display_all(CellNode *head, int length);

#endif
