
#include "String.h"
#include "Expression.h"

namespace Freeky
{
	Expression::Expression(String exp)
	{
		StrValue = exp;
		words = exp.split();
		next = block = nullptr;
	}
	Expression::Expression(std::string exp)
	{
		StrValue = exp;
		words = String(exp).split();
		next = block = nullptr;
	}

	Expression::Expression(const char exp[])
	{
		StrValue = exp;
		words = String(exp).split();
		next = block = nullptr;
	}

	Instructions Expression::indentify()
	{
		// check words
		return Instructions::Assign;
	}
	Expression& Expression::operator+(Expression& const right)
	{
		next = new Expression(right.Stringify());
		return *this;
	}
	Expression& Expression::operator+(String& const right)
	{
		next = new Expression(right);
		return *this;
	}
	Expression& Expression::operator+(const std::string& right)
	{
		next = new Expression(right);
		return *this;
	}
	Expression& Expression::operator+(const char right[])
	{
		next = new Expression(right);
		return *this;
	}

	String Expression::operator[](long int index)
	{
		const long int len = length();
		if (index >= 0)
		{
			if (index >= len)
			{
				String outOfRange("Out of Range!");
				return outOfRange;
			}
			return words[index];
		}
		else 
		{
			if (index * -1 > len)
			{
				String outOfRange = "Out of Range!";
				return outOfRange;
			}
			return words[len + index];
		}
	}

	Expression* Expression::last()
	{
		Expression* current = this;
		while (current->next != nullptr) current = current->next;
		return current;
	}

	String Expression::Stringify()
	{
		String result = StrValue;
		Expression* c = this;
		while (c->next != nullptr)
		{
			if (c->block)
				result += "\t" + c->block->Stringify() + "\n";
			result += c->next->Stringify() + "\n";
		}
		// block;
		return result;
	}

	String* operator~(Expression exps)
	{
		const std::vector <String> wordsOfExp = *exps;
		int sze = exps.length();
		String* arrWords = new String[sze];
		for (int i = 0; i < sze; i++)
			arrWords[i] = *wordsOfExp[i];
		return arrWords;
	}

}