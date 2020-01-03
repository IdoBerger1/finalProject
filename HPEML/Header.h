//
//  Header.h
//  Classes
//
//  Created by Dan Lemberg on 18/05/2019.
//  Copyright © 2019 Dan Lemberg. All rights reserved.
//

#ifndef Header_h
#define Header_h


#include <immintrin.h>
#include <iostream>
#include <stdbool.h>
//#include <sstream>
//#include <fstream>
//#include <cmath>
//#include <tuple>
//#include <x86intrin.h>
//#include <mkl.h>
//#include <thread>
//#include <mutex>
//#include "t_timer.h"
//#include <unistd.h>
//#include <vector>

/* Definition Section - START */
#define architecture_256

#ifdef architecture_128
#define vectypefloat __m128
#else
#ifdef architecture_256
#define vectypefloat __m256
#define vectypeint __m256i
#define vectypedouble __m256d
#else
#ifdef architecture_512
#define vectypefloat __m512
#else
//??????????????????
#endif
#endif
#endif
/* Definition Section - END */


/* class System - START */
class System
{
	//...
};
/* class System - END */


/* class Float - START */
class Float // Type of scalar field
{
	float _num;

public:
	class vec;

	// constructors
	inline Float();
	inline Float(float& num);
	inline Float(float&& num);
	inline Float(Float& F);
	inline Float(Float&& F);

	// assignment
	inline Float& operator = (Float& F);
	inline Float& operator = (Float&& F);
	inline Float& operator = (float& num);
	inline Float& operator = (float&& num);
	inline Float& operator = (vec& V);  //_mm256_storeu_ps
	inline Float& operator = (vec&& V); //_mm256_storeu_ps

	// accessors
	inline float data();
	inline float* adress();

	//...

	class vec // Type of AVX vector
	{
		vectypefloat _v;

	public:

		// constructors
		inline vec();
		inline vec(vectypefloat& v);
		inline vec(vectypefloat&& v);
		inline vec(float* p); // or inline void load(float *p); //_mm256_loadu_ps
		inline vec(Float* p); // or inline void load(Float *p); //_mm256_loadu_ps
		inline vec(vec& V);
		inline vec(vec&& V);

		// assignment
		inline vec& operator = (vec& V);
		inline vec& operator = (vec&& V);
		inline vec& operator = (float* p); //_mm256_loadu_ps
		inline vec& operator = (Float* p); //_mm256_loadu_ps
		inline vec& operator = (Float& F); // or inline void set(Float& x); //_mm256_broadcast_ss
		inline vec& operator = (Float&& F);//or inline void set(Float&& x); //_mm256_broadcast_ss

		// geters and seters
		inline vectypefloat data();
		inline vectypefloat* adress();

		// operators arithmetic
		inline friend vec operator + (vec& A, vec& B); //_mm256_add_ps        //4 times
		inline friend vec operator - (vec& A, vec& B); //_mm256_sub_ps        //4 times
		inline friend vec operator * (vec& A, vec& B); //_mm256_mul_ps        //4 times
		inline friend vec operator / (vec& A, vec& B); //_mm256_div_ps        //4 times
		inline friend vec mul_add(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B + C
		inline friend vec mul_sub(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B - C

		//...
	};
};
/* class Float - END */

/* class Int32 - START */
class Int32 // Type of scalar field
{
	int _num;

public:
	class vec;

	// constructors
	inline Int32();
	inline Int32(int& num);
	inline Int32(int&& num);
	inline Int32(Int32& F);
	inline Int32(Int32&& F);

	// assignment
	inline Int32& operator = (Int32& F);
	inline Int32& operator = (Int32&& F);
	inline Int32& operator = (int& num);
	inline Int32& operator = (int&& num);
	//inline Int32& operator = (vec& V);  //_mm256_storeu_ps
	//inline Int32& operator = (vec&& V); //_mm256_storeu_ps

	// accessors
	inline int get_data();
	inline int* get_adress();

	//...

	class vec // Type of AVX vector
	{
		vectypeint _v;

	public:

		// constructors
		inline vec();
		inline vec(vectypeint& v);
		inline vec(vectypeint&& v);
		inline vec(int* p); // or inline void load(int *p); //_mm256_loadu_ps
		inline vec(Int32* p); // or inline void load(Int32 *p); //_mm256_loadu_ps
		inline vec(vec& V);
		inline vec(vec&& V);

		// assignment
		inline vec& operator = (vec& V);
		inline vec& operator = (vec&& V);
		inline vec& operator = (int* p); //_mm256_loadu_ps
		inline vec& operator = (Int32* p); //_mm256_loadu_ps
		inline vec& operator = (Int32& F); // or inline void set(Int32& x); //_mm256_broadcast_ss
		inline vec& operator = (Int32&& F);//or inline void set(Int32&& x); //_mm256_broadcast_ss

		inline friend bool operator == (vectypeint& a, vectypeint& b);
		inline friend bool operator != (vectypeint& a, vectypeint& b);

		// geters and seters
		inline vectypeint get_data();
		inline vectypeint* get_adress();
		inline void set_data(vectypeint v);
		inline void set_adress(vectypeint* v);

		// operators arithmetic
		inline friend vec operator + (vec& A, vec& B); //_mm256_add_epi32        //4 times
		inline friend vec operator + (vec& A, vec&& B);
		inline friend vec operator + (vec&& A, vec& B);
		inline friend vec operator + (vec&& A, vec&& B);

		inline friend vec operator - (vec& A, vec& B); //_mm256_sub_ps        //4 times
		inline friend vec operator - (vec& A, vec&& B);
		inline friend vec operator - (vec&& A, vec& B);
		inline friend vec operator - (vec&& A, vec&& B);

		inline friend vec operator * (vec& A, vec& B); //_mm256_mul_ps        //4 times
		inline friend vec operator * (vec& A, vec&& B);
		inline friend vec operator * (vec&& A, vec& B);
		inline friend vec operator * (vec&& A, vec&& B);

		inline friend vec mul_add(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B + C
		inline friend vec mul_sub(vec& A, vec& B, vec& C); //_mm256_fmsub_ps // return A * B - C

		//...
	};
};
/* class Int32 - END */

/* class Int64 - START */
class Int64 // Type of scalar field
{
	int _num;

public:
	class vec;

	// constructors
	inline Int64();
	inline Int64(int& num);
	inline Int64(int&& num);
	inline Int64(Int64& F);
	inline Int64(Int64&& F);

	// assignment
	inline Int64& operator = (Int64& F);
	inline Int64& operator = (Int64&& F);
	inline Int64& operator = (int& num);
	inline Int64& operator = (int&& num);
	//inline Int64& operator = (vec& V);  //_mm256_storeu_ps
	//inline Int64& operator = (vec&& V); //_mm256_storeu_ps

	// accessors
	inline int get_data();
	inline int* get_adress();

	//...

	class vec // Type of AVX vector
	{
		vectypeint _v;

	public:

		// constructors
		inline vec();
		inline vec(vectypeint& v);
		inline vec(vectypeint&& v);
		inline vec(int* p); // or inline void load(int *p); //_mm256_loadu_ps
		inline vec(Int64* p); // or inline void load(Int64 *p); //_mm256_loadu_ps
		inline vec(vec& V);
		inline vec(vec&& V);

		// assignment
		inline vec& operator = (vec& V);
		inline vec& operator = (vec&& V);
		inline vec& operator = (int* p); //_mm256_loadu_ps
		inline vec& operator = (Int64* p); //_mm256_loadu_ps
		inline vec& operator = (Int64& F); // or inline void set(Int64& x); //_mm256_broadcast_ss
		inline vec& operator = (Int64&& F);//or inline void set(Int64&& x); //_mm256_broadcast_ss

		inline friend bool operator == (vectypeint& a, vectypeint& b);
		inline friend bool operator != (vectypeint& a, vectypeint& b);

		// geters and seters
		inline vectypeint get_data();
		inline vectypeint* get_adress();
		inline void set_data(vectypeint v);
		inline void set_adress(vectypeint* v);

		// operators arithmetic
		inline friend vec operator + (vec& A, vec& B); //_mm256_add_epi32        //4 times
		inline friend vec operator + (vec& A, vec&& B);
		inline friend vec operator + (vec&& A, vec& B);
		inline friend vec operator + (vec&& A, vec&& B);

		inline friend vec operator - (vec& A, vec& B); //_mm256_sub_ps        //4 times
		inline friend vec operator - (vec& A, vec&& B);
		inline friend vec operator - (vec&& A, vec& B);
		inline friend vec operator - (vec&& A, vec&& B);

		inline friend vec operator * (vec& A, vec& B); //_mm256_mul_ps        //4 times
		inline friend vec operator * (vec& A, vec&& B);
		inline friend vec operator * (vec&& A, vec& B);
		inline friend vec operator * (vec&& A, vec&& B);

		inline friend vec mul_add(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B + C
		inline friend vec mul_sub(vec& A, vec& B, vec& C); //_mm256_fmsub_ps // return A * B - C

		//...
	};
};
/* class Int64 - END */

/* class Double - START */
class Double // Type of scalar field
{
	double _num;

public:
	class vec;

	// constructors
	inline Double();
	inline Double(double& num);
	inline Double(double&& num);
	inline Double(Double& F);
	inline Double(Double&& F);

	// assignment
	inline Double& operator = (Double& F);
	inline Double& operator = (Double&& F);
	inline Double& operator = (double& num);
	inline Double& operator = (double&& num);
	//inline Double& operator = (vec& V);  //_mm256_storeu_pd
	//inline Double& operator = (vec&& V); //_mm256_storeu_pd

	// accessors
	inline double data();
	inline double* adress();

	//...

	class vec // Type of AVX vector
	{
		vectypedouble _v;

	public:

		// constructors
		inline vec();
		inline vec(vectypedouble& v);
		inline vec(vectypedouble&& v);
		inline vec(double* p); // or inline void load(double *p); //_mm256_loadu_pd
		inline vec(Double* p); // or inline void load(Double *p); //_mm256_loadu_pd
		inline vec(vec& V);
		inline vec(vec&& V);

		// assignment
		inline vec& operator = (vec& V);
		inline vec& operator = (vec&& V);
		inline vec& operator = (double* p); //_mm256_loadu_pd
		inline vec& operator = (Double* p); //_mm256_loadu_pd
		inline vec& operator = (Double& F); // or inline void set(Double& x); //_mm256_broadcast_ss
		inline vec& operator = (Double&& F);//or inline void set(Double&& x); //_mm256_broadcast_ss

		inline friend bool operator == (vectypedouble& a, vectypedouble& b);
		inline friend bool operator != (vectypedouble& a, vectypedouble& b);

		// geters and seters
		inline vectypedouble get_data();
		inline vectypedouble* get_adress();
		inline void set_data(vectypedouble v);
		inline void set_adress(vectypedouble* v);

		// operators arithmetic
		inline friend vec operator + (vec& A, vec& B); //_mm256_add_pd        //4 times
		inline friend vec operator + (vec& A, vec&& B);
		inline friend vec operator + (vec&& A, vec& B);
		inline friend vec operator + (vec&& A, vec&& B);

		inline friend vec operator - (vec& A, vec& B); //_mm256_sub_pd        //4 times
		inline friend vec operator - (vec& A, vec&& B);
		inline friend vec operator - (vec&& A, vec& B);
		inline friend vec operator - (vec&& A, vec&& B);

		inline friend vec operator * (vec& A, vec& B); //_mm256_mul_pd        //4 times
		inline friend vec operator * (vec& A, vec&& B);
		inline friend vec operator * (vec&& A, vec& B);
		inline friend vec operator * (vec&& A, vec&& B);

		inline friend vec operator / (vec& A, vec& B); //_mm256_mul_pd        //4 times
		inline friend vec operator / (vec& A, vec&& B);
		inline friend vec operator / (vec&& A, vec& B);
		inline friend vec operator / (vec&& A, vec&& B);

		inline friend vec mul_add(vec& A, vec& B, vec& C); //_mm256_fmadd_pd // return A * B + C
		inline friend vec mul_sub(vec& A, vec& B, vec& C); //_mm256_fmsub_pd // return A * B - C

		//...
	};
};
/* class Double - END */



/*
//class Long
//template <size_t base> class GF; GF<base>
//class Bool

//class Complex_Double
//class Complex_Float
*/


/* class Memory_Block - START */
template <typename scalar, typename T> // CRTP (Curiously Recurring Template Pattern)
class Memory_Block // Base type of Matrix
{
protected:
	scalar* _mat;
	size_t _row;
	size_t _col;

public:
	// constructors
	Memory_Block(); // empty constructor
	Memory_Block(size_t row, size_t col); // matrix of size (rows_, cols_)
	Memory_Block(size_t row, size_t col, scalar val); // matrix filled by val
	Memory_Block(size_t row, size_t col, std::string type); // rand or one matrix ...
	Memory_Block(std::initializer_list<std::initializer_list<scalar>> list_lists);
	Memory_Block(std::vector<std::vector<scalar>>& vec_vecs);
	Memory_Block(std::vector<std::vector<scalar>>&& vec_vecs);
	Memory_Block(const Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block&& M); // rvalue copy constructor

	// accessors
	inline scalar& operator () (size_t i, size_t j); // access to element (i, j)
	inline scalar* operator [] (size_t i); // access to row i

	// extractors
	T operator () (size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol);  // sub-matrix: (upperRow : lowerRow, leftCol : rightCol)
	T sub(std::vector<size_t> row_list, std::vector<size_t> col_list);

	// sub-matrix: row_list - is a list of row nambers, col_list - is a list of column nambers
	// if (row_list.size() == 0) then - all rows
	// if (col_list.size() == 0) then - all columns

	// geters 
	inline scalar* get_data();
	inline size_t get_rows();
	inline size_t get_cols();

	//seters
	inline void set_data(scalar* data);
	inline void set_rows(size_t rows);
	inline void set_cols(size_t cols);


	// assignment
	inline Memory_Block& operator = (const Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block& M);
	inline Memory_Block& operator = (std::vector< std::vector<scalar> >& vec_vecs);
	inline Memory_Block& operator = (std::vector< std::vector<scalar> >&& vec_vecs);
	inline Memory_Block& operator = (Memory_Block&& M);

	// input\output operators
	friend ostream& operator << (ostream& out, Memory_Block& M);
	friend ostream& operator << (ostream& out, Memory_Block&& M);
	friend Memory_Block& operator << (Memory_Block& M, T x);
	friend Memory_Block& operator , (Memory_Block& M, T x);

	// destructor
	~Memory_Block();

	// Slices ??? "Probably class Slice"
	//...
};
/* class Memory_Block - END */


/* class Matrix - START */
template <typename scalar>
class Matrix : public Memory_Block<scalar, Matrix<scalar>> // Type of Matrix
{
	// constructors
	using Memory_Block<scalar, Matrix<scalar>>::Memory_Block;

	Matrix(const Matrix& M);
	Matrix(Matrix& M);
	Matrix(Matrix&& M);

	// operators assignment
	inline Matrix& operator = (const Matrix& M);
	inline Matrix& operator = (Matrix& M);
	inline Matrix& operator = (std::vector<std::vector<scalar> >& vec_vecs);
	inline Matrix& operator = (std::vector<std::vector<scalar> >&& vec_vecs);
	inline Matrix& operator = (Matrix&& M);

	// operators arithmetic
	friend Matrix& operator += (Matrix& A, Matrix& B); //4 times
	friend Matrix& operator -= (Matrix& A, Matrix& B); //4 times
	friend Matrix& operator *= (Matrix& M, scalar c);  //2 times
	friend Matrix& operator += (Matrix& M, scalar c);  //2 times
	friend Matrix& operator -= (Matrix& M, scalar c);  //2 times
	friend Matrix& operator /= (Matrix& M, scalar c);  //2 times

	friend Matrix operator + (Matrix& A, Matrix& B); //4 times
	friend Matrix operator - (Matrix& A, Matrix& B); //4 times
	friend Matrix operator * (Matrix& A, Matrix& B); //4 times
	friend Matrix operator + (Matrix& A, scalar c); //4 times
	friend Matrix operator - (Matrix& A, scalar c); //4 times
	friend Matrix operator * (Matrix& A, scalar c); //4 times
	friend Matrix operator / (Matrix& A, scalar c); //2 times

	// product with transpose
	friend Matrix product(Matrix&& A, char mode_a, Matrix&& B, char mode_b); //4 times

	// Element-wise product
	friend Matrix dot_product(Matrix&& a, Matrix&& b); //4 times

	Matrix trans(bool inplace);
	Matrix conj(bool inplace);
	Matrix diag();
	//...
};
/* class Matrix - END */


/* class Vector - START */
template <typename scalar>
class Vector : public Matrix<scalar> {
	//constructors
	Vector(); //empty constructor
	Vector(size_t len); //Vector of size len
	Vector(size_t len, scalar val); //Vector filled by val
	Vector(size_t row, size_t col, std::string type); //rand Vector ...
	Vector(std::initializer_list<scalar> list);
	Vector(std::vector<scalar>& vec);
	Vector(std::vector<scalar>&& vec_vecs);
	Vector(const Vector& V); //lvalue copy constructor
	Vector(Vector& V); //lvalue copy constructor
	Vector(Vector&& V); //rvalue copy constructor

	//...
};
/* class Vector - END */


#endif /* Header_h */

