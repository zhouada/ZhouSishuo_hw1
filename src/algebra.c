#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    Matrix c;
    int i, j;
    c = create_matrix(a.rows, a.cols);
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    } // ToDo
    return c;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    Matrix c;
    int i, j;
    c = create_matrix(a.rows, a.cols);
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    } // ToDo
    return c;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    Matrix c;
    int  i, j, k;
    double m = 0;
    c = create_matrix(a.rows, a.cols);
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            for (k = 0; k < b.cols; k++)
            {

                m += a.data[i][k] * b.data[k][j];
            }
            c.data[i][j] = m;
            m = 0;
        }
    } // ToDo
    return c;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix c;
    int i, j;
    c = create_matrix(a.rows, a.cols);
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] * k;
        }
    } // ToDo
    return c;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix c;
    int i, j;
    c = create_matrix(a.cols, a.rows);
    for (i = 0; i < a.cols; i++)
    {
        for (j = 0; j < a.rows; j++)
        {
            c.data[i][j] = a.data[j][i];
        }
    } // ToDo
    return c;
}
/*得到代数余子式*/
Matrix getrid(Matrix a, int i, int j)
{
    Matrix c;
    int ii = 0, jj = 0;
    int m, n;
    c = create_matrix(a.rows - 1, a.cols - 1);
    for (m = 0; m < a.rows; m++)
    {
        if (m != i)
        {
            for (n = 0; n < a.cols; n++)
            {
                if (n != j)
                {
                    c.data[ii][jj] = a.data[m][n];
                    jj++;
                }
            }
            ii++;
            jj = 0;
        }
    }
    return c;
}

double det_matrix(Matrix a)
{
    double c;
    int j;
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else if (a.rows == 1)
    {
        return a.data[0][0];
    }
    else if (a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    for (j = 0; j < a.cols; j++)
    {
        c = a.data[1][j];
        c += pow(-1, j + 1) * det_matrix(getrid(a, 1, j));
    }
    // ToDo
    return c;
}

Matrix inv_matrix(Matrix a)
{
    Matrix c;
    Matrix result = create_matrix(a.rows, a.cols);
    int det;
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else if (det_matrix(a) == 0)
    {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int k;
        int i, j;
        k = 1 / det_matrix(a);
        Matrix Aji = transpose_matrix(a);
        double aij;
        for (i = 0; i < a.rows; i++)
        {

            for (j = 0; j < a.cols; j++)
            {
                aij = det_matrix(getrid(Aji, i, j));
                result.data[i][j] = k * aij * pow(-1, i + j);
            }
        }
    }
    // ToDo
    return result;
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    double c = 0;
    int i;
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    for (i = 0; i < a.rows; i++)
    {
        c += a.data[i][i];
    }
    // ToDo
    return c;
}

void print_matrix(Matrix a)
{
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}