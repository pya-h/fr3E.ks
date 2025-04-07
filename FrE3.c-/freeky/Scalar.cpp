
#include <sstream>
#include "Scalar.h"
#include <iostream>

namespace Freeky
{
	
	Scalar::Scalar(long num)
	{
		value = std::to_string(num);
	}
	Scalar::Scalar(int num)
	{
		value = std::to_string(num);

	}
	Scalar::Scalar(float num)
	{
		value = std::to_string(num);

	}
	Scalar::Scalar(double num)
	{
		value = std::to_string(num);

	}
	Scalar::Scalar(long double num)
	{
		value = std::to_string(num);

	}

	Scalar::Scalar(const char num[])
	{
		value = std::string(num);
	}

	Scalar::Scalar(std::string num)
	{
		value = num;
	}

	Scalar::Scalar(String num)
	{
		value = num.toString();
	}

	Scalar& Scalar::operator=(Scalar& right)
	{
		value = right.$();
		return *this;
	}

	char Scalar::operator[](long index)
	{
		return value[index];
	}

	std::string Scalar::$()
	{
		return value;
	}


	Scalar Scalar::operator+(Scalar& right)
	{

		// IN DECIMAL NUMBERS , THE ADDITION SEQUENCE MUST BE SYNCRONIZED BY THE "." CHAR POSITION
		std::string result = "";
		//Scalar r();
		long idx = ~(*this) - 1, idy = ~right - 1;

		int carry = 0;
		char digit;
		for (; idx >= 0 && idy >= 0; idx--, idy--) {
			digit = value[idx] + right[idy] - '0' + carry;
			carry = 0;
			if (digit > '9')
			{
				digit -= 10;
				carry++;
			}
			result = digit + result;
		}
		for (; idx >= 0; digit = (value[idx] + carry), result = digit + result, idx--, carry = 0);
		for (; idy >= 0; digit = (value[idy] + carry), result = digit + result, --idy, carry = 0);

		//Scalar r(result);
		return Scalar(result);
	}

	long operator~(Scalar& right)
	{
		return right.$().length();
	}

	std::istream& operator>>(std::istream& in, Scalar sc)
	{
		in >> sc;
		return in;
	}

	std::ostream& operator<<(std::ostream& out, Scalar sc)
	{
		out << sc.$();
		return out;
	}

}
