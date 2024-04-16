#pragma once
#include <limits>



//Matrices are to be defined as first as such:
// To access element M[i,j] of matrix, it is as simple as M.element[i][j], where i is the row and j is the column.
// To access the number of rows, M.rowCount.
// To access the number of columns, M.colCount.
// To access the number of elements, M.rowCount*M.colCount.

struct Matrix
{
	float** element;
	int rowCount;
	int colCount;
};


Matrix MatrixTranspose(Matrix M);

Matrix MatrixIdentity(int size);



Matrix MatrixRect(int rows, int columns, float def_value);
Matrix MatrixRect(int rows, int columns);
Matrix MatrixSquare(int size, float def_value);
Matrix MatrixSquare(int size);

Matrix MatrixMultiply(Matrix M, Matrix N);

float MatrixDeterminant(Matrix M);

Matrix MatrixSubMatrix(int rowStart, int rowEnd, int colStart, int colEnd, Matrix M);

Matrix MatrixSubMatrixExCol(int rowStart, int rowEnd, int colStart, int colEnd, int excludeCol, Matrix M);
Matrix MatrixSubMatrixExRow(int rowStart, int rowEnd, int colStart, int colEnd, int excludeRow, Matrix M);

Matrix MatrixSubMatrix(int rowStart, int rowEnd, int colStart, int colEnd, int excludeRow, int excludeCol, Matrix M);


Matrix MatrixCofactors(Matrix M);

Matrix MatrixAdjoint(Matrix M);


Matrix MatrixInverse(Matrix M);

Matrix MatrixScalarMultiply(float scalar, Matrix M);

Matrix MatrixPseudoInverse(Matrix M);

void MatrixFree(Matrix* M);


bool MatrixIsNull(const Matrix &M);