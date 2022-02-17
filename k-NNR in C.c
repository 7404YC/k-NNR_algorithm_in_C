// only 119 lines without comments, enjoy  :D
#include <stdio.h>
#include <stdlib.h>
// k-NNR algorithm to calculate every point on a matrix, based on chessboard distance (layers),
// and not Euclidean distance.
// global variable so when you use it, you wont have to rely on pointers
int rowGiven,columnGiven;

// this function takes in
// 1. which layer should it traverse.
// 2. the whole matrix as a pointer (the name of array itself is a pointer so no '*' needed.
// 3. variable to hold amount of a.
// 4. variable to hold amount of b.
// 5. variable to hold amount of c.
// 6. variable to hold total amount of a,b and c counted.
// 7 and 8. position of which cell we are in the matrix now.
// 9. the counted value of the range should we traverse to count the 4 edges of each layer.
// 10. whether the current edge is vertical or horizontal, look into code to see
//     elaboration on why is it important.
void countEdges(int layer, int mtrx[rowGiven][columnGiven],int *c_a,
                int *c_b, int *c_c, int *count_them, int i, int j,
                int C1, int C2, int C3, int mode)
{
    for(int h = C1; h <= C2; h++)
    {
        int g = C3;
        if(g<0||g>rowGiven-1||h<0||h>columnGiven-1)
            continue;
        if(mode == 1)
            // in edge a & c, only the column coordinate is changing
            switch(mtrx[g][h])
            {
                case 0: break;
                case 1: (*c_a)++; (*count_them)++; break;
                case 2: (*c_b)++; (*count_them)++; break;
                case 3: (*c_c)++; (*count_them)++; break;
            }
        else
            // in edge b & d, only the row coordinate is changing
            switch(mtrx[h][g])
            {
                case 0: break;
                case 1: (*c_a)++; (*count_them)++; break;
                case 2: (*c_b)++; (*count_them)++; break;
                case 3: (*c_c)++; (*count_them)++; break;
            }
    }
}

int main()
{
    // first get the matrix,
    // a = 1, b = 2, c = 3, empty = 0;
    int mtrx [10][11] = {   {0,0,0,0,0,0,0,0,0,0,0},
                            {0,3,3,0,0,0,1,1,0,0,0},
                            {0,3,3,3,0,1,1,1,1,0,0},
                            {0,3,3,3,0,0,1,3,0,0,0},
                            {0,2,0,0,0,2,0,0,0,0,0},
                            {0,0,0,0,0,0,3,0,0,0,0},
                            {0,0,0,2,2,0,2,2,2,0,0},
                            {0,0,0,0,0,1,2,2,0,0,0},
                            {0,0,0,0,0,2,2,2,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0}    };
    // we traverse around, if the cell value is 0, meaning it is supposed to be
    // calculated, then we take the 3 layers beside it.
    // if the 3 layers also cannot satisfy 9 cells with values then forget it.
    // we will calculate which is the max value get then fill in 1 or 2 or 3 into it.
    // 1st layer will have priority over 2nd so is 2nd over 3rd

    // traverse condition
    // 1. does not overstep outside the box, meaning index !<0  or !>limit of dimension you entered
    // 2. skip its own cell, so traverse stops when it is on the current i,j coordinate
    // 3. count the 1st layer, count the second layer, check if got enough, if no, continue,
    //    if yes, decide.
    // 4. do this for all cells.
    printf("Please enter the coefficient k in k-NNR calculation:\n");
    // what amount of k-nearest neighbour?
    int KNNR;
    scanf(" %d", &KNNR);
    // get row count of matrix
    rowGiven = sizeof(mtrx)/sizeof(mtrx[0]);
    // get column count of matrix
    columnGiven = sizeof(mtrx[0])/sizeof(mtrx[0][0]);
    // the maximum layer we can traverse based on the largest dimension given
    int max_layer;
    if(rowGiven > columnGiven)
        max_layer = rowGiven;
    else
        max_layer = columnGiven;
    // declare another matrix to hold the changes, this is because we cannot operate on
    // original matrix when we havent done all the operations.
    int mtrx2[rowGiven][columnGiven];
    printf("\nThe original matrix: a = 1, b = 2, c  =3, empty = 0\n");
    for(int i = 0; i < rowGiven; i++)
    {
        for(int j = 0; j < columnGiven; j++)
        {
            // make a copy of original matrix on the temporary matrix
            mtrx2[i][j] = mtrx[i][j];
            printf("%3d ",mtrx[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n\n");
    // traverse across the rows
    for(int i = 0; i < (sizeof(mtrx)/sizeof(mtrx[0])); i++)
    {
        // traverse across the columns
        for(int j = 0; j < (sizeof(mtrx[0])/sizeof(mtrx[0][0])); j++)
        {
            // if current cell is 0, count it (0 represent unfilled and need calculation)
            if(mtrx[i][j] == 0)
            {
                int layer, count_them = 0, c_a = 0, c_b = 0, c_c = 0;
                for(layer = 1; layer < max_layer; layer++)
                {
                // 4 corners first. They have the following dynamic coordinates based on which layer we are talking about
                //                  (i-layer,j-layer)
                //                  (i-layer,j+layer)
                //                  (j-layer,i+layer)
                //                  (i+layer,j+layer)
                // the distances between the adjacent corners are 2 * layer
                // e.g.: on layer 1, distance between adjacent corner = 2
                //       layer 2 has 4, layer 3 has 6
                // increment by layer * 2 avoids us from traversing non-corner elements
                // so we always only loop 4 times no matter which layer we are on
                for(int g = i-layer; g <= i+layer; g+=(layer*2))
                {
                    for(int h = j-layer; h <= j+layer; h+=(layer*2))
                    {
                        if(g<0||g>rowGiven-1||h<0||h>columnGiven-1)
                            continue;
                        switch(mtrx[g][h])
                        {
                            case 0: break;
                            case 1: c_a++; count_them++; break;
                            case 2: c_b++; count_them++; break;
                            case 3: c_c++; count_them++; break;
                        }
                    }
                }
                // done with corner, then deal with 4 edges labeled a,b,c and d:
                //        a
                //      O----O
                //    b |    | d
                //      |    |
                //      O----O
                //        c
                // note that in one of the edges, theres always either the row or column
                // that does not change, so we can traverse based on that.
                // a -> (i-layer,j-layer+1) --> (i-layer,j+layer-1)
                // b -> (i-layer+1,j-layer) --> (i+layer-1,j-layer)
                // c -> (i+layer,j-layer+1) --> (i+layer,j+layer-1)
                // d -> (i-layer+1,j+layer) --> (i+layer-1,j+layer)

                // so, edge a should be changing columns only so:
                countEdges(layer,mtrx,&c_a,&c_b,&c_c,&count_them,i,j,j-layer+1,j+layer-1,i - layer,1);
                // so, edge c should be changing columns only so:
                countEdges(layer,mtrx,&c_a,&c_b,&c_c,&count_them,i,j,j-layer+1,j+layer-1,i + layer,1);
                // so, edge b should be changing rows only so:
                countEdges(layer,mtrx,&c_a,&c_b,&c_c,&count_them,i,j,i-layer+1,i+layer-1,j - layer,2);
                // so, edge d should be changing rows only so:
                countEdges(layer,mtrx,&c_a,&c_b,&c_c,&count_them,i,j,i-layer+1,i+layer-1,j + layer,2);

                // if we go over the needed elements or exactly on it, we can quit
                // counting the layers already.
                if(count_them >= KNNR)
                    break;
                }
                // decide which is more, if count_them is exactly 9, if not, then put 0 to represent "?"
                if(count_them == KNNR)
                {
                    if(c_a>c_b && c_a>c_c)
                        mtrx2[i][j] = 1;
                    else if(c_b>c_a && c_b>c_c)
                        mtrx2[i][j] = 2;
                    else if(c_c>c_a && c_c>c_b)
                        mtrx2[i][j] = 3;
                    // there be cases where you get appearance of originally filled is k times but the
                    // count of either combination may be same, resulting in indecision, thus filling 0
                    else if(c_a==c_b || c_b==c_c || c_c==c_a)
                        mtrx2[i][j] = 0;
                }
                else // this is for if counted neighbor is not same as user given value of k
                // we dont need to do anything as they're originally 0 already, but you can write some code
                // here if you need it to do anything
            }
        }
    }
    // to print the calculated matrix only
    printf("The calculated matrix: a = 1, b = 2, c  =3, empty = 0\n");
    for(int i = 0; i < rowGiven; i++)
    {
        for(int j = 0; j < columnGiven; j++)
            printf("%3d ",mtrx2[i][j]);
        printf("\n\n");
    }
    // this line is here in case you compiled it into an executable file.
    // if there is no pause, after the code is done, it will quit itself.
    // leaving you no time to observe the result.
    system("PAUSE");
    return 0;
}
