/*************************************************************************
*                              bit2.c
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part B
* 
* 
*      Summary: This file is used to implement our version of 2D bit
*               array. It incorporates Hanson's Bit_T but index in
*               different way to make 1D array into 2D array.
*     
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "bit.h"
#include "assert.h"
#include "mem.h"

#define T Bit2_T

/* data that our bit array element holds */
struct T {
    int width;
    int height;
    Bit_T bit;
};

/****************************************************************
 * Bit2_new
 * Description: Create a new 2D bit array with size of width
 *              by height, each element holding of byte-size
 *              of memory.
 * Inputs: 1) Integer value of width of the desired bit array
 *         2) Integer value of height of the desired bit array
 *         3) Integer value of byte-size of each array element holds
 * Output: Bit2_T type array
 * Implementation: 
 *****************************************************************/
T Bit2_new(int width, int height)
{
    assert(width >= 0 && height >= 0);

    T bit2;
    /* allocates a new 2D Bit */
    NEW(bit2);

    /* store bit information */
    bit2->bit = Bit_new(width * height);
    bit2->width = width;
    bit2->height = height;

    return bit2;
}

/******************************************************************
 * Bit2_width
 * Description: Get width value of bit array which is the
 *              number of columns of the array
 * Inputs: UArray2_T type bit array
 * Output: Integer value of width of bit array
 * Implementation: 
 ******************************************************************/
int Bit2_width(T bit2)
{
    assert(bit2 != NULL);
    return bit2->width;
}

/******************************************************************
 * Bit2_height
 * Description: Get height value of bit array which is the 
 *              number of rows of the array
 * Inputs: Bit2_T type bit array
 * Output: Integer value of height of bit array
 * Implementation: 
 ******************************************************************/
int Bit2_height(T bit2)
{
    assert(bit2 != NULL);
    return bit2->height;
}

/******************************************************************
 * Bit2_put
 * Description: Put element to given [i, j] index of bit array
 * Inputs: 1) Bit2_T type bit array
 *         2) Integer value i which is column index of bit array
 *         3) Integer value j which is row index of bit array
 *         4) Integer value value which is the value we are inserting
 * Output: Integer value of the inserted value
 * Implementation: 
 ******************************************************************/
int Bit2_put(T bit2, int i, int j, int value)
{
    assert(bit2 != NULL);
    assert(value == 0 || value == 1);

    int width = Bit2_width(bit2);
    int height = Bit2_height(bit2);

    assert(i >= 0 && i < width && j >= 0 && j < height);

    int index = width * j + i;

    return Bit_put(bit2->bit, index, value);
}

/******************************************************************
 * Bit2_get
 * Description: Get element of given [i, j] index of bit array
 * Inputs: 1) Bit2_T type bit array
 *         2) Integer value i which is column index of bit array
 *         3) Integer value j which is row index of bit array
 * Output: Integer value of the bit array element at index [i,j]
 * Implementation: 
 ******************************************************************/
int Bit2_get(T bit2, int i, int j)
{
    assert(bit2 != NULL);

    int width = Bit2_width(bit2);
    int height = Bit2_height(bit2);

    assert(i >= 0 && i < width && j >= 0 && j < height);

    int index = width * j + i;

    return Bit_get(bit2->bit, index);
}

/*****************************************************************
* Bit2_map_col_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an bit array
*              column by column.
* Inputs: 1) Bit2_T type bit array
*         2) A void apply function that takes in column and row indices,
*            the Bit2_T type bit array, the value at [i, j] index of 
*            bit array, a void pointer closure
*         3) A void pointer closure
* Output: Void
* Implementation: 
 ******************************************************************/
void Bit2_map_col_major(T bit2, void apply(int i, int j, T bit2, 
                        int value, void *cl), void *cl)
{
    assert(bit2 != NULL);
    assert(apply != NULL);

    int width = Bit2_width(bit2);
    int height = Bit2_height(bit2);

    for (int idx = 0; idx < width; idx++) {
        for (int jdx = 0; jdx < height; jdx++) {
            apply(idx, jdx, bit2, Bit2_get(bit2, idx, jdx), cl);
        }
    }
}

/*****************************************************************
* Bit2_map_row_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an bit array
*              row by row.
* Inputs: 1) Bit2_T type bit array
*         2) A void apply function that takes in column and row indices,
*            the Bit2_T type bit array, the value at [i, j] index of 
*            bit array, a void pointer closure
*         3) A void pointer closure
* Output: Void
* Implementation: 
 ******************************************************************/
void Bit2_map_row_major(T bit2, void apply(int i, int j, T bit2, 
                        int value, void *cl), void *cl)
{
    assert(bit2 != NULL);
    assert(apply != NULL);

    int width = Bit2_width(bit2);
    int height = Bit2_height(bit2);

    for (int jdx = 0; jdx < height; jdx++) {
        for (int idx = 0; idx < width; idx++) {
            apply(idx, jdx, bit2, Bit2_get(bit2, idx, jdx), cl);
        }
    }
}

/******************************************************************
 * Bit2_free
 * Description: Deallocate memory used by bit array
 * Inputs: An address to bit array
 * Output: Void
 * Implementation: 
 ******************************************************************/
void Bit2_free(T *bit2)
{
    assert(bit2 != NULL && *bit2 != NULL);
    assert((*bit2)->bit != NULL);

    Bit_free(&((*bit2)->bit));
    free(*bit2);
}