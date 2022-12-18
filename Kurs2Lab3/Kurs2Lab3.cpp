#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
using namespace std;


class Error {
public:
	virtual void print() = 0;
};

class ENotExistsIndex : public Error {
public:
	string ENEI;
	ENotExistsIndex() :ENEI("Invalid index!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class EDivisionByZero : public Error {
public:
	string ENEI;
	EDivisionByZero() :ENEI("Division by zero!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESize : public Error {
public:
	string ENEI;
	ESize() :ENEI("Sizes are't equal!") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESizeLessThan2 : public Error {
public:
	string ENEI;
	ESizeLessThan2() :ENEI("Sizes less than 2") {}
	void print() {
		cout << ENEI << endl;
	}
};


template <typename T>

class TemplateVector
{
private:
	size_t size;
	vector<T> _array;
	T eps;

public:

	TemplateVector()
	{
		size = 0;
		eps = 0;
	}

	TemplateVector(const size_t d)
	{
		size = d;
		_array.reserve(d);
		eps = 0;
	}

	TemplateVector(const size_t d, const vector<T> ar, const T epsilon)
	{
		size = d;
		_array.reserve(d);
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			_array.push_back(ar[i]);
		}

	}

	auto begin()
	{
		return _array.begin();
	}

	auto end()
	{
		return _array.end();
	}

	TemplateVector(const TemplateVector& source) = default;

	~TemplateVector() = default;


	friend ostream& operator<<(ostream& os, TemplateVector& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v._array.at(0) << ',';
			}

			else if (i < v.size - 1)
			{
				os << v._array.at(i) << ',';
			}

			else if (i == v.size - 1)
			{
				os << v._array.at(i) << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(_array.at(i) - v._array.at(i)) > eps)
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const TemplateVector<T>& v) const
	{
		return !(*this == v);
	}

	TemplateVector operator + (const TemplateVector& v) const
	{
		TemplateVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector& operator += (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) + v._array.at(i));
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector operator - (const TemplateVector& v) const
	{
		TemplateVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector& operator -= (const TemplateVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.at(i) = _array.at(i) - v._array.at(i);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator -= (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.emplace(i, _array.at(i) - v[i]);
		}
		return obj;
	}

	T operator * (const TemplateVector& v) const
	{
		T multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * v._array.at(i);
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * conj(v[i]);
		}
		return multiplication;
	}

	TemplateVector operator * (const T s)
	{
		TemplateVector<T> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator * (const complex<T> s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector operator * (const T s, const TemplateVector& v)
	{
		TemplateVector<T> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v._array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const complex<T> s, const TemplateVector& v)
	{
		TemplateVector<complex<T>> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v._array.at(i) * s);
		}
		return obj;

	}

	TemplateVector operator / (const T s) const
	{
		TemplateVector obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	T operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array.at(i);
	}

	T& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array.at(i);
	}

	size_t get_size() const
	{
		return size;
	}

	TemplateVector UnitPerpendicular()
	{
		{
			if (size % 2 == 0)
			{
				if (size == 2)
				{
					T* vector = new T[2];
					vector[0] = _array.at(1) * -1;
					vector[1] = _array.at(0);

					T x = vector[0] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
					T y = vector[1] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
					vector[0] = x;
					vector[1] = y;

					return TemplateVector(size, vector, 0);
				}
				else
				{
					T* vector = new T[size];
					vector[0] = 0;
					vector[size - 1] = 0;
					for (size_t i = 1; i < size - 1; ++i)
					{
						if (i % 2 != 0)
						{
							vector[i] = -1 * _array.at(i + 1);
						}

						else
						{
							vector[i] = _array.at(i - 1);
						}
					}



					T summ = 0;
					for (size_t j = 1; j < size - 1; ++j)
					{
						summ += pow(vector[j], 2);
					}


					for (size_t i = 1; i < size - 1; ++i)
					{
						vector.push_back( vector[i] / pow(summ, 0.5));
					}

					return TemplateVector(size, vector, 0);
				}
			}
			if (size % 2 != 0)
			{
				if (size < 2) throw  ESizeLessThan2();
				else
				{
					T* vector = new T[size];
					vector[0] = 0;
					for (size_t i = 1; i < size; ++i)
					{
						if (i % 2 != 0)
						{
							vector[i] = _array.at(i + 1);
						}

						else
						{
							vector[i] = -1 * _array.at(i - 1);
						}
					}

					T summ = 0;
					for (size_t j = 1; j < size; ++j)
					{
						summ += pow(vector[j], 2);
					}


					for (size_t i = 1; i < size; ++i)
					{
						vector.push_back(vector[i] / pow(summ, 0.5));
					}

					return TemplateVector(size, vector, 0);
				}
			}
		}
	}



	//TemplateVector operator =(const TemplateVector& v)
	//{
	//	if (size != v.size)throw ESize();

	//	for (size_t i = 0; i < size; ++i)
	//	{
	//		array.emplace(i, v.array.at(i));
	//	}
	//	return *this;
	//}



};

template <typename T>

class TemplateVector<complex<T>>
{
private:
	size_t size;
	vector<complex<T>> _array;
	T eps;
public:

	TemplateVector()
	{
		size = 0;
		eps = 0;
	}

	TemplateVector(const size_t d)
	{
		size = d;
		_array.reserve(d);
		eps = 0;
	}

	TemplateVector(const size_t d, const vector<complex<T>> ar, const T epsilon)
	{
		size = d;
		_array.reserve(d);
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			_array.push_back(ar[i]);
		}

	}


	TemplateVector(const TemplateVector<complex<T>>& source) = default;
	//{
	//	size = source.size;
	//	eps = source.eps;
	//	array.reserve(size);
	//	for (size_t i = 0; i < size; ++i)
	//	{
	//		array.push_back(source[i]);
	//	}
	//}

	~TemplateVector() = default;

	auto begin()
	{
		return _array.begin();
	}

	auto end()
	{
		return _array.end();
	}

	friend ostream& operator<<(ostream& os, const TemplateVector<complex<T>>& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v._array.at(0) << ',';
			}

			else if (i < v.size - 1)
			{
				os << v._array.at(i) << ',';
			}

			else if (i == v.size - 1)
			{
				os << v._array.at(i) << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(_array.at(i) - v._array.at(i)) > eps)
			{
				return false;
			}
		}
		return true;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] + v._array[i];
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<T>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) + v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) - v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<T>& v) const
	{
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) - v[i]);
		}
		return *this;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * conj(v[i]); //a= [z1,z2,z3] b= [z4,z5,z6] multi += z1*z4
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<T>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * v[i];
		}
		return multiplication;
	}

	TemplateVector<complex<T>> operator * (const T s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const T s, const TemplateVector<complex<T>>& v)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v._array.at(i) * s);
		}
		return obj;

	}

	friend TemplateVector<complex<T>> operator * (const complex<T> s, const TemplateVector<complex<T>>& v)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj.array.push_back(v._array.at(i) * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator * (const complex<T> s)
	{
		TemplateVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array[i] * s);
		}
		return obj;

	}

	TemplateVector<complex<T>> operator / (const T s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	complex<T> operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array.at(i);
	}

	complex<T>& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array.at(i);
	}

	size_t get_size() const
	{
		return size;
	}


	TemplateVector<complex<T>> UnitPerpendicular()
	{

		if (size % 2 == 0)
		{
			if (size == 2)
			{
				complex<T>* vector = new complex<T>[2];
				vector[0] = _array.at(1) * -1.0;
				vector[1] = _array.at(0);

				complex<T> x = vector[0] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
				complex<T> y = vector[1] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
				vector[0] = x;
				vector[1] = y;

				return TemplateVector<complex<T>>(size, vector, 0);
			}
			else
			{
				complex<T>* vector = new complex<T>[size];
				vector[0] = 0;
				vector[size - 1] = 0;
				for (size_t i = 1; i < size - 1; ++i)
				{
					if (i % 2 != 0)
					{
						vector[i] = -1.0 * _array.at(i + 1);
					}

					else
					{
						vector[i] = _array.at(i - 1);
					}
				}



				complex<T> summ = 0;
				for (size_t j = 1; j < size - 1; ++j)
				{
					summ += pow(vector[j], 2);
				}


				for (size_t i = 1; i < size - 1; ++i)
				{
					vector.push_back( vector[i] / pow(summ, 0.5));
				}

				return TemplateVector<complex<T>>(size, vector, 0);
			}
		}
		if (size % 2 != 0)
		{
			if (size < 2) throw  ESizeLessThan2();
			else
			{
				complex<T>* vector = new complex<T>[size];
				vector[0] = 0;
				for (size_t i = 1; i < size; ++i)
				{
					if (i % 2 != 0)
					{
						vector[i] = _array.at(i + 1);
					}

					else
					{
						vector[i] = -1.0 * _array.at(i - 1);
					}
				}
				complex<T> summ = 0;
				for (size_t j = 1; j < size; ++j)
				{
					summ += pow(vector[j], 2);
				}

				for (size_t i = 1; i < size; ++i)
				{
					vector.push_back(vector[i] / pow(summ, 0.5));
				}
				

				TemplateVector<complex<T>> obj(size, vector, 0);

				return obj;
			}

		}
	}
};


int main()
{
	vector<int> fir_array = { 1, 2, 3 };
	vector<int> sec_array = { 4, 5, 6 };

	TemplateVector<int> first(3, fir_array, 0), second(3, sec_array, 0);
	cout << first << endl;
	TemplateVector<int> resultsum = first + second;
	cout << "sum: " << resultsum << endl;

	vector<double> first_array = { 1.1, 2.2, 3.3 };
	vector<double> second_array = { 4.4, 5.5, 6.6 };

	TemplateVector<double> f_v(3, first_array, 0.5), s_v(3, second_array, 0.5);
	TemplateVector<double> resultsubtraction = s_v - f_v;
	cout << "subtraction: " << resultsubtraction << endl;
	cout << "operator [] test: " << resultsubtraction[0] << endl;

	int resultmultiv = first * second;
	cout << "result of multiplication of vectors : " << resultmultiv << endl;

	TemplateVector<double> resultmultic = s_v * 5;
	cout << "result of multiplication : " << resultmultic << endl;


	complex<double>  z1(1, 2), z2(3, 4), z3(5, 6), z4(7, 8), z5(9, 10), z6(11, 12);
	vector<complex<double>> arr = { z1, z2, z3 }, arr2 = { z4, z5, z6 };
	TemplateVector<complex<double>> complexv(3, arr, 0.5), complexv2(3, arr2, 0.5);
	cout << "complexv : " << complexv << endl;
	cout << "complexv2 : " << complexv2 << endl;

	complex<double> resultofmult = complexv * complexv2;
	cout << "test of multi : " << resultofmult << endl;
	complex<double> multi_of_double_and_complex = f_v * complexv;
	cout << "test multi_of_double_and_complex : " << multi_of_double_and_complex << endl;

	TemplateVector<complex<double>> plusresult = complexv + f_v;
	cout << "test of summ operation : " << plusresult << endl;

	TemplateVector<double> v = f_v.UnitPerpendicular();
	cout << "perp double test :" << v << endl;
	TemplateVector<complex<double>> asd = complexv.UnitPerpendicular();
	cout << "perp duoble copmlex test :" << asd << endl;


	for (auto y : f_v)
	{
		cout << y << endl;
	}

	for (auto x : complexv)
	{
		cout << x << endl;
	}


	return 0;
}
