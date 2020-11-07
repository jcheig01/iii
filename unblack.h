/*************************************************************************
*                              unblack.h
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part D
* 
* 
*      Summary: This is the header file for unblack.c. This file 
*               initializes the functions that unblackedges.c and unblack.c
*               use to remove black edges.
**************************************************************************/

#ifndef UNBLACK_INCLUDED
#define UNBLACK_INCLUDED

#include "bit2.h"
#include "stack.h"

/* 
 * struct holding column and row indices of black pixel that needs
 * to be unblacked
 */
typedef struct BlackIndex {
    int col;
    int row;
} Index;

/*
 * makes an index struct out of a given column and row
 * indices, and pushes it to the stack. 
 */
void push_to_stack(Stack_T stack, int col, int row);

/* 
 * traverses the edges of our bitmap, pushes black
 * edge pixels to the stack, and calls unblack function
 */
void get_edges(Bit2_T bitmap, Stack_T stack, Bit2_T visited);

/* checks whether an index has a black, unvisited pixel */
int unvisited_black(Bit2_T bitmap, Bit2_T visited, int col, int row);

/* 
 * while the stack is not empty, pop off black pixel from
 * the stack, and push all of the pixel's unvisited black 
 * neighbors on the stack, and unblack the pixel in the bitmap
 */
void unblack(Bit2_T bitmap, Stack_T stack, Bit2_T visited);

#endif