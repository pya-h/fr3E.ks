#pragma once
#ifndef String_h
#define String_h
#include <string>
#include <vector>
#include <istream>

namespace Freeky
{
	enum Character {
		EndLine = '\n',
		Tab = '\t',
		Space = ' ',
		BackSpace = '\b',
		Return = '\r',
		BackSlash = '\\',
		Quatation = '\'',
		DoubleQuatation = '\"',
		Dot = '.'
	};

	class String {
		private:
			std::string value;
		public:
			String();
			String(std::string v);
			String(const char v[]);
			String(const char);
			String(int);
			String(long);
			String(float);
			String(double);
			String(long double);

			//String(String& const StrV);

			std::vector<String> split(char seperator = Character::Space);

			std::string toString();
			
			String operator+(String right);
			friend String operator+(std::string left, String right);
			String operator+(const std::string& right);
			String operator+(const char right[]);
			String operator+(const char right);
			//friend String operator+(const char right, String s);
			
			String operator+(const int);
			String operator+(const float);
			String operator+(const double);
			String operator+(const bool);

			String operator-(String& const right);
			String operator-(const std::string& right);
			String& operator-(const char right);

			String operator|(String right);
			friend String operator|(std::string, String);
			String operator|(const std::string& right);
			String operator|(const char str[]);
			String operator|(const bool);
			String operator|(const int);
			String operator|(const float);
			String operator|(const double);

			bool operator,(String);

			String operator*(const bool);
			String operator*(const int);

			String& operator=(String right);
			String& operator=(const std::string& right);
			String& operator=(const char right[]);

			//String& operator+=(String right);
			String& operator+=(String right);
			//String& operator+=(String& const right);
			String& operator+=(const std::string& right);
			String& operator+=(const char right[]);
			String& operator+=(const int x);
			String& operator+=(const float x);
			String& operator+=(const double x);

			// connect strings with space seperator (if needed)
			String& operator|=(String right);
			String& operator|=(const std::string& right);
			String& operator|=(const char right[]);
			String& operator|=(const bool);
			String& operator|=(const int x);
			String& operator|=(const float x);
			String& operator|=(const double x);
			
			String& operator*=(const int);
			String& operator*=(const bool);
			char& operator[](long int index);
			String operator()(long int index);

			//bool operator() (const String& lhs, const String& rhs) const
			//{
			//	return lhs < rhs;
			//}
			friend std::string operator~(String);

			friend String operator*(String); // copy String

			friend double operator+(String);
			friend double operator+(const std::string&);
			
			friend bool operator< (String, String);
			long int operator%(char ch);
			friend long int operator%(const std::string&, char);
			
			friend std::istream& operator >> (std::istream& in, String& str);
			friend std::ostream& operator<<(std::ostream& out, String& str);
			static bool isSeperator(char ch);
			long int length();
			void print(char finisher = Character::EndLine);
			void read(String msg, char finisher = Character::EndLine);
			long i64();
			int i32();
			inline String type() { return "String"; }

			// ----------------------------------------------------------------------------
			// comparison operators
			friend inline bool operator== (String& left, String& right) {
				return left.toString().compare(right.toString()) == 0;
			}

			friend inline bool operator== (String& left, const std::string& right) {
			}

			friend inline bool operator== (String& left, const char right[]) {
				return left.toString().compare(right) == 0;
			}

			friend inline bool operator== (const std::string& left, String& right) {
				return left.compare(right.toString()) == 0;
			}

			friend inline bool operator== (const char left[], String& right) {
				return right.toString().compare(left) == 0;
			}

			friend inline bool operator== (const std::string& left, const std::string& right) {
				return left.compare(right) == 0;
			}

			friend inline bool operator< (String& left, String& right) {
				return left.toString().compare(right.toString()) < 0;
			}

			friend inline bool operator< (String& left, const std::string& right) {
				return left.toString().compare(right) < 0;
			}

			friend inline bool operator< (String& left, const char right[]) {
				return left.toString().compare(right) < 0;
			}

			friend inline bool operator< (const std::string& left, String& right) {
				return left.compare(right.toString()) < 0;
			}

			friend inline bool operator< (const char left[], String& right) {
				return right.toString().compare(left) < 0;
			}

			friend inline bool operator< (const std::string& left, const std::string& right) {
				return left.compare(right) < 0;
			}

			friend inline bool operator> (String& left, String& right) {
				return left.toString().compare(right.toString()) > 0;
			}

			friend inline bool operator> (String& left, const std::string& right) {
				return left.toString().compare(right) > 0;
			}

			friend inline bool operator> (String& left, const char right[]) {
				return left.toString().compare(right) > 0;
			}

			friend inline bool operator> (const std::string& left, String& right) {
				return left.compare(right.toString()) > 0;
			}

			friend inline bool operator> (const char left[], String& right) {
				return right.toString().compare(left) > 0;
			}

			friend inline bool operator> (const std::string& left, const std::string& right) {
				return left.compare(right) > 0;
			}

			friend inline bool operator<= (String& left, String& right) {
				return left.toString().compare(right.toString()) <= 0;
			}

			friend inline bool operator<= (String& left, const std::string& right) {
				return left.toString().compare(right) <= 0;
			}

			friend inline bool operator<= (String& left, const char right[]) {
				return left.toString().compare(right) <= 0;
			}

			friend inline bool operator<= (const std::string& left, String& right) {
				return left.compare(right.toString()) <= 0;
			}

			friend inline bool operator<= (const char left[], String& right) {
				return right.toString().compare(left) <= 0;
			}

			friend inline bool operator<= (const std::string& left, const std::string& right) {
				return left.compare(right) <= 0;
			}

			friend inline bool operator>= (String& left, String& right) {
				return left.toString().compare(right.toString()) >= 0;
			}

			friend inline bool operator>= (String& left, const std::string& right) {
				return left.toString().compare(right) >= 0;
			}

			friend inline bool operator>= (String& left, const char right[]) {
				return left.toString().compare(right) >= 0;
			}

			friend inline bool operator>= (const std::string& left, String& right) {
				return left.compare(right.toString()) > 0;
			}

			friend inline bool operator>= (const char left[], String& right) {
				return right.toString().compare(left) >= 0;
			}

			friend inline bool operator>= (const std::string& left, const std::string& right) {
				return left.compare(right) >= 0;
			}


			bool operator <(String& rhs) const
			{
				return value.compare(rhs.toString()) < 0;
			}
			bool operator >(String& rhs) const
			{
				return value.compare(rhs.toString()) > 0;
			}
			bool operator <=(String& rhs) const
			{
				return value.compare(rhs.toString()) <= 0;
			}
			bool operator >=(String& rhs) const
			{
				return value.compare(rhs.toString()) >= 0;
			}
			bool operator ==(String& rhs) const
			{
				return !value.compare(rhs.toString());
			}
			bool operator !=(String& rhs) const
			{
				return value.compare(rhs.toString());
			}
	};
}
#endif // !String_h

