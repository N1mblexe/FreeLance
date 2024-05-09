#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <sstream>

class Matrix {
private:
	std::vector<std::vector<int>> mat;

public:
	std::string name;

	//-----------Fatih Berat Okyay--------------
	Matrix(std::string name, int rows, int cols);

	int At(int row, int col) const;

	Matrix operator+(Matrix& other) const;
	Matrix operator-(Matrix& other) const;
	//-------------------------------------------

	//-----------Merve Nur Bal-------------------
	Matrix operator*(Matrix& other) const;
	Matrix& operator=(Matrix& other);

	static Matrix Transpose(const Matrix& inputMatrix);
	static bool isSizeEqual(const Matrix& mat1, const Matrix& mat2);
	//-------------------------------------------

	//------------Sümeyye Salih------------------
	int* size() const;
	std::string ToString() const;
	void Assign(int value, int row, int col);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	//------------------------------------------
};

#endif // MATRIX_H
