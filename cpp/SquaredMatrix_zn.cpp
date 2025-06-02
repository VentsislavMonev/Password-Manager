#include "SquaredMatrix_zn.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

int SquaredMatrix_zn::normalizeModulo(int value) const
{
    return (value % modNumber + modNumber) % modNumber;
}

int SquaredMatrix_zn::modularMultiply(int a, int b) const
{
    return normalizeModulo(static_cast<long long>(a) * b);
}

int SquaredMatrix_zn::extendedGCD(int a, int b, int &x, int &y) const
{
    if (b == 0) 
    {
        x = 1;
        y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd_val = extendedGCD(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd_val;
}

int SquaredMatrix_zn::modularInverse(int a) const
{
    a = normalizeModulo(a);
    
    int x, y;
    int gcd_val = extendedGCD(a, modNumber, x, y);
    
    if (gcd_val != 1)
    {
        throw std::runtime_error("Modular inverse does not exist");
    }
    
    return normalizeModulo(x);
}

int SquaredMatrix_zn::calculateBiggerDeterminant(const std::vector<std::vector<int>> &mat, int n) const
{
    if (n == 1) 
    {
        return normalizeModulo(mat[0][0]);
    }
    
    if (n == 2) 
    {
        int det = modularMultiply(mat[0][0], mat[1][1]) - modularMultiply(mat[0][1], mat[1][0]);
        return normalizeModulo(det);
    }
    
    int determinant = 0;
    
    // Expand along first row
    for (int col = 0; col < n; col++) 
    {
        // Create minor matrix
        std::vector<std::vector<int>> minor(n - 1, std::vector<int>(n - 1));
        
        for (int i = 1; i < n; i++) 
        {
            int minorCol = 0;
            for (int j = 0; j < n; j++) 
            {
                if (j == col) continue;
                minor[i - 1][minorCol] = mat[i][j];
                minorCol++;
            }
        }
        
        int minorDet = calculateBiggerDeterminant(minor, n - 1);
        int cofactor = (col % 2 == 0 ? 1 : -1) * modularMultiply(mat[0][col], minorDet);
        determinant = normalizeModulo(determinant + cofactor);
    }
    
    return determinant;









    // if (n == 1) 
    // {
    //     return mat[0][0];
    // }
    
    // if (n == 2) 
    // {
    //     return mat[0][0] * mat[1][1] - 
    //            mat[0][1] * mat[1][0];
    // }
    
    // int res = 0;
    // for (int col = 0; col < n; ++col) 
    // {
    //     std::vector<std::vector<int>> sub(n - 1, std::vector<int>(n - 1));

    //     for (int i = 1; i < n; ++i) 
    //     {
    //         int subcol = 0;
    //         for (int j = 0; j < n; ++j) 
    //         {
              
    //             // Skip the current column
    //             if (j == col) continue; 
              
    //             // Fill the submatrix
    //             sub[i - 1][subcol++] = mat[i][j]; 
    //         }
    //     }
      
    //     int sign = (col % 2 == 0) ? 1 : -1;
    //     res += sign * mat[0][col] * calculateBiggerDeterminant(sub, n - 1);
    // }
    // return res; 
}

SquaredMatrix_zn::SquaredMatrix_zn(const std::vector<std::vector<int>>& matrix, int _dimension, int _modNumber)
{
    setDimension(_dimension);
    setMod(_modNumber);    
    setMatrix(matrix);
}

int SquaredMatrix_zn::getDeterminant() const
{
    return calculateBiggerDeterminant(squareMatrix, dimension);
}

bool SquaredMatrix_zn::isInvertible() const
{
    int det = getDeterminant();
    if (det == 0) return false;
    
    int x, y;
    int gcd_val = extendedGCD(det, modNumber, x, y);
    return gcd_val == 1;
}

SquaredMatrix_zn SquaredMatrix_zn::getInverseMatrix() const
{
    if (!isInvertible()) {
        throw std::runtime_error("Matrix is not invertible in Z_" + std::to_string(modNumber));
    }
    
    int det = getDeterminant();
    int detInverse = modularInverse(det);
    
    // Handle 1x1 case
    if (dimension == 1) {
        std::vector<std::vector<int>> inverse = {{detInverse}};
        return SquaredMatrix_zn(inverse, dimension, modNumber);
    }
    
    // Handle 2x2 case
    if (dimension == 2) {
        std::vector<std::vector<int>> inverse(2, std::vector<int>(2));
        inverse[0][0] = modularMultiply(squareMatrix[1][1], detInverse);
        inverse[0][1] = modularMultiply(-squareMatrix[0][1], detInverse);
        inverse[1][0] = modularMultiply(-squareMatrix[1][0], detInverse);
        inverse[1][1] = modularMultiply(squareMatrix[0][0], detInverse);
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                inverse[i][j] = normalizeModulo(inverse[i][j]);
            }
        }
        return SquaredMatrix_zn(inverse, dimension, modNumber);
    }
    
    // For larger matrices: calculate adjugate matrix
    std::vector<std::vector<int>> inverse(dimension, std::vector<int>(dimension));
    
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // Create minor matrix (remove row i and column j)
            std::vector<std::vector<int>> minor(dimension - 1, std::vector<int>(dimension - 1));
            
            int minorRow = 0;
            for (int row = 0; row < dimension; row++) {
                if (row == i) continue;
                int minorCol = 0;
                for (int col = 0; col < dimension; col++) {
                    if (col == j) continue;
                    minor[minorRow][minorCol] = squareMatrix[row][col];
                    minorCol++;
                }
                minorRow++;
            }
            
            int minorDet = calculateBiggerDeterminant(minor, dimension - 1);
            int cofactor = ((i + j) % 2 == 0 ? 1 : -1) * minorDet;
            cofactor = normalizeModulo(cofactor);
            
            // Transpose while assigning (adjugate = transpose of cofactor matrix)
            inverse[j][i] = modularMultiply(cofactor, detInverse);
        }
    }
    
    return SquaredMatrix_zn(inverse, dimension, modNumber);
}

void SquaredMatrix_zn::print() const
{
    for (size_t i = 0; i < dimension; i++)
    {
        for (size_t j = 0; j < dimension; j++)
        {
            std::cout<<squareMatrix[i][j]<< " ";
        }
        std::cout<<std::endl;
        
    }
    
}

std::vector<int> &SquaredMatrix_zn::operator[](int row)
{
    if (row < 0 || row >= squareMatrix.size()) 
    {
        throw std::out_of_range("Row index out of bounds");
    }
    return squareMatrix[row];
}

const std::vector<int> &SquaredMatrix_zn::operator[](int row) const
{
    if (row < 0 || row >= squareMatrix.size()) {
        throw std::out_of_range("Row index out of bounds");
    }
    return squareMatrix[row];
}

SquaredMatrix_zn SquaredMatrix_zn::operator*(const SquaredMatrix_zn &other)const
{
    if (dimension != other.dimension || modNumber != other.modNumber) 
    {
        throw std::invalid_argument("Matrix dimensions or moduli don't match");
    }
    
    std::vector<std::vector<int>> result(dimension, std::vector<int>(dimension, 0));
    
    for (int i = 0; i < dimension; i++) 
    {
        for (int j = 0; j < dimension; j++) 
        {
            for (int k = 0; k < dimension; k++) 
            {
                result[i][j] = normalizeModulo(result[i][j] + 
                    modularMultiply(squareMatrix[i][k], other.squareMatrix[k][j]));
            }
        }
    }
    
    return SquaredMatrix_zn(result, dimension, modNumber);
}

void SquaredMatrix_zn::setDimension(int _dim)
{
    if(_dim<=0) throw std::invalid_argument("Dimension must be atleast one!");
    dimension=_dim;
}

void SquaredMatrix_zn::setMod(int _mod)
{
    if(_mod<=1) throw std::invalid_argument("Mod number must be bigger than one!");
    modNumber=_mod;
}

void SquaredMatrix_zn::setMatrix(const std::vector<std::vector<int>> &matrix)
{
    if (!matrix.size()) throw std::runtime_error("Missing matrix!");
    if (matrix.size() != dimension) throw std::invalid_argument("Must be a square matrix!");
    for (const std::vector<int>& row : matrix)
    {
        if (row.size() != dimension) throw std::invalid_argument("Must be a square matrix!");
        for (int i : row)
            if (i < 0 || i >= modNumber) throw std::invalid_argument("Elements must be modulo of " + std::to_string(modNumber));
    }
    squareMatrix = matrix;
}