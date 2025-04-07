#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "String.h"
#include <vector>

namespace Freeky
{
	typedef enum {
		Assign,
		Write,
		Read,
		Loop,
		Check,
		// ...
	} Instructions;

	class Expression {
		private:
			String StrValue;
			std::vector <String> words;
			Expression *next, *block;
		public:
			Expression(String);
			Expression(std::string);
			Expression(const char exp[]);
			long int length() { return words.size(); };

			Instructions indentify(); // identify the expression type by its checking value;

			Expression& operator+(Expression& const right);
			Expression& operator+(String& const right);
			Expression& operator+(const std::string& right);
			Expression& operator+(const char exp[]);
			
			String operator[] (long int index);
			Expression *last();
			std::vector <String> getWords() { return words; };
			friend std::vector <String> operator*(Expression exp) { return exp.getWords(); };

			friend String* operator~(Expression); // convert vector words to dynamic array
			String Stringify();
			inline String type() { return "Expression"; }

	};
}
#endif // !EXPRESSION_H

