#ifndef SQUARE_MATRIX_Zn_HPP
#define SQUARE_MATRIX_Zn_HPP

#include <vector>

class SquaredMatrix_zn
{
public:
    SquaredMatrix_zn(const std::vector<std::vector<int>>&, int, int);

    int getDeterminant()const;
    bool isInvertible()const;
    SquaredMatrix_zn getInverseMatrix()const;
    void print()const;

    std::vector<int>& operator[](int row);
    const std::vector<int>& operator[](int row) const;
    SquaredMatrix_zn operator*(const SquaredMatrix_zn& other) const;

    int getDimension()const {return dimension;}
    int getModNumber()const {return modNumber;}
    
private:
    int normalizeModulo(int value) const;
    int modularMultiply(int a, int b) const;
    int extendedGCD(int a, int b, int& x, int& y) const;
    int modularInverse(int a) const;

    int calculateBiggerDeterminant(const std::vector<std::vector<int>>& mat, int n)const;

    void setDimension(int _dim);
    void setMod(int _mod);
    void setMatrix(const std::vector<std::vector<int>>& matrix);

private:
    std::vector<std::vector<int>> squareMatrix;
    int dimension;
    int modNumber;
};

#endif