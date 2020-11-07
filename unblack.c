/*************************************************************************
*                              unblack.c
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part D
* 
* 
*      Summary: This is the helper file for unblackedges.c that does the
*               actual DFS processing to unblack the black edges. By using
*               stack push & pop, we store all the black pixels that need
*               to be unblacked and through DFS, pop and push the neighbor
*               black pixels.
*
**************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "unblack.h"

/****************************************************************
 * push_to_stack
 * Description: Push index info to stack
 * Inputs: 1) Stack we are pushing to
 *         2) Integer value of column index
 *         3) Integer value of row index
 * Output: Void
 * Implementation: Allocate memory for index info (containing row &
 *                 column indices) and push to stack
 *****************************************************************/
void push_to_stack(Stack_T stack, int col, int row)
{
    Index *index_p = (Index *) malloc(sizeof(Index));
    index_p -> col = col; 
    index_p -> row = row; 
    Stack_push(stack, index_p);
}

/****************************************************************
 * get_edges
 * Description: Get black edges and push to stack
 * Inputs: 1) Bit2_T type bitmap representation of pbm file
 *         2) Stack of black pixel indices
 *         3) Bit2_T type bitmap representing visited pixels
 * Output: Void
 * Implementation: Traverse through edges of pbm file and push
 *                 black pixels to stack
 *****************************************************************/
void get_edges(Bit2_T bitmap, Stack_T stack, Bit2_T visited)
{      
    int row = 0;
    int col = 0; 
    int width = Bit2_width(bitmap);
    int height = Bit2_height(bitmap);

    /* traverse columns and add black edge pixels to stack and unblack them */
    while (col < width) {
        if (Bit2_get(bitmap, col, 0) == 1) {
            push_to_stack (stack, col, 0);
            unblack (bitmap, stack, visited); 
        }
        if (Bit2_get(bitmap, col, height - 1) == 1)  {
            push_to_stack (stack, col, height - 1);
            unblack (bitmap, stack, visited);
        }
        col++;
    }   
    /* traverse rows and add black edge pixels to stack and unblack them */
    while (row < height) {
        if (Bit2_get(bitmap, 0, row) == 1) {
            push_to_stack (stack, 0, row);
            unblack(bitmap, stack, visited); 
        }
        if (Bit2_get(bitmap, width - 1, row) == 1)  {
            push_to_stack (stack, width - 1, row);
            unblack(bitmap, stack, visited);
        }
        row++;
    }
}

/****************************************************************
 * unvisited_black
 * Description: Check if black pixel was unvisited
 * Inputs: 1) Bit2_T type bitmap representation of pbm file
 *         2) Bit2_T type bitmap representing visited pixels
 *         3) Integer value of column index
 *         4) Integer value of row index
 * Output: int
 * Implementation: Return 1 if the black pixel that needs to be
 *                 unblacked is unvisited, if not, return 0.
 *****************************************************************/
int unvisited_black(Bit2_T bitmap, Bit2_T visited, int col, int row)
{
    return ((col >= 0) && (col < Bit2_width (bitmap)) && 
            (row >= 0) && (row < Bit2_height(bitmap)) &&
            (Bit2_get (bitmap, col, row) == 1) &&
            (Bit2_get (visited, col, row) == 0));
}

/****************************************************************
 * unblack
 * Description: Implement DFS to unblack the black pixels
 * Inputs: 1) Bit2_T type bitmap representation of pbm file
 *         2) Stack of black pixel indices
 *         3) Bit2_T type bitmap representing visited pixels
 * Output: Void
 * Implementation: Until the stack containing the black pixels
 *                 that needed to be unblacked gets empty, check
 *                 for neighbor pixels that need to be unblacked
 *                 and push to stack.
 *****************************************************************/
void unblack(Bit2_T bitmap, Stack_T stack, Bit2_T visited)
{ 
    while (Stack_empty(stack) != 1) {
        /* initialize black pixel index to be popped */
        Index *popped = (Index *) Stack_pop(stack);
        int col = popped->col;
        int row = popped->row;

        if (Bit2_get(visited, col, row) == 0) {
            /* mark that we've visited this pixel */
            Bit2_put(visited, col, row, 1); 

            /* push unvisited black neighbors to stack */
            /* neighbor pixel in column c - 1, row r*/
            if (unvisited_black (bitmap, visited, col - 1, row)) {
                push_to_stack (stack, col - 1, row); 
            }
            /* neighbor pixel in column c + 1, row r*/
            if (unvisited_black (bitmap, visited, col + 1, row)) {
                push_to_stack (stack, col + 1, row);
            }
            /* neighbor pixel in column c, row r - 1 */
            if (unvisited_black (bitmap, visited, col, row-1)) {
                push_to_stack (stack, col, row - 1);
            }
            /* neighbor pixel in column c, row r + 1 */
            if (unvisited_black (bitmap, visited, col, row+1)) {
                push_to_stack (stack, col, row + 1);
            }
                        
        }
        /* unblack pixel */
        Bit2_put(bitmap, col, row, 0);
        /* deallocate struct index */
        free(popped);
    }
}