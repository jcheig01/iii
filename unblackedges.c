/*************************************************************************
*                              unblackedges.c
* 
* 
*      Authors: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
*
*      Date: 
*      Fall 2020 - COMP40
*      HW 2 - Part D
* 
* 
*      Summary: This program takes pbm file as an input and unblack all
*               the black edges using DFS algorithm which is implemented
*               in unblack.c file. Then, we print out the right pbm format
*               for unblacked file.
*     
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "unblack.h"
#include "pnmrdr.h"

/* check for valid pbm input and use DFS algorithm to unblack
   to unblack edges */
void process_unblack(FILE *fp);
/* format unblack pbm output into P1 pbm format */
void format_output(Bit2_T bitmap);
/* apply function for Bit2_map_row_major used to print out
   bit value of unblacked pbm file */
void print_format(int col, int row, Bit2_T bitmap, int val, void *cl);

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
            exit(EXIT_FAILURE);
        }
    }

    /* Exit the program if there are more than 1 image to be read*/
    else {
        fprintf(stderr, "Input too long\n");
        exit(EXIT_FAILURE);
    }

    process_unblack(fp);

    return EXIT_SUCCESS;
}

/***********************************************************
* process_unblack
* Description: Process "unblacking" any edges that contain
*              black line by utilizing DFS algorithm.
* Input: File pointer fp
* Output: Void
* Implementation: Check if the image in the correct format.
*                 Check the width and height is not zero.
*                 Make two bitmap of size of pbm image, one
*                 for actual pbm image bit, and one for keep
*                 tracking if the image bit was visited during
*                 DFS process. Also, make stack which will
*                 store all the black pixels that need to be
*                 unblacked. By using get_edges, get edges
*                 of pbm image and unblack edges. Then,
*                 format output that will print the unblacked
*                 pbm.
***********************************************************/
void process_unblack(FILE *fp)
{

    Pnmrdr_T rdr;

    /* check if pnm is correct format */
    TRY
        rdr = Pnmrdr_new(fp);

    EXCEPT(Pnmrdr_Badformat)
        fprintf(stderr, "Not a pnm\n");
        fclose(fp);
        exit(EXIT_FAILURE);

    END_TRY;

    Pnmrdr_mapdata pnmdata = Pnmrdr_data(rdr);

    /* check for portable bitmap */
    if (pnmdata.type != Pnmrdr_bit) {
        fprintf(stderr, "Not a bitmap\n");
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int width = pnmdata.width;
    int height = pnmdata.height;

    /* check for correct pbm size */
    if (width == 0 || height == 0) {
        fprintf(stderr, "Width/Height should not be 0\n");
        Pnmrdr_free(&rdr);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* make bitmap and put pixel value of pbm file that is read */
    Bit2_T bitmap = Bit2_new(width, height);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Bit2_put(bitmap, col, row, Pnmrdr_get(rdr));
        }
    }

    /* bitmap for keep track of already searched bit */
    Bit2_T visited = Bit2_new(Bit2_width(bitmap), Bit2_height(bitmap));

    /* stack holding black pixels that need to be unblacked */
    Stack_T stack = Stack_new();

    /* get edges and unblack pixels that need to unblacked */
    get_edges(bitmap, stack, visited);
    /* format into P1 pbm and print out */
    format_output(bitmap);

    Bit2_free(&bitmap);
    Bit2_free(&visited);
    Stack_free(&stack);
    Pnmrdr_free(&rdr);
    fclose(fp);
}

/***********************************************************
* format_output
* Purpose: Format the result output
* Input: Bit2_T type bitmap is the bit array of unblacked
*        pbm file
* Output: Void
* Implementation: Print out in P1 pbm format and allocate
*                 integer memory which will be passed onto
*                 Bit2_map_row_major which is used to print
*                 every bit value. The allocated integer
*                 memory is used to make sure the output
*                 doesn't print more than 70 columns
***********************************************************/
void format_output(Bit2_T bitmap)
{
    printf("P1\n");
    printf("%d %d\n", Bit2_width(bitmap), Bit2_height(bitmap));
    int *counter = (int *) malloc(sizeof(int));
    *counter = 0; 
    Bit2_map_row_major(bitmap, print_format, counter);
    free(counter);
}

/***********************************************************
* print_format
* Description: Serves as the apply function for
*              Bit2_map_row_major functions to print out
*              result. 
* Input: 1) Integer col is column index of bit array
*        2) Integer row is row index of bit array
*        3) Bit2_T type bitmap is the bit array we are
*           using to iterate
*        4) Integer val is the value of element at index
*           [col, row] in bitmap
*.       5) Void pointer to closure is integer memory
*           in our case, which counts until 70 column
*           and reset
* Output: Void
* Implementation: Print out bit value, but check if we get
*                 to the last colimn of the picture, or we
*                 get to 70 columns, then we insert a newline
*                 into our output
***********************************************************/
void print_format(int col, int row, Bit2_T bitmap, int val, void *cl)
{
    (void) row;

    int *counter = (int *) cl;
    (*counter)++;
    /* if we get to the last column of the picture, or we get to 70
        columns, then we insert a newline into our output. */
    if (col == Bit2_width(bitmap) - 1 || *counter == 70) {
        printf("%d\n", val);
        *counter = 0; 
    } 
    else {
        printf("%d", val);
    }
}