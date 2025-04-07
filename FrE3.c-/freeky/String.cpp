#include "String.h"
#include <sstream>
#include <iostream>
#include <ostream>
#include <istream>
#include "String.h"

namespace Freeky
{
	String::String()
	{
		value = "";
	}
	String::String(std::string v)
	{
		value = v;
	}
	String::String(const char v[])
	{
		value = std::string(v);
	}

	String::String(const char x)
	{
		value = { x };
	}

	String::String(int x)
	{
		value = std::to_string(x);
	}

	String::String(long x)
	{
		value = std::to_string(x);
	}

	String::String(float x)
	{
		value = std::to_string(x);
	}

	String::String(double x)
	{
		value = std::to_string(x);
	}
	
	String::String(long double x)
	{
		value = std::to_string(x);
	}

	std::vector <String> String::split(char seperator)
	{
		std::vector <String> result;
		std::stringstream rawStream(value);
		std::string segment;
		while (std::getline(rawStream, segment, seperator))
		{
			result.push_back(segment);
		}
		return result;
	}

	std::string String::toString()
	{
		return value;
	}

	String String::operator+(String right)
	{
		return toString() + right.toString();
	}

	String String::operator+(const std::string& right)
	{
		return toString() + right;
	}

	String String::operator+(const char right[])
	{
		return toString() + " " + std::string(right);
	}

	String String::operator+(const char right)
	{
		return toString() + " " + String(right);
	}

	String String::operator+(const int x)
	{
		return toString() + std::to_string(x);
	}

	String String::operator+(const float x)
	{
		return toString() + std::to_string(x);
	}

	String String::operator+(const double x)
	{
		return toString() + std::to_string(x);
	}

	String String::operator+(const bool x)
	{
		return toString() + (x ? "true" : "false");
	}

	String& String::operator-(const char right)
	{
		String result = "";
		for (int i = 0; value[i]; i++)
			if (value[i] != right)
				result += String(value[i]);
		std::cout << result;
		return result;
	}

	String String::operator|(String right)
	{
		std::string rightValue = right.toString();
		const long int l = length();
		return l== 0 || (!isSeperator(value[l - 1]) && !isSeperator(rightValue[0])) ? (value + " " + rightValue) : (value + rightValue);

	}
	
	String operator|(const std::string& left, String& const right)
	{
		std::string rightValue = right.toString();
		const long int l = left.length();
		return l == 0 || (!String::isSeperator(left[l - 1]) && !String::isSeperator(rightValue[0])) ? (left + " " + rightValue) : (left + rightValue);

	}

	String String::operator|(const std::string& right)
	{
		const long int l = length();
		return l == 0 || (!isSeperator(value[l - 1]) && !isSeperator(right[0])) ? (value + " " + right) : (value + right);
	}

	String String::operator|(const char right[])
	{
		const long int l = length();
		return l == 0 || (!isSeperator(value[l - 1]) && !isSeperator(right[0])) ? (value + " " + std::string(right)) : (value + std::string(right));
	}

	String String::operator|(const bool x)
	{
		return *this | (x ? "true" : "false");
	}

	String String::operator|(const int x)
	{
		return *this | String(x);
	}

	String String::operator|(const float x)
	{
		return *this | String(x);
	}

	String String::operator|(const double x)
	{
		return *this | String(x);
	}

	bool String::operator,(String type)
	{
		if (type == "int")
		{
			int i = 0;
			for (; value[i] && value[i] >= '0' && value[i] <= '9'; i++);
			return i >= length();
		}
		else if (type == "num")
		{
			int i = 0, numberOfDots = 0, StrLen = length();
			for (; value[i] && numberOfDots <= 1 && ((value[i] >= '0' && value[i] <= '9') || value[i] == '.'); i++)
				if (value[i] == '.') numberOfDots++;
			return i >= StrLen && (numberOfDots == 0 || StrLen >= 2);
		}
		else if (type == "dec")
		{
			int i = 0, numberOfDots = 0, StrLen = length();
			for (; value[i] && numberOfDots <= 1 && ((value[i] >= '0' && value[i] <= '9') || value[i] == '.'); i++)
				if (value[i] == '.') numberOfDots++;
			return i >= StrLen && (numberOfDots == 1 && StrLen >= 2 && value[StrLen - 1] != Character::Dot);
		}
	}

	String String::operator*(const int numberOfRepeat)
	{
		String newString = String();
		if (!numberOfRepeat) return newString;
		newString = value;
		for (int i = 1; i < numberOfRepeat; i++, newString |= value);
		return newString.toString();
	}

	String String::operator*(const bool x)
	{
		return (x ? *this : "");
	}

	String& String::operator=(String right)
	{
		value = right.toString();
		return *this;
	}

	String& String::operator=(const std::string& right)
	{
		value = right;
		return *this;
	}

	String& String::operator=(const char right[])
	{
		value = std::string(right);
		return *this;
	}

	String& String::operator+=(String right)
	{
		*this = *this + right.toString();
		return *this;
	}

	//String& String::operator+=(String& const right)
	//{
	//	*this = *this + right;
	//	return *this;
	//}

	String& String::operator+=(const std::string& right)
	{
		*this = *this + right;
		return *this;
	}

	String& String::operator+=(const char right[])
	{
		*this = *this + std::string(right);
		return *this;
	}

	String& String::operator+=(const int x)
	{
		*this = *this + std::to_string(x);
		return *this;
	}

	String& String::operator+=(const float x)
	{
		*this = *this + std::to_string(x);
		return *this;
	}

	String& String::operator+=(const double x)
	{
		*this = *this + std::to_string(x);
		return *this;
	}


	String& String::operator|=(String right)
	{
		*this = *this | right;
		return *this;
	}

	String& String::operator|=(const std::string& right)
	{
		*this = *this | right;
		return *this;
	}

	String& String::operator|=(const char right[])
	{
		*this = *this | right;
		return *this;
	}

	String& String::operator|=(const bool right)
	{
		*this = *this | right;
		return *this;
	}

	String& String::operator|=(const int x)
	{
		*this = *this | String(x);
		return *this;
	}

	String& String::operator|=(const float x)
	{
		*this = *this | String(x);
		return *this;
	}

	String& String::operator|=(const double x)
	{
		*this = *this | String(x);
		return *this;
	}

	String& String::operator*=(const bool right)
	{
		*this = *this * right;
		return *this;
	}

	char& String::operator[](long int index)
	{
		const int len = value.length();
		return value[index >= 0 ? index : len + index];
	}

	String String::operator()(long int index)
	{
		String r = value[index];
		return r;
	}

	String& String::operator*=(const int numberOfRepeates)
	{
		*this = *this * numberOfRepeates;
		return *this;
	}

	//bool String::operator<(String s)
	//{
	//	return value.compare(s.toString()) < 0;
	//}

	long int String::operator%(char ch)
	{
		int i = 0;
		for (; value[i] && value[i] != ch; i++);
		return i < length() ? i : -1;
	}

	bool String::isSeperator(char ch)
	{
		return ch == Character::Space || ch == Character::Tab || ch == Character::EndLine;
	}

	long int String::length()
	{
		int i = 0;
		for (i = 0; value[i]; i++);
		return i;
	}

	void String::print(char finisher)
	{
		std::cout << toString() << finisher;
	}

	void String::read(String msg, char finisher)
	{
		std::cout << "In: " << msg << finisher;
		std::getline(std::cin, value);
	}

	String operator+(std::string left, String right)
	{
		return left + right.toString();
	}

	//String operator+(const char right, String s)
	//{
	//	return String(s) + s;
	//}

	String operator|(std::string left, String right)
	{
		return String(left) | right;
	}


	std::string operator~(String Str)
	{
		
		return Str.toString();

	}

	long String::i64()
	{

		std::stringstream ss;

		long int num = 0;
		ss << value;
		ss >> num;
		return num;

	}


	int String::i32()
	{

		std::stringstream ss;
		int num = 0;
		ss << value;
		ss >> num;
		return num;

	}

	String operator*(String source)
	{
		String str(source.toString());
		return str;
	}

	double operator+(String Str)
	{
		std::stringstream ss;
		double num = 0.0;
		ss << Str;
		ss >> num;
		return num;
	}

	double operator+(const std::string& str)
	{
		return +String(str);
		
	}

	bool operator<(String s1, String s2)
	{
		return s1.toString().compare(s2.toString()) < 0;
	}

	long int operator%(const std::string& str, char ch)
	{
		return String(str) % ch;
	}

	std::istream& operator>>(std::istream& in, String& str)
	{
		in >> str;
		return in;
	}

	std::ostream& operator<<(std::ostream& os, String& str)
	{
		os << str.toString();
		return os;
	}


}