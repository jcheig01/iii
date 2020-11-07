/*************************************************************************
*                              bit2.h
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part B
* 
* 
*      Summary: This is the header file for the bit2 data structure. 
*               Our Bit2 incorporate Bit_T bit vectors, allowing 
*               for a representation of a 2D bitmap.
*     
**************************************************************************/

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;

/****************************************************************
 * Bit2_new
 * Description: Create a new 2D bit array with size of width
 *              by height, each element holding of byte-size
 *              of memory.
 * Inputs: 1) Integer value of width of the desired bit array
 *         2) Integer value of height of the desired bit array
 *         3) Integer value of byte-size of each array element holds
 * Expectation: All parameters must be positive integers.
 * Output: Bit2_T type array
 * Expectation: If any of the parameter integers is non-positive, 
 *.             exit with assert.
 *              Otherwise, return an 2D bit array of given width
 *              & height with each element of given size.
 *****************************************************************/
extern T Bit2_new(int width, int height);

/******************************************************************
 * Bit2_width
 * Description: Get width value of bit array which is the
 *              number of columns of the array
 * Inputs: UArray2_T type bit array
 * Expectation: Parameter bit array must not be null.
 * Output: Integer value of width of bit array
 * Expectation: If the parameter array is null, exit with assert.
 *              Otherwise, return the width value of array
 *              in integer type.
 ******************************************************************/
extern int Bit2_width(T bit2);

/******************************************************************
 * Bit2_height
 * Description: Get height value of bit array which is the 
 *              number of rows of the array
 * Inputs: Bit2_T type bit array
 * Expectation: Parameter bit array must not be null.
 * Output: Integer value of height of bit array
 * Expectation: If the parameter array is null, exit with assert.
 *              Otherwise, return the height value of array
 *              in integer type.
 ******************************************************************/
extern int Bit2_height(T bit2);

/******************************************************************
 * Bit2_put
 * Description: Put element to given [i, j] index of bit array
 * Inputs: 1) Bit2_T type bit array
 *         2) Integer value i which is column index of bit array
 *         3) Integer value j which is row index of bit array
 *         4) Integer value value which is the value we are inserting
 * Expectation: Parameter bit array must not be null.
 *              Indices i and j must be positive integerand less
 *              than width and height of the array respectively.
 *              Value inserting must be 0 or 1
 * Output: Integer value of the inserted value
 * Expectation: If the parameter array is null, exit with assert.
 *              If indices i and j are negative or greater than
 *              width and height respectively, exit with assert.
 *              If value inserting is not 0 or 1, exit with assert.
 *              Otherwise, return integer value of the inserted value.
 ******************************************************************/
extern int Bit2_put(T bit2, int i, int j, int value);

/******************************************************************
 * Bit2_get
 * Description: Get element of given [i, j] index of bit array
 * Inputs: 1) Bit2_T type bit array
 *         2) Integer value i which is column index of bit array
 *         3) Integer value j which is row index of bit array
 * Expectation: Parameter bit array must not be null.
 *              Indices i and j must be positive integerand less
 *              than width and height of the array respectively.
 * Output: Integer value of the bit array element at index [i,j]
 * Expectation: If the parameter array is null, exit with assert.
 *              If indices i and j are negative or greater than
 *              width and height respectively, exit with assert.
 *              Otherwise, return integer value of the element
 *              at [i,j] index of bit array.
 ******************************************************************/
extern int Bit2_get(T bit2, int i, int j);

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
* Expectation: Parameter bit array must not be null.
*              Parameter apply function must not be null.
* Output: Void
* Expectation: If the parameter array or apply function is null,
*              exit with assert.
*              Otherwise, the function apply can be applied to every 
*              element column by column.
 ******************************************************************/
extern void Bit2_map_col_major(T bit2, void apply(int i, int j, T bit2, 
                        int value, void *cl), void *cl);

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
* Expectation: Parameter bit array must not be null.
*              Parameter apply function must not be null.
* Output: Void
* Expectation: If the parameter array or apply function is null,
*              exit with assert.
*              Otherwise, the function apply can be applied to every 
*              element row by row.
 ******************************************************************/
extern void Bit2_map_row_major(T bit2, void apply(int i, int j, T bit2, 
                        int value, void *cl), void *cl);

/******************************************************************
 * Bit2_free
 * Description: Deallocate memory used by bit array
 * Inputs: An address to bit array
 * Expectation: An address must not be null.
 * Output: Void
 * Expectation: If the parameter address is null, exit with assert.
 *              Otherwise, deallocate memory of the address that the
 *              bit array holds.
 ******************************************************************/
extern void Bit2_free(T *bit2);

#undef T
#endif