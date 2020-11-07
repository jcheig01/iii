# iii
C sudoku &amp; unblackedges

Name: Jae Hyun Cheigh (jcheig01), Khanh Nguyen (cnguye10)
Fall 2020 - COMP40
Homework 2
Submit Date: 10/1/2020

We successfully implemented sudoku program by utilizing 2D unboxed array
data structure that we created. We first built uarray2.h and uarray2.c
files which implemented UArray2_T type 2D unboxed array, which was built with
the help of Hanson's UArray_T, 1D unboxed array. Each of the element in this
2D array was able to store width, height, byte-size of unboxed array created,
and Hanson's 1D unboxed array. Then, we created sudoku.c where we implemented
the actual sudoku program. The implementation read portable graymap file of
pixel values ranging from 1-9. We were to transform this image into a sudoku
problem, each pixel values representing sudoku values. By utilizing map
functions of unboxed array, we were able to find if any duplicate values
existed either in any column or row in the image. Also, we divided the 9x9
pgm into 3x3 submaps in order to check if any duplicate pixel value existed
there as well. If these checks all passed, then the program successfully
exited with 1, if not, exited with 0.

Also, we successfully implemented unblackedges program by utilizing 2D bit
array data structure that we created and Hanson's stack data structure.
We first built bit2.h and bit2.c files which implemented Bit2_T type 2D
bit array, which was built with the help of Hanson's Bit_T, 1D bit array.
Each of the element in this 2D bit array stored width, height of bit array
created, and Hanson's 1D bit array. Then, we created unblackedges.c,
unblack.c, and unblack.h (the latter 2 files were used as helper modules for
unblackedges.c) where we implemented the actual unblackedges program. The
implementation read portable bitmap and stored bits into our 2D bit array,
and performed DFS to unblack the black edges. Aside from creating 2D bit
array for reading pbm file bit values, we created another 2D bit array of 
the same size in order to keep track of visited/unvisited index while 
performing DFS. Stack data structure was used to push black bits that
needed to be unblacked. Every time the array element was popped, the
neighbor black bits were searched and the popped element value changed
from 1(black) to 0(white).

There was a memory leak for using pngtopnm command for converting png file
to pnm file. We checked with the TA and it seemed like it was a leak that
we couldn't avoid. Other than that, the program worked well in general.
