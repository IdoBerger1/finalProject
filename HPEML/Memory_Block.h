#ifndef Memory_Block_Class
#define Memory_Block_Class

#define VECSIZE 8
#define I_BLOCKSIZE 32
#define J_BLOCKSIZE 32
#define K_BLOCKSIZE 32
#define UNROLL_1 4 // UNROLL_1 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
#define UNROLL_2 2 //UNROLL_2 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}

#include<iostream>
#include<vector>
using namespace std;


template <typename scalar, typename T> // CRTP (Curiously Recurring Template Pattern)
class Memory_Block // Base type of Matrix
{
protected:
	scalar* _mat;
	size_t _row;
	size_t _col;

public:
	// constructors
	Memory_Block() : _row(0), _col(0), _mat(nullptr) {}
	Memory_Block(size_t row, size_t col) : _row(row), _col(col), _mat(new scalar[row * col]) {}
	Memory_Block(size_t row, size_t col, scalar val) : _row(row), _col(col), _mat(new scalar[row * col])
	{
		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				_mat[i] = scalar::vec(val);

			for (; i < sizeOfMatrix; ++i)
				_mat[i] = val;
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				_mat[i] = val;
		}
	}

	Memory_Block(size_t row, size_t col, scalar* mat) : _row(row), _col(col), _mat(new scalar[row * col])
	{
		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				_mat[i] = scalar::vec(mat + i);

			for (; i < sizeOfMatrix; ++i)
				_mat[i] = mat[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				_mat[i] = mat[i];
		}
	}

	Memory_Block(size_t row, size_t col, string type); // rand or one matrix ...
	Memory_Block(initializer_list<initializer_list<scalar>> list_lists);
	Memory_Block(vector<vector<scalar>>& vec_vecs);
	Memory_Block(vector<vector<scalar>>&& vec_vecs);
	Memory_Block(const Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block&& M); // rvalue copy constructor

	// accessors
	inline scalar& operator () (size_t i, size_t j) { return _mat[i * _col + j]; } // access to element (i, j)
	inline scalar* operator [] (size_t i) { return _mat + i * _col; } // access to row i

	// extractors
	T operator () (size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol)  // sub-matrix: (upperRow : lowerRow(inclusive), leftCol : rightCol(inclusive))
	{
		size_t vecsize = VECSIZE, i, j, k;
		size_t row = lowerRow - upperRow + 1, col = rightCol - leftCol + 1;
		scalar* matrix = new scalar[row * col];

		if (rightCol >= vecsize)
		{
			for (i = upperRow, k = 0; i <= lowerRow; ++i)
			{
				for (j = leftCol; j < rightCol - vecsize; j += vecsize, k += vecsize)
					matrix[k] = scalar::vec(this->operator[](i) + j); // the operator () implemented above

				for (; j <= rightCol; ++j, ++k)
					matrix[k] = this->operator()(i, j);
			}
		}

		else
		{
			for (i = upperRow, k = 0; i <= lowerRow; ++i)
				for (j = leftCol; j <= rightCol; ++j, ++k)
					matrix[k] = this->operator()(i, j);
		}

		T subMatrix(row, col, matrix); // allocate sub matrix
		delete[] matrix;
		return subMatrix;
	}

	T sub(vector<size_t> row_list, vector<size_t> col_list);

	/*
	* collect 4 sub matrices into one big matrix
	* subMatrices[0] - upper left
	* subMatrices[1] - upper right
	* subMatrices[2] - lower left
	* subMatrices[3] - lower right
	*/
	T collect(Memory_Block subBlocks[], size_t row, size_t col)
	{
		size_t vecsize = VECSIZE, i, j;
		scalar* matrix = new scalar[row * col], * subMatrices[4];

		for (i = 0; i < 4; ++i)
			subMatrices[i] = subBlocks[i].data();

		if (col / 2 >= vecsize)
		{
			for (i = 0; i < row / 2; ++i)
			{
				for (j = 0; j < col / 2 - vecsize; j += vecsize)
				{
					matrix[i * col + j] = scalar::vec(subMatrices[0] + i * col / 2 + j);
					matrix[i * col + col / 2 + j] = scalar::vec(subMatrices[1] + i * col / 2 + j);
					matrix[(i + row / 2) * col + j] = scalar::vec(subMatrices[2] + i * col / 2 + j);
					matrix[(i + row / 2) * col + col / 2 + j] = scalar::vec(subMatrices[3] + i * col / 2 + j);
				}

				for (; j < col / 2; ++j)
				{
					matrix[i * col + j] = subMatrices[0][i * col / 2 + j];
					matrix[i * col + col / 2 + j] = subMatrices[1][i * col / 2 + j];
					matrix[(i + row / 2) * col + j] = subMatrices[2][i * col / 2 + j];
					matrix[(i + row / 2) * col + col / 2 + j] = subMatrices[3][i * col / 2 + j];
				}
			}
		}
		else
		{
			for (i = 0; i < row / 2; ++i)
			{
				for (j = 0; j < col / 2; ++j)
				{
					matrix[i * col + j] = subMatrices[0][i * col / 2 + j];
					matrix[i * col + col / 2 + j] = subMatrices[1][i * col / 2 + j];
					matrix[(i + row / 2) * col + j] = subMatrices[2][i * col / 2 + j];
					matrix[(i + row / 2) * col + col / 2 + j] = subMatrices[3][i * col / 2 + j];
				}
			}
		}

		T collectedMemoryBlock(row, col, matrix);
		delete[] matrix;
		return collectedMemoryBlock;
	}

	// sub-matrix: row_list - is a list of row nambers, col_list - is a list of column nambers
	// if (row_list.size() == 0) then - all rows
	// if (col_list.size() == 0) then - all columns

	// geters and seters
	inline scalar* data() { return _mat; }
	inline size_t rows() { return _row; }
	inline size_t cols() { return _col; }

	// assignment
	inline Memory_Block& operator = (const Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block&& M);
	inline Memory_Block& operator = (vector<vector<scalar>>& vec_vecs);
	inline Memory_Block& operator = (vector<vector<scalar>>&& vec_vecs);

	// input\output operators
	friend ostream& operator << (ostream& out, Memory_Block& m)
	{
		size_t row = m.rows(), col = m.cols();
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
				out << m(i, j) << " ";
			out << endl;
		}
		return out;
	}

	friend ostream& operator << (ostream& out, Memory_Block&& m)
	{
		size_t row = m.rows(), col = m.cols();
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
				out << m(i, j) << " ";
			out << endl;
		}
		return out;
	}
	friend Memory_Block& operator << (Memory_Block& M, T x);
	friend Memory_Block& operator , (Memory_Block& M, T x);

	// destructor
	~Memory_Block()
	{
		if (_mat != nullptr)
			delete[] _mat;
	}
};

#endif // !Memory_Block_Class