#include "HPEML.h"

using namespace std;

class test
{
public:
	float num;

	test() : num(0) {}
	test(float _num) : num(_num) {}

	test& operator = (__m256 _register) { _mm256_storeu_ps(&num, _register); return *this; }
	//void method(__m256 _register)
	//{
	//	_mm256_storeu_ps(&num, _register);
	//}

	float* address() { return &num; }
};



int main()
{
	size_t row = 16, col = 16;
	Float F1(5), F2(10);
	Matrix<Float> A(row, col, F1), B(row, col, F2);

	cout << A - B;

	return 0;
}