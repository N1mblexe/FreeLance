#include "Test.h"
#include <cstdlib>

#define LINE "\n------------------------------------\n\n"

// Function to run various matrix operations for testing
void Test::Run()
{
	// Create two matrices of size 4x4
	Matrix* mat1 = new Matrix("A", 4, 4);
	Matrix* mat2 = new Matrix("B", 4, 4);

	// Generate random values for both matrices
	GenerateRandomMatrix(*mat1);
	GenerateRandomMatrix(*mat2);

	// Display the matrices
	std::cout << mat1->ToString() << LINE;
	std::cout << mat2->ToString() << LINE;

	// Perform matrix addition, subtraction, and multiplication and display the results
	std::cout << (*mat1 + *mat2).ToString() << LINE;
	std::cout << (*mat1 - *mat2).ToString() << LINE;
	std::cout << (*mat1 * *mat2).ToString() << LINE;

	// Display the transposes of both matrices
	std::cout << Matrix::Transpose(*mat1).ToString() << LINE;
	std::cout << Matrix::Transpose(*mat2).ToString() << LINE;

	// Clean up dynamically allocated memory
	delete mat1;
	delete mat2;
}

// Function to generate random values for a matrix
void Test::GenerateRandomMatrix(Matrix& mat)
{
	// Loop through the matrix elements
	for (int i = 0; i < mat.size()[0]; i++)
	{
		for (int j = 0; j < mat.size()[1]; j++)
		{
			// Generate a random value and multiply by 1 or -1 randomly
			int r = rand() % 6;
			r *= (rand() % 2 == 0) ? 1 : -1;

			// Assign the random value to the matrix element
			mat.Assign(r, i, j);
		}
	}
}