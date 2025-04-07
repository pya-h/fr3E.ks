
#ifndef SCALAR_H
#define SCALAR_H

#include <vector>
#include <string>
#include "String.h";

namespace Freeky
{
	class Scalar {
	private:
		std::string value;
	public:
		Scalar() { value = ""; };
		Scalar(long num);
		Scalar(int num);
		Scalar(float num);
		Scalar(double num);
		Scalar(long double num);
		Scalar(const char num[]);
		Scalar(std::string num);
		Scalar(String num);

		//Scalar& operator+(Scalar& ) ;
		Scalar operator+(Scalar&);

		Scalar& operator=(Scalar& right);

		friend long operator~(Scalar& right);
		char operator[](long);

		friend std::istream& operator>> (std::istream& in, Scalar);
		friend std::ostream& operator<<(std::ostream& out, Scalar);

		std::string $();
	};
}
SCALAR_H // !EXPRESSION_H
#endif