/*************************************************************************
*                              sudoku.c
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Fall 2020 - COMP40
*      HW 2 - Part B
* 
* 
*      Summary: This program takes pgm file as an input and check if
*               the sudoku (represented as pixel values) is valid by
*               checking duplicate values in any row, column, or 3x3
*               submaps. If the file successfully passes all the checks,
*               the program exits 0, otherwise exits with 1.
*     
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "pnmrdr.h"

#define NINE 9

/* check for valid pgm file and check if sudoku has
   no duplicate value in each row/column/submap */
int check_all(FILE *fp);
/* check pgm file for graymap type, valid width/height/max pixel intensity */
void correct_pgm(FILE *fp, Pnmrdr_T rdr);
/* apply function for UArray2_map_col_major to check
   if duplicate values exist in column */
void check_col(int i, int j, UArray2_T uarray2, void *value, void *cl);
/* apply function for UArray2_map_row_major to check
   if duplicate values exist in row */
void check_row(int i, int j, UArray2_T uarray2, void *value, void *cl);
/* check submaps of unboxed array for duplicate value */
void check_submap(UArray2_T uarray2, int *count);
/* helper function for check_submap that looks through submap */
void each_submap(UArray2_T uarray2, int *count, int i, int j);
/* check if duplicate occurred in each row/column/submap */
void check_duplicate(int *count);
/* reset integer memory indices 1-9 to value 0 */
void reset_count(int **count);
/* free integer memory, 2D unboxed array, pnm reader, file pointer */
void free_all(int *count, UArray2_T uarray2, Pnmrdr_T rdr, FILE *fp);

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    /* If no argument is given, program reads from standard input*/
    if (argc == 1) {
        fp = stdin;
    }

    /* If an argument is given, it should be the name of a
    * portable graymap file*/
    else if (argc == 2) {
        fp = fopen(argv[1], "rb");
        if (fp == NULL) {
            fprintf(stderr, "%s: %s\n", "Could not open file", argv[1]);
            exit(1);
        }
    }

    /* Exit the program if there are more than 1 image to be read*/
    else {
        fprintf(stderr, "Input too long\n");
        exit(1);
    }

    /* 0 if success, 1 if fail */
    int answer = check_all(fp);

    exit(answer);
}

/******************************************************************
 * check_all
 * Description: Check if the sudoku is valid
 * Inputs: File pointer type fp
 * Output: Integer of 1 (correct) or 0 (fail)
 * Implementation: Check for any input file errors including correct
 *                 format, size, and maximum intensity values.
 *                 Allocate memory that holds 10 integer values. 0
 *                 index used for correctness (1 or 0) and 1-9 indices
 *                 telling how many pixel values(from 1-9) are in each
 *                 column/row/submap. If any of int memory indices 1-9
 *                 contain value greater than 2, meaning duplicate
 *                 occurred, then 0 index will become 0, which is
 *                 the value returned.
 ******************************************************************/
int check_all(FILE *fp)
{
    Pnmrdr_T rdr;

    /* check if pnm is correct format */
    TRY
        rdr = Pnmrdr_new(fp);

    EXCEPT(Pnmrdr_Badformat)
        fprintf(stderr, "Not a pnm\n");
        fclose(fp);
        exit(1);
        
    END_TRY;

    /* check if pgm input is suitable for sudoku */
    correct_pgm(fp, rdr);

    /* allocate memory that count occurrence of pixel value */
    /* Value at 0 index is 1 if sudoku is incorrect and 0 if correct*/
    int *count = (int *) malloc((NINE+1) * sizeof(int));
    /* check if machine is out of memory */
    if (count == NULL) {
        free(count);
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(1);
    }
    /* start out count memory values to be all 0 */
    count[0] = 0;
    reset_count(&count);

    /* make 9x9 unboxed array */
    UArray2_T uarray2 = UArray2_new(NINE, NINE, sizeof(int));
    /* put pixel value to unboxed array */
    for (int j = 0; j < NINE; j++) {
        for (int i = 0; i < NINE; i++) {
            int pixel = Pnmrdr_get(rdr);
            /* check if each pixel is between 1 and 9 */
            if (pixel < 1 || pixel > 9) {
                count[0] = 1;
            }
            else {
            /* put pixel in unboxed array */
            *(int *) UArray2_at(uarray2, i, j) = pixel;
            }
        }
    }
    /* if the pixel value was less than 1 or greater than 9, exit */
    if (count[0] == 1) {
        free_all(count, uarray2, rdr, fp);
        exit(1);
    }

    /* check for duplicates in any columns */
    UArray2_map_col_major(uarray2, check_col, count);
    reset_count(&count);
    /* check for duplicates in any rows */
    UArray2_map_row_major(uarray2, check_row, count);
    reset_count(&count);
    /* check for duplicates in any submaps */
    check_submap(uarray2, count);
    /* 0 if all sudoku passes, 1 if not */
    int answer = count[0];

    /* deallocate memories */
    free_all(count, uarray2, rdr, fp);
    return answer;
}

/******************************************************************
 * correct_pgm
 * Description: Check if pgm file is suitable for sudoku
 * Inputs: File pointer fp, Pnm reader rdr
 * Output: Void
 * Implementation: If pnm reader is not graymap type, exit with 1.
 *                 If width/height/max intensity is not 9, exit
 *                 with 1.
 ******************************************************************/
void correct_pgm(FILE *fp, Pnmrdr_T rdr)
{
    Pnmrdr_mapdata pnmdata = Pnmrdr_data(rdr);

    /* check for portable graymap */
    if (pnmdata.type != Pnmrdr_gray) {
        fprintf(stderr, "Not a graymap\n");
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(1);
    }
    /* check for width and height of sudoku to be 9 */
    if (pnmdata.width != NINE || pnmdata.height != NINE) {
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(1);
    }
    /* check for max intensity to be 9 */
    if (pnmdata.denominator != NINE) {
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(1);
    }
}

/******************************************************************
 * check_col
 * Description: Apply function for UArray2_map_col_major to check
 *              if duplicate values exist in column
 * Inputs: 1) Integer i is column number of array
 *         2) Integer j is row number of array
 *         3) UArray2_T uarray2 is the array we are looking through
 *         4) Void pointer to value at [i, j] index at uarray2
 *         5) Void pointer to closure, in our case, it points to
 *            integer memory of size 10 called count
 * Output: Void
 * Implementation: Pixel value at [i, j] becomes index of count
 *                 memory and adds 1 to that index, meaning that
 *                 pixel is now occurred in the column. If it's last
 *                 index of the column, check for any duplicate
 *                 in that column.
 ******************************************************************/
void check_col(int i, int j, UArray2_T uarray2, void *value, void *cl)
{
    (void) i;
    (void) uarray2;

    int *pixel = (int *) value;
    int *count = (int *) cl;
    /* increment value at index of pixel value */
    count[*pixel] = count[*pixel] + 1;

    /* if at last index of column, check for duplicate */
    if (j == NINE-1) {
        check_duplicate(count);
    }
}

/******************************************************************
 * check_row
 * Description: Apply function for UArray2_map_row_major to check
 *              if duplicate values exist in column
 * Inputs: 1) Integer i is column number of array
 *         2) Integer j is row number of array
 *         3) UArray2_T uarray2 is the array we are looking through
 *         4) Void pointer to value at [i, j] index at uarray2
 *         5) Void pointer to closure, in our case, it points to
 *            integer memory of size 10 called count
 * Output: Void
 * Implementation: Pixel value at [i, j] becomes index of count
 *                 memory and adds 1 to that index, meaning that
 *                 pixel is now occurred in the row. If it's last
 *                 index of the row, check for any duplicate
 *                 in that row.
 ******************************************************************/
void check_row(int i, int j, UArray2_T uarray2, void *value, void *cl)
{
    (void) j;
    (void) uarray2;

    int *pixel = (int *) value;
    int *count = (int *) cl;
    /* increment value at index of pixel value */
    count[*pixel] = count[*pixel] + 1;

    /* if at last index of column, check for duplicate */
    if (i == NINE-1) {
        check_duplicate(count);
    }
}

/******************************************************************
 * check_submap
 * Description: Divide the unboxed array into submaps to check for
 *              any duplicate in the submap
 * Inputs: 1) UArray2_T uarray2 is the array we are looking through
 *         2) Integer pointer count which is allocated memory to
 *            check for occurrence number of pixel from 1-9
 * Output: Void
 * Implementation: Iterate array using double for loops but
 *                 increment row and column values by 3 every time
 ******************************************************************/
void check_submap(UArray2_T uarray2, int *count)
{
    for (int i = 0; i < NINE; i=i+3) {
        for (int j = 0; j < NINE; j=j+3) {
            each_submap(uarray2, count, i, j);
        }
    }
}

/******************************************************************
 * each_submap
 * Description: Look for duplicates in the submap
 * Inputs: 1) UArray2_T uarray2 is the array we are looking through
 *         2) Integer pointer count which is allocated memory to
 *            check for occurrence number of pixel from 1-9
 *         3) Integer i is column number of array
 *         4) Integer j is row number of array
 * Output: Void
 * Implementation: Iterate through submap and use pixel value as
 *                 the index of count integer memory and add 1
 *                 every time that pixel value is shown.
 *                 When done iterating, check for duplicate using
 *                 count memory.
 ******************************************************************/
void each_submap(UArray2_T uarray2, int *count, int i, int j)
{
    int pixel = 0;

    for (int idx = i; idx < i+3; idx++) {
        for (int jdx = j; jdx < j+3; jdx++) {
            pixel = *(int *) UArray2_at(uarray2, idx, jdx);
            /* increment value at index of pixel value */
            count[pixel] = count[pixel] + 1;
        }
    }

    check_duplicate(count);
}

/******************************************************************
 * check_duplicate
 * Description: Check if duplicate existed in each column/row/submap
 * Inputs: Integer pointer count which is allocated memory to
 *         check for occurrence number of pixel from 1-9
 * Output: Void
 * Implementation: Iterate from 1-9 indices and if any of value
 *                 at those indices is greater 2, meaning duplicate
 *                 occurred, make 0 index of count memory to 1.
 *                 Then, reset indices 1-9 to value 0.
 ******************************************************************/
void check_duplicate(int *count)
{
    for (int idx = 1; idx < NINE+1; idx++) {
        if (count[idx] > 1) {
            count[0] = 1;
        }
    }

    reset_count(&count);
}

/******************************************************************
 * reset_count
 * Description: Reset count memory indices to 0
 * Inputs: Integer pointer count which is allocated memory to
 *         check for occurrence number of pixel from 1-9
 * Output: Void
 * Implementation: From 1-9 indices of count memory, make values
 *                 at those indices to 0.
 ******************************************************************/
void reset_count(int **count)
{
    for (int i = 1; i < NINE+1; i++) {
        (*count)[i] = 0;
    }
}

/******************************************************************
 * free_all
 * Description: Handy function to deallocate memories
 * Inputs: 1) Integer pointer count which is allocated memory to
 *            check for occurrence number of pixel from 1-9
 *         2) UArray2_T uarray2 is the array we are looking through
 *         3) Pnm reader rdr
 *         4) File pointer fp
 * Output: Void
 * Implementation: Free integer memory, 2D unboxed array, pnm reader, 
 *                 and file pointer
 ******************************************************************/
void free_all(int *count, UArray2_T uarray2, Pnmrdr_T rdr, FILE *fp)
{
    free(count);
    UArray2_free(&uarray2);
    Pnmrdr_free(&rdr);
    fclose(fp);
}
