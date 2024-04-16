#include "matrix.h"

//How to write function description.
/*Function Name: "Function Name"
  Author: "Author Name"
  Date: "MMM DD, YYYY", CSUN  "Spring or Fall" "Year" ISOC <- date and semester created
  Desc: "Description of what the function does and how it does it.
  Description are not for where it is used. Each function description should be self-described."
  input: "variable type 1"
  "variable type 2"
  "variable type 3"
  output: "variable type"
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      MMM DD, YYYY   "Author 1"      "Why function was modified and/or what was modified"
  */


//Matrices are to be defined as first as such:
// To access element M[i,j] of matrix, it is as simple as M.element[i][j], where i is the row and j is the column.
// To access the number of rows, M.rowCount.
// To access the number of columns, M.colCount.
// To access the number of elements, M.rowCount*M.colCount.

/*Function Name: MatrixTranspose
  Author: Omar Orozco
  Date: Mar 17, 2024, CSUN Spring 2024 ISOC
  Desc: Takes the transpose of a matrix. A transpose of a matrix is 
  defined as tM[i,j] = M[j,i].
  input: Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 17, 2024   Omar Orozco     Created function
  */
Matrix MatrixTranspose(Matrix M)
{
    Matrix tM = {nullptr, 0, 0}; //allocate memory for transposed matrix
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0)
    {
        tM.element = nullptr;
        tM.rowCount = 0;
        tM.colCount = 0;
        return tM;
    }
    tM.rowCount = M.colCount;
    tM.colCount = M.rowCount;
    tM.element = new float*[tM.rowCount]; //pointer to all row pointers

    int row = 0;
    int col = 0;
    for (row = 0; row < tM.rowCount; row++) //iterate through all rows
    {
        tM.element[row] = new float[tM.colCount]; //create row vector, length of column count
        for (col = 0; col < tM.colCount; col++) //iterate through all cols of row
            tM.element[row][col] = M.element[col][row]; //tM[i,j] = M[j,i]
    }
    //done transposing matrix M
    return tM; //return transposed matrix
}

/*Function Name: MatrixIdentity
  Author: Omar Orozco
  Date: Mar 17, 2024, CSUN Spring 2024 ISOC
  Desc: Creates an identity matrix with row and column of length size.
  input: int
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 17, 2024   Omar Orozco     Created function
  */
Matrix MatrixIdentity(int size)
{
    Matrix I = { nullptr, 0, 0 }; //allocate memory for identity matrix
    if (size <= 0)
    {
        I.element = nullptr;
        I.rowCount = 0;
        I.colCount = 0;
        return I;
    }
    I.rowCount = size;
    I.colCount = size;
    I.element = new float*[size]; //pointer to all row pointers

    int row = 0;
    int col = 0;
    for (row = 0; row < size; row++) //iterate through all rows
    {
        I.element[row] = new float[size]; //create row vector, length of column count
        for (col = 0; col < size; col++) //iterate through all cols of row
        {
            if (row != col) //if i != j => M[i,j] = 0 , else M[i,j] =  1
            I.element[row][col] = 0.0;
            else
            I.element[row][col] = 1.0;
        }
    }
    //done creating identity matrix I
    return I; //return identity matrix
}

/*Function Name: MatrixRect
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: Creates a matrix with the given amount of rows and columns. 
  All the elements in the matrix are initialized to a passed in default value.
  input: int
         int
         float
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixRect(int rows, int columns, float def_value)
{
    Matrix M; //allocate memory for matrix
    M.rowCount = rows;
    M.colCount = columns;
    M.element = new float* [rows]; //pointer to all row pointers

    int row = 0;
    int col = 0;
    for (row = 0; row < rows; row++) //iterate through all rows
    {
        M.element[row] = new float[columns]; //create row vector, length of column count
        for (col = 0; col < columns; col++) //iterate through all cols of row
                M.element[row][col] = def_value;
    }
    return M;
}
/*Function Name: MatrixRect
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: Creates a matrix with the given amount of rows and columns.
  All the elements in the matrix are initialized to 0.0.
  input: int
         float
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixRect(int rows, int columns)
{
    return MatrixRect(rows, columns, 0.0);
}

/*Function Name: MatrixSquare
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: Creates a square matrix with the column and row length equal to the size indicated.
  All the elements in the matrix initialized to a passed in default value.
  input: int
         float
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSquare(int size, float def_value)
{
    return MatrixRect(size, size, def_value);
}

/*Function Name: MatrixSquare
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: Creates a square matrix with the column and row length equal to the size indicated.
  All the elements in the matrix are initialized to 0.0.
  input: int
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSquare(int size)
{
    return MatrixRect(size, size);
}

/*Function Name: MatrixMultiply
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: Multiplies both matricies, as long as we can multiply them. That is both matricies exist and the number of columns of the left matrix
  match the number of rows of the right matrix. That is MatrixMultiply(Matrix M, Matrix N) is equivalent to M*N. If the conditions aren't met
  to multiply both matrices, a null Matrix is returned.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixMultiply(Matrix M, Matrix N)
{
    Matrix R = { nullptr, 0, 0 };
    if (M.element == nullptr || N.element == nullptr || (M.colCount != N.rowCount)) //check if Matrices M and N exist, and that we can multiply them
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }
    //Valid M and N matrices and can multiply them
    R.rowCount = M.rowCount;
    R.colCount = N.colCount;
    R.element = new float* [R.rowCount];
    int row = 0;
    int col = 0;
    float accumulator = 0.0;
    int elementMN = 0;
    for (row = 0; row < R.rowCount; row++) //iterate through all rows
    {
        R.element[row] = new float[R.colCount]; //create row vector, length of column count
        for (col = 0; col < R.colCount; col++) //iterate through all cols of row
        {
            accumulator = 0.0;
            for (elementMN = 0; elementMN < M.colCount; elementMN++)
            {
                accumulator += M.element[row][elementMN]*N.element[elementMN][col];
            }
            R.element[row][col] = accumulator;
        }
    }
    return R;
}

/*Function Name: MatrixDeterminant
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function calculates the matrix determinant as long as the matrix is a valid matrix (not a null Matrix) and a square matrix.
  The determinent is calculated through a recursive method, where the determinent of the minors of the first row is used. If the conditions
  aren't met to calculte the matrix determinent then a a null Matrix is returned.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
  output: float
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
float MatrixDeterminant(Matrix M)
{
    if (M.element == nullptr || M.colCount != M.rowCount) //check if Matrix M exists and is a square matrix
    {
        return std::numeric_limits<float>::quiet_NaN();
    }
    if (M.colCount == 1)
        return M.element[0][0];
    float accumulator = 0.0;
    Matrix subMatrix = { nullptr, 0, 0 };
    for (int i = 0; i < M.colCount; i++)
    {
        subMatrix = MatrixSubMatrixExCol(1, M.rowCount - 1, 0, M.colCount - 1, i, M); //get minor of M[0][i]
        if ((i % 2) == 0)
            accumulator += M.element[0][i] * MatrixDeterminant(subMatrix); //multiply M[0][i] with determinent of the minor of M[0][i]
        else
            accumulator -= M.element[0][i] * MatrixDeterminant(subMatrix); //multiply M[0][i] with determinent of the minor of M[0][i]
        MatrixFree(&subMatrix);
    }
    return accumulator;
}

/*Function Name: MatrixSubMatrix (overloaded)
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates a sub matrix of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) and that the bounds
  of the requested matrix is encomposed within the input matrix.This will return sub matrix as bounded between rowStart,rowEnd, colStart, 
  and colEnd, inclusively.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: int
         int
         int
         int
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSubMatrix(int rowStart, int rowEnd, int colStart, int colEnd, Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0 || rowStart < 0 || rowStart > rowEnd || colStart < 0 || colStart > colEnd)
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }
    R.rowCount = rowEnd - rowStart + 1;
    R.colCount = colEnd - colStart + 1;
    R.element = new float* [R.rowCount];
    int row = 0;
    int col = 0;
    for (row = rowStart; row <= rowEnd; row++) //iterate through rows we want
    {
        R.element[row - rowStart] = new float[R.colCount];//create row vector, length of column count
        for (col = colStart; col <= colEnd; col++) //iterate through cols we want from the rows we want
            R.element[row - rowStart][col - colStart] = M.element[row][col];
    }
    return R;
}

/*Function Name: MatrixSubMatrixExCol
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates a sub matrix of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) and that the bounds
  of the requested matrix is encomposed within the input matrix. This will return sub matrix as bounded between rowStart,rowEnd, colStart,
  and colEnd, inclusively. It will exclude the column as indicated. If the input matrix is a single column and that column is excluded,
  then a null matrix is returned.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: int
         int
         int
         int
         int
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSubMatrixExCol(int rowStart, int rowEnd, int colStart, int colEnd, int excludeCol, Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    if (excludeCol < colStart || excludeCol > colEnd) //if out of bounds, same as not excluding anything
        return MatrixSubMatrix(rowStart, rowEnd, colStart, colEnd, M);
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0 || rowStart < 0 || rowStart > rowEnd || colStart < 0 || colStart > colEnd || (excludeCol == colStart && excludeCol == colEnd))
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }
    R.rowCount = rowEnd - rowStart + 1;
    R.colCount = colEnd - colStart;
    R.element = new float* [R.rowCount];
    int row = 0;
    int col = 0;
    for (row = rowStart; row <= rowEnd; row++) //iterate through rows we want
    {
        R.element[row - rowStart] = new float[R.colCount];//create row vector, length of column count
        for (col = colStart; col <= colEnd; col++) //iterate through cols we want from the rows we want
            if (col != excludeCol) //if the excluded column reached, just skip it
            {
                if (col > excludeCol)
                    R.element[row - rowStart][col - colStart - 1] = M.element[row][col]; //if we are past excluded col, then we need to reduce col index, so we keep matrix compact
                else
                    R.element[row - rowStart][col - colStart] = M.element[row][col]; //haven't reached exlcuded col, so indexing is fine
            }
    }
    return R;
}

/*Function Name: MatrixSubMatrixExRow
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates a sub matrix of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) and that the bounds
  of the requested matrix is encomposed within the input matrix. This will return sub matrix as bounded between rowStart,rowEnd, colStart,
  and colEnd, inclusively. It will exclude the row as indicated. If the input matrix is a single row and that row is excluded,
  then a null matrix is returned.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: int
         int
         int
         int
         int
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSubMatrixExRow(int rowStart, int rowEnd, int colStart, int colEnd, int excludeRow, Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    if (excludeRow < rowStart || excludeRow > rowEnd) //if out of bounds, same as not excluding anything
        return MatrixSubMatrix(rowStart, rowEnd, colStart, colEnd, M);
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0 || rowStart < 0 || rowStart > rowEnd || colStart < 0 || colStart > colEnd || (excludeRow == rowStart && excludeRow == rowEnd))
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }
    R.rowCount = rowEnd - rowStart;
    R.colCount = colEnd - colStart + 1;
    R.element = new float* [R.rowCount];
    int row = 0;
    int col = 0;
    for (row = rowStart; row <= rowEnd; row++) //iterate through rows we want
    {
        if (row != excludeRow) //if the excluded row reached, just skip it
        {
            if (row > excludeRow) //if the excluded row reached, just skip it
            {
                R.element[row - rowStart - 1] = new float[R.colCount];//create row vector, length of column count

                for (col = colStart; col <= colEnd; col++) //iterate through cols we want from the rows we want
                    R.element[row - rowStart - 1][col - colStart] = M.element[row][col];
            }
            else
            {
                R.element[row - rowStart] = new float[R.colCount];//create row vector, length of column count

                for (col = colStart; col <= colEnd; col++) //iterate through cols we want from the rows we want
                    R.element[row - rowStart][col - colStart] = M.element[row][col];
            }
        }
    }
    return R;
}


/*Function Name: MatrixSubMatrix (overloaded)
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates a sub matrix of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) and that the bounds
  of the requested matrix is encomposed within the input matrix. This will return sub matrix as bounded between rowStart, rowEnd, colStart,
  and colEnd, inclusively. It will exclude the column and row as indicated. If the entirity of the input matrix were to be excluded then a null matrix 
  is returned.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: int
         int
         int
         int
         int
         int
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixSubMatrix(int rowStart, int rowEnd, int colStart, int colEnd, int excludeRow, int excludeCol, Matrix M)
{
    Matrix R = { nullptr, 0 ,0 };
    Matrix M_row{ nullptr, 0, 0 };
    M_row = MatrixSubMatrixExRow(0, M.rowCount - 1, 0, M.colCount - 1, excludeRow, M); //removes only the row
    if (excludeRow < 0)
        R = MatrixSubMatrixExCol(rowStart, rowEnd, colStart, colEnd, excludeCol, M_row);
    else if (excludeRow <= rowStart)
    {
        if (rowStart - 1 == -1)
            rowStart++;
        if (rowEnd - 1 == -1)
            rowEnd++;
        R = MatrixSubMatrixExCol(rowStart - 1, rowEnd - 1, colStart, colEnd, excludeCol, M_row);
    }
    else if (excludeRow > rowStart && excludeRow <= rowEnd)
    {
        if (rowEnd - 1 == -1)
            rowEnd++;
        R = MatrixSubMatrixExCol(rowStart, rowEnd - 1, colStart, colEnd, excludeCol, M_row);
    }
    else// if(excludeRow > rowEnd)
        R = MatrixSubMatrixExCol(rowStart, rowEnd, colStart, colEnd, excludeCol, M_row);
    MatrixFree(&M_row);
    return R;
}

/*Function Name: MatrixCofactors
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function returns the cofactors of the input matrix as long as the input matrix is a valid matrix (not a null Matrix), otherwise
  it will return the null Matrix.This function goes through each element of the matrix and calculates the determinent of the minor of each 
  element as the new element value.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixCofactors(Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0)
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }

    R.rowCount = M.rowCount;
    R.colCount = M.colCount;
    R.element = new float* [R.rowCount];

    int row = 0;
    int col = 0;
    float cofactor = 0.0;
    Matrix subMatrix;
    for (row = 0; row < R.rowCount; row++) //iterate through all rows
    {
        R.element[row] = new float[R.colCount]; //create row vector, length of column count
        for (col = 0; col < R.colCount; col++) //iterate through all cols of row
        {
            subMatrix = MatrixSubMatrix(0, M.rowCount - 1, 0, M.colCount - 1, row, col, M); //minor of M[row][col]
            cofactor = MatrixDeterminant(subMatrix); //determinent of minor[row][col] is the cofactor
            MatrixFree(&subMatrix);
            if ((row + col) % 2 == 0) //if even then positive cofactor, otherwise negative cofactor element
                R.element[row][col] = cofactor;
            else
                R.element[row][col] = -cofactor;
        }
    }

    return R;
}

/*Function Name: MatrixAdjoint
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates the adjoint of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) otherwise a null Matrix
  is returned. This calculates the adjoint by first finding the cofactors of the input matrix, then transposing the cofactors of the input matrix.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixAdjoint(Matrix M)
{
    Matrix cofactors = MatrixCofactors(M);
    Matrix T = MatrixTranspose(cofactors);
    MatrixFree(&cofactors);
    return T;
}


/*Function Name: MatrixInverse
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates the inverse of the input matrix as long as the input matrix is a valid matrix (not a null Matrix) and a square matrix
  otherwise a null Matrix is returned. This calculates the adjoint of the input matrix and the deteriment of the input matrix. Then it divides the 
  adjoint matrix by the determinent by multiplying the reciprocol of the determinent. That result is the inverse of the input matrix.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
  output: Matrix
  History:  Version      Date         Author        Change
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixInverse(Matrix M)
{
    Matrix adjoint = MatrixAdjoint(M);
    float det = MatrixDeterminant(M);
    Matrix I = MatrixScalarMultiply(1 / det, adjoint);
    MatrixFree(&adjoint);
        
    return I;
}

/*Function Name: MatrixScalarMultiply
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function multiplies the input matrix by a scalar as long as the input matrix is a valid matrix (not a null Matrix) otherwise a null Matrix
  is returned. This multiplies each element in the matrix by the scalar.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: float
         Matrix
  output: Matrix
  History:  Version      Date         Author        Change              
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixScalarMultiply(float scalar, Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    if (M.element == nullptr || M.colCount <= 0 || M.rowCount <= 0)
    {
        R.element = nullptr;
        R.colCount = 0;
        R.rowCount = 0;
        return R;
    }

    R.rowCount = M.rowCount;
    R.colCount = M.colCount;
    R.element = new float* [R.rowCount];

    int row = 0;
    int col = 0;

    for (row = 0; row < R.rowCount; row++) //iterate through all rows
    {
        R.element[row] = new float[R.colCount]; //create row vector, length of column count
        for (col = 0; col < R.colCount; col++) //iterate through all cols of row
            R.element[row][col] = M.element[row][col] * scalar;
    }
    return R;
}

/*Function Name: MatrixPsuedoInverse
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function creates the Psuedo Inverse matrix of the input matrix as long as the input matrix is a valid matrix (not a null Matrix)
  otherwise a null Matrix is returned. This first takes the transpose of the input matrix and multiplies that with the input matrix. The inverse
  of the multiplied result is then taken. That inversed result is then multiplied with the transpose of the input matrix. That final result is the
  Psuedo Inverse of the input matrix.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix
  output: Matrix
  History:  Version      Date         Author        Change
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
Matrix MatrixPseudoInverse(Matrix M)
{
    Matrix R = { nullptr, 0, 0 };
    Matrix tM = MatrixTranspose(M);
    Matrix symM = MatrixMultiply(tM, M);
    Matrix invM = MatrixInverse(symM);
    R = MatrixMultiply(invM, tM);
    MatrixFree(&tM);
    MatrixFree(&symM);
    MatrixFree(&invM);
    return R;
}

/*Function Name: MatrixFree
  Author: Omar Orozco
  Date: Mar 18, 2024, CSUN Spring 2024 ISOC
  Desc: This function takes in a pointer to a matrix and frees all the memory stored at the within the pointed to matrix and modifies it
  into a null Matrix. If a nullptr is passed, then this function returns immediately. If the matrix does not point to any memory,
  then its column and row count  and then is returned. If the rows point to memory, it is deleted and set to point to nullptr. Once all rows have 
  been cleared. The element memory is then deleted and set to point to nullptr and the matrices column and row count are set to zero.
  Where the null Matrix is defined as:
        element = nullptr;
        colCount = 0;
        rowCount = 0;
  input: Matrix*
  output: void
  History:  Version      Date         Author        Change
  --------------------------------------------------------------
            1.0      Mar 18, 2024   Omar Orozco     Created function
  */
void MatrixFree(Matrix* M)
{
    if (M == nullptr) //no address to a matrix passed
        return;
    if (M->element == nullptr) //matrix passed through pointer does not point to any memory
    {
        M->colCount = 0;
        M->rowCount = 0;
        return;
    }
    for (int row = 0; row < M->rowCount; row++)
    {
        if (M->element[row] != nullptr) //if it points to memory, then free it
        {
            delete[](M->element[row]);
            M->element[row] = nullptr;
        }
    }
    delete[] M->element;
    M->element = nullptr;
    M->colCount = 0;
    M->rowCount = 0;
    return;
}

bool MatrixIsNull(const Matrix &M)
{
    return (M.element == nullptr || M.colCount == 0 || M.rowCount == 0);
}