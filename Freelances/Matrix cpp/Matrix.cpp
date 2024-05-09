#include "Matrix.h"
#include <iomanip>

// Constructor: Initializes a matrix with specified name, rows, and columns.
Matrix::Matrix(std::string name, int x, int y) : name(name), mat(x, std::vector<int>(y, 0)) { }

// Addition operator overloading: Adds two matrices element-wise.
Matrix Matrix::operator+(Matrix& other) const
{
	Matrix result = *this;
	if (isSizeEqual(result, other)) {
		// Perform element-wise addition for matrices of equal size.
		for (int i = 0; i < result.size()[0]; ++i)
		{
			for (int j = 0; j < result.size()[1]; ++j)
			{
				result.mat[i][j] += other.mat[i][j];
			}
		}
	}
	result.name = result.name + " + " + other.name;
	return result;
}

// Accessor method: Returns the element at the specified indices.
int Matrix::At(int x, int y) const
{
	return mat[x][y];
}

// Subtraction operator overloading: Subtracts two matrices element-wise.
Matrix Matrix::operator-(Matrix& other) const
{
	Matrix result = *this;
	if (isSizeEqual(result, other))
	{
		// Perform element-wise subtraction for matrices of equal size.
		for (int i = 0; i < result.size()[0]; ++i)
		{
			for (int j = 0; j < result.size()[1]; ++j)
			{
				result.mat[i][j] -= other.mat[i][j];
			}
		}
	}
	result.name = result.name + " - " + other.name;

	return result;
}

// Multiplication operator overloading: Multiplies two matrices.
Matrix Matrix::operator*(Matrix& other) const
{
	Matrix result(this->name + " * " + other.name, this->size()[0], other.size()[1]);

	if (this->size()[1] == other.size()[0])
	{
		// Perform matrix multiplication for compatible matrices.
		for (int i = 0; i < this->size()[0]; ++i)
		{
			for (int j = 0; j < other.size()[1]; ++j)
			{
				for (int k = 0; k < this->size()[1]; ++k)
				{
					result.mat[i][j] += this->mat[i][k] * other.mat[k][j];
				}
			}
		}
	}

	return result;
}

// Assignment operator overloading: Assigns the value of another matrix to the current matrix.
Matrix& Matrix::operator=(Matrix& other)
{
	if (this != &other)
	{
		// Perform a deep copy of the matrix, including its name and elements.
		this->name = other.name;
		this->mat = other.mat;
	}
	return *this;
}

// Transpose method: Transposes the given matrix.
Matrix Matrix::Transpose(const Matrix& inputMatrix)
{
	int rows = inputMatrix.size()[0];
	int cols = inputMatrix.size()[1];

	Matrix result("Transposed " + inputMatrix.name, cols, rows);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			// Swap rows and columns to transpose the matrix.
			result.Assign(inputMatrix.At(j, i), i, j);
		}
	}

	return result;
}

// Size accessor method: Returns an array representing the dimensions of the matrix.
int* Matrix::size() const
{
	static int size[2] = { static_cast<int>(this->mat.size()), (this->mat.empty() ? 0 : static_cast<int>(this->mat[0].size())) };
	return size;
}

// Check if two matrices have equal size.
bool Matrix::isSizeEqual(const Matrix& mat1, const Matrix& mat2)
{
	return mat1.size()[0] == mat2.size()[0] && mat1.size()[1] == mat2.size()[1];
}

// Convert matrix to string representation.
std::string Matrix::ToString() const
{
	std::ostringstream oss;

	int maxRowSize = 0;
	for (const auto& row : mat) {
		maxRowSize = std::max(maxRowSize, static_cast<int>(row.size()));
	}
	int padding = name.length() + 3;

	for (int i = 0; i < mat.size(); ++i)
	{
		if (i == mat.size() / 2) {
			// Add padding and matrix name for better visualization.
			oss << std::setw(padding) << name + " = ";
		}
		else {
			oss << std::setw(padding) << "";
		}

		// Output matrix elements with proper formatting.
		for (int j = 0; j < mat[i].size(); ++j)
		{
			oss << std::setw(4) << mat[i][j] << ' ';
		}

		oss << '\n';
	}

	return oss.str();
}

// Assign a value to a specific element in the matrix.
void Matrix::Assign(int val, int x, int y)
{
	mat.at(x).at(y) = val;
}

// Overloaded stream insertion operator for printing the matrix.
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	// Output matrix name and elements to the stream.
	os << matrix.name << ":\n";
	for (int i = 0; i < matrix.mat.size(); ++i)
	{
		for (int j = 0; j < matrix.mat[i].size(); ++j)
		{
			os << matrix.mat[i][j] << ' ';
		}
		os << '\n';
	}
	return os;
}