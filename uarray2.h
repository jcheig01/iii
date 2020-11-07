/*************************************************************************
*                              uarray2.h
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part B
* 
* 
*      Summary: This is the header file for the UArray2 data structure. 
*               Our UArray2_T incorporate UArray_T unboxed array, allowing 
*               for a representation of a 2D unboxed array.
*     
**************************************************************************/

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;

/****************************************************************
 * UArray2_new
 * Description: Create a new unboxed 2D array with size of width
 *              by height, each element holding of byte-size
 *              of memory.
 * Inputs: 1) Integer value of width of the desired unboxed array
 *         2) Integer value of height of the desired unboxed array
 *         3) Integer value of byte-size of each array element holds
 * Expectation: All parameters must be positive integers.
 * Output: UArray2_T type array
 * Expectation: If any of the parameter integers is non-positive, 
 *.             exit with assert.
 *              Otherwise, return an unboxed 2D array of given width
 *              & height with each element of given size.
 *****************************************************************/
extern T UArray2_new(int width, int height, int size);


/******************************************************************
 * UArray2_width
 * Description: Get width value of unboxed array which is the
 *              number of columns of the array
 * Inputs: UArray2_T type unboxed array
 * Expectation: Parameter unboxed array must not be null.
 * Output: Integer value of width of unboxed array
 * Expectation: If the parameter array is null, exit with assert.
 *              Otherwise, return the width value of array
 *              in integer type.
 ******************************************************************/
extern int UArray2_width(T uarray2);


/******************************************************************
 * UArray2_height
 * Description: Get height value of unboxed array which is the 
 *              number of rows of the array
 * Inputs: UArray2_T type unboxed array
 * Expectation: Parameter unboxed array must not be null.
 * Output: Integer value of height of unboxed array
 * Expectation: If the parameter array is null, exit with assert.
 *              Otherwise, return the height value of array
 *              in integer type.
 ******************************************************************/
extern int UArray2_height(T uarray2);


/******************************************************************
 * UArray2_size
 * Description: Get unboxed array’s element’s byte-size of memory
 * Inputs: UArray2_T type unboxed array
 * Expectation: Parameter unboxed array must not be null.
 * Output: Integer value of element’s size
 * Expectation: If the parameter array is null, exit with assert.
 *              Otherwise, return byte-size of element of unboxed array
 *              in integer type.
 ******************************************************************/
extern int UArray2_size(T uarray2);


/******************************************************************
 * UArray2_at
 * Description: Get pointer to element in unboxed array indexed
 *              in given column & row
 * Inputs: 1) UArray2_T type unboxed array
 *         2) Integer value i which is column index of unboxed array
 *         3) Integer value j which is row index of unboxed array
 * Expectation: Parameter unboxed array must not be null.
 *              Parameter index i must be non-negative and less
 *              than width of the unboxed array.
 *              Parameter index j must be non-negative and less
 *              than height of the unboxed array.
 * Output: Void pointer to desired element of unboxed array
 * Expectation: If the parameter array is null, exit with assert.
 *              If parameter index i is negative or greater than width
 *              of the unboxed array, exit with assert.
 *              If parameter index j is negative or greater than height
 *              of the unboxed array, exit with assert.
 *              Otherwise, return a pointer to element at [i, j] index
 *              in an unboxed array.
 ******************************************************************/
extern void *UArray2_at(T uarray2, int i, int j);



/*****************************************************************
* UArray2_map_col_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an unboxed array
*              column by column.
* Inputs: 1) UArray2_T type unboxed array
*         2) A void apply function that takes in column and row indices,
*            the UArray2 type unboxed array, the value at [i, j] index
*            of unboxed array, a void pointer closure
*         3) A void pointer closure
* Expectation: Parameter unboxed array must not be null.
*              Parameter apply function must not be null.
* Output: Void
* Expectation: If the parameter array or apply function is null,
*              exit with assert.
*              Otherwise, the function apply can be applied to every 
*              element column by column.
 ******************************************************************/
extern void UArray2_map_col_major(T uarray2, void apply(int i, int j,
                                  T uarray2,void *value, void *cl),
                                  void *cl);


/******************************************************************
 * UArray2_map_row_major
* Description: Allows the client to specify a function apply that 
*              can be applied to every element in an unboxed array
*              row by row.
* Inputs: 1) UArray2_T type unboxed array
*         2) A void apply function that takes in column and row indices,
*            the UArray2 type unboxed array, the value at [i, j] index
*            of unboxed array, a void pointer closure
*         3) A void pointer closure
* Expectation: Parameter unboxed array must not be null.
*              Parameter apply function must not be null.
* Output: Void
* Expectation: If the parameter array or apply function is null,
*              exit with assert.
*              Otherwise, the function apply can be applied to every 
*              element row by row.
 ******************************************************************/
extern void UArray2_map_row_major(T uarray2, void apply(int i, int j, 
                                  T uarray2, void *value, void *cl),
                                  void *cl);



/******************************************************************
 * UArray2_free
 * Description: Deallocate memory used by unboxed array
 * Inputs: An address to unboxed array
 * Expectation: An address must not be null.
 * Output: Void
 * Expectation: If the parameter address is null, exit with assert.
 *              Otherwise, deallocate memory of the address that the
 *              unboxed array holds.
 ******************************************************************/
extern void UArray2_free(T *uarray2);

#undef T
#endif

