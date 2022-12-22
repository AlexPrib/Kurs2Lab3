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
		if (size != v.size) throw ("Sizes are't equal!");

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
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector& operator += (const TemplateVector& v) const
	{
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) + v._array.at(i));
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector operator - (const TemplateVector& v) const
	{
		TemplateVector obj(size);
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector& operator -= (const TemplateVector& v) const
	{
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.at(i) = _array.at(i) - v._array.at(i);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator -= (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.emplace(i, _array.at(i) - v[i]);
		}
		return obj;
	}

	T operator * (const TemplateVector& v) const
	{
		T multiplication = 0;
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * v._array.at(i);
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ("Sizes are't equal!");
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
		if (s == 0) throw (" division by zero");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s.real() == 0 && s.imag() == 0) throw (" division by zero");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	T operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ("Invalid index!");
		return _array.at(i);
	}

	T& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ("Invalid index!");
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
					vector<T> vector;
					T tmp_1 = _array.at(1) * -1.0;
					T tmp_2 = _array.at(0);

					T x = tmp_1 / pow((pow(tmp_1, 2) + pow(tmp_2, 2)), 0.5);
					T y = tmp_2 / pow((pow(tmp_1, 2) + pow(tmp_2, 2)), 0.5);
					vector.push_back(x);
					vector.push_back(y);

					return TemplateVector(size, vector, 0);
				}
				else
				{
					vector<T> vector;
					for (size_t i = 1; i < size - 1; ++i)
					{
						if (i % 2 != 0)
						{
							vector.push_back( - 1 * _array.at(i + 1));
						}

						else
						{
							vector.push_back(_array.at(i - 1));
						}
					}



					T summ = 0;
					for (size_t j = 0; j < size - 1; ++j)
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
				if (size < 2) throw  ("Sizes less than 2");
				else
				{
					vector<T> vector;
					for (size_t i = 1; i < size; ++i)
					{
						if (i % 2 != 0)
						{
							vector.push_back(_array.at(i + 1));
						}

						else
						{
							vector.push_back( - 1 * _array.at(i - 1));
						}
					}

					T summ = 0;
					for (size_t j = 0; j < size - 1; ++j)
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
		if (size != v.size)throw ("Sizes are't equal!");

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
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator + (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) + v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] + v._array[i];
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator += (const TemplateVector<T>& v) const
	{
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) + v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<complex<T>>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v._array.at(i));
		}
		return obj;
	}

	TemplateVector<complex<T>> operator - (const TemplateVector<T>& v) const
	{
		TemplateVector<complex<T>> obj(size);
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) - v[i]);
		}
		return obj;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<complex<T>>& v) const
	{
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) - v[i]);
		}
		return *this;
	}

	TemplateVector<complex<T>>& operator -= (const TemplateVector<T>& v) const
	{
		if (size != v.get_size())throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			this->_array.emplace(i, _array.at(i) - v[i]);
		}
		return *this;
	}

	complex<T> operator * (const TemplateVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.size)throw ("Sizes are't equal!");
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array.at(i) * conj(v[i]); //a= [z1,z2,z3] b= [z4,z5,z6] multi += z1*z4
		}
		return multiplication;
	}

	complex<T> operator * (const TemplateVector<T>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ("Sizes are't equal!");
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
		if (s == 0) throw (" division by zero");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	TemplateVector<complex<T>> operator / (const complex<T> s) const
	{
		TemplateVector<complex<T>> obj(size);
		if (s.real() == 0 && s.imag() == 0) throw (" division by zero");
		for (size_t i = 0; i < size; ++i)
		{
			obj._array.push_back(_array.at(i) / s);
		}
		return obj;
	}

	complex<T> operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ("Invalid index!");
		return _array.at(i);
	}

	complex<T>& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ("Invalid index!");
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
				vector<complex<T>>v;
				complex<T> tmp_1 = _array.at(1) * -1.0;
				complex<T> tmp_2 = _array.at(0);

				complex<T> x = tmp_1 / pow((pow(tmp_1, 2) + pow(tmp_2, 2)), 0.5);
				complex<T> y = tmp_2 / pow((pow(tmp_1, 2) + pow(tmp_2, 2)), 0.5);
				v.push_back(x);
				v.push_back(y);

				return TemplateVector<complex<T>>(size, v, 0);
				
			}
			else
			{
				vector<complex<T>>vec;
				for (size_t i = 1; i < size - 1; ++i)
				{
					if (i % 2 != 0)
					{
						vec.push_back( - 1.0 * _array.at(i + 1));
					}

					else
					{
						vec.push_back (_array.at(i - 1));
					}
				}



				complex<T> summ = 0;
				for (size_t j = 0; j < size - 1; ++j)
				{
					summ += pow(vec[j], 2);
				}


				for (size_t i = 1; i < size - 1; ++i)
				{
					vec.push_back( vec[i] / pow(summ, 0.5));
				}

				return TemplateVector<complex<T>>(size, vec, 0);
			}
		}
		if (size % 2 != 0)
		{
			if (size < 2) throw  ("Sizes less than 2");
			else
			{
				vector<complex<T>>vec;
				for (size_t i = 1; i < size; ++i)
				{
					if (i % 2 != 0)
					{
						vec.push_back(_array.at(i + 1));
					}

					else
					{
						vec.push_back( - 1.0 * _array.at(i - 1));
					}
				}
				complex<T> summ = 0;
				for (size_t j = 0; j < size - 1; ++j)
				{
					summ += pow(vec[j], 2);
				}

				for (size_t i = 1; i < size; ++i)
				{
					vec.push_back(vec[i] / pow(summ, 0.5));
				}
				
				TemplateVector<complex<T>> obj(size, vec, 0);

				return obj;
			}

		}
	}
};


int main()
{
	try 
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


		complex<double>  z1(0, 0), z2(3, 4), z3(5, 6), z4(7, 8), z5(9, 10), z6(11, 12);
		vector<complex<double>> arr = { z1, z2, z3 }, arr2 = { z4, z5, z6 };
		TemplateVector<complex<double>> complexv(3, arr, 0.5), complexv2(3, arr2, 0.5);
		cout << "complexv : " << complexv << endl;
		cout << "complexv2 : " << complexv2 << endl;

		complex<double> resultofmult = complexv * complexv2;
		cout << "test of multi : " << resultofmult << endl;
		complex<double> multi_of_double_and_complex = f_v * complexv;
		cout << "test multi_of_double_and_complex : " << multi_of_double_and_complex << endl;
		TemplateVector<complex<double>> division = complexv / z1;
		cout << "test division:" << division << endl;

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
	}
	catch (const char* r)
	{
		cout << r << endl;
	}


	return 0;
}
