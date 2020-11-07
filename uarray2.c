/*************************************************************************
*                              uarray2.c
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part B
* 
* 
*      Summary: This file is used to implement our version of 2D unboxed
*               array. It incorporates Hanson's UArray_T but index in
*               different way to make 1D array into 2D array.
*     
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "uarray.h"
#include "assert.h"
#include "mem.h"

#define T UArray2_T

/* data that our unboxed array element holds */
struct T {
    int width;
    int height;
    int size;
    UArray_T array;
};

/****************************************************************
 * UArray2_new
 * Description: Create a new unboxed 2D array with size of width
 *              by height, each element holding of byte-size
 *              of memory.
 * Inputs: 1) Integer value of width of the desired unboxed array
 *         2) Integer value of height of the desired unboxed array
 *         3) Integer value of byte-size of each array element holds
 * Output: UArray2_T type array
 * Implementation: Check if width & height are positive integer and
 *                 if byte-size is greater than 0. Allocate memory for
 *                 UArray2 unboxed array and initialize width, height,
 *                 size, and actual UArray unboxed array that we
 *                 will be incorporating with, and return the unboxed
 *                 array.
 *****************************************************************/
T UArray2_new(int width, int height, int size)
{
    assert(width >= 0 && height >= 0);
    assert(size > 0);

    T uarray2;
    NEW(uarray2);

    uarray2->array = UArray_new(width * height, size);
    uarray2->width = width;
    uarray2->height = height;
    uarray2->size = size;

    return uarray2;
}

/******************************************************************
 * UArray2_width
 * Description: Get width value of unboxed array which is the
 *              number of columns of the array
 * Inputs: UArray2_T type unboxed array
 * Output: Integer value of width of unboxed array
 * Implementation: Check if unboxed array is not null. If exist,
 *                 return width of that unboxed array
 ******************************************************************/
int UArray2_width(T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->width;
}

/******************************************************************
 * UArray2_height
 * Description: Get height value of unboxed array which is the
 *              number of columns of the array
 * Inputs: UArray2_T type unboxed array
 * Output: Integer value of height of unboxed array
 * Implementation: Check if unboxed array is not null. If exist,
 *                 return height of that unboxed array
 ******************************************************************/
int UArray2_height(T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->height;
}

/******************************************************************
 * UArray2_size
 * Description: Get unboxed array’s element’s byte-size of memory
 * Inputs: UArray2_T type unboxed array
 * Output: Integer value of element’s size
 * Implementation: Check if unboxed array is not null. If exist,
 *                 return byte-size of that unboxed array
 ******************************************************************/
int UArray2_size(T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->size;
}

/******************************************************************
 * UArray2_at
 * Description: Get pointer to element in unboxed array indexed
 *              in given column & row
 * Inputs: 1) UArray2_T type unboxed array
 *         2) Integer value i which is column number of unboxed array
 *         3) Integer value j which is row number of unboxed array
 * Output: Void pointer to desired element of unboxed array
 * Implementation: Check if unboxed array is not null. Also, check if
 *                 parameter index i is positive and less than width,
 *                 and if parameter index j is positive and less than
 *                 height of the unboxed array. Index of our 2D
 *                 unboxed array will correspond to width * j + i index
 *                 of UArray unboxed array, where we will be getting 
 *                 the value from.
 ******************************************************************/
void *UArray2_at(T uarray2, int i, int j)
{
    assert(uarray2 != NULL);

    int width = UArray2_width(uarray2);
    int height = UArray2_height(uarray2);

    assert(i >= 0 && i < width && j >= 0 && j < height);

    int index = width * j + i;

    void *element = UArray_at(uarray2->array, index);

    return element;
}

/*****************************************************************
* UArray2_map_col_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an unboxed array
*              column by column.
* Inputs: 1) UArray2_T type unboxed array
*         2) A void apply function that takes in column and row indices,
*            the UArray2 type unboxed array, the value at [i, j] index, 
*            a void pointer closure
*         3) A void pointer closure
* Output: Void
* Implementation: Check if unboxed array and apply function are not null.
*                 Use apply function column by column by iterating
*                 row index earlier than column index.
 ******************************************************************/
void UArray2_map_col_major(T uarray2, void apply(int i, int j, T uarray2,
                           void *value, void *cl), void *cl)
{
    assert(uarray2 != NULL);
    assert(apply != NULL);

    int width = UArray2_width(uarray2);
    int height = UArray2_height(uarray2);

    for (int idx = 0; idx < width; idx++) {
        for (int jdx = 0; jdx < height; jdx++) {
            apply(idx, jdx, uarray2, UArray2_at(uarray2, idx, jdx), cl);
        }
    }

}

/******************************************************************
 * UArray2_map_row_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an unboxed array
*              row by row.
* Inputs: 1) UArray2_T type unboxed array
*         2) A void apply function that takes in column and row indices,
*            the UArray2 type unboxed array, the value at [i, j] index, 
*            a void pointer closure
*         3) A void pointer closure
* Output: Void
* Implementation: Check if unboxed array and apply function are not null.
*                 Use apply function row by row by iterating column
*                 index earlier than row index.
 ******************************************************************/
void UArray2_map_row_major(T uarray2, void apply(int i, int j, T uarray2,
                           void *value, void *cl), void *cl)
{
    assert(uarray2 != NULL);
    assert(apply != NULL);

    int width = UArray2_width(uarray2);
    int height = UArray2_height(uarray2);

    for (int jdx = 0; jdx < height; jdx++) {
        for (int idx = 0; idx < width; idx++) {
            apply(idx, jdx, uarray2, UArray2_at(uarray2, idx, jdx), cl);
        }
    }

} 

/******************************************************************
 * UArray2_free
 * Description: Deallocate memory used by unboxed array
 * Inputs: An address to unboxed array
 * Output: Void
 * Implementation: Check if unboxed array or element inside are not
 *.                null. Then, free any allocated memery of UArray
 *                 unboxed array and our unboxed array.
 ******************************************************************/
void UArray2_free(T *uarray2)
{
    assert(uarray2 != NULL && *uarray2 != NULL);
    assert((*uarray2)->array != NULL);

    UArray_free(&((*uarray2)->array));
    free(*uarray2);
}