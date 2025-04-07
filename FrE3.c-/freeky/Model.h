#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "String.h"
#include <vector>
#include <map>
#include "Expression.h";

namespace Freeky
{

	typedef enum {
		$_I8_$,
		$_I16_$,
		$_I32$,
		$_I64_$,
		$_F32_$,
		$_F64_$,
		$_F96_$,
		$_TEXT_$,
		$_SWITCH_$,
		$_BATCH_$,
		$_METHOD_$,
		$_FUNCTION_$,
		$_NADA_$,
		$_ALIEN_$
	} TYPES;

	class Method
	{
	private:
		String name;
		Expression* duty;
		//std::map <String, Memento> localVariables;
	public:
		void execute();

	};
	// memory manager
	class Memento
	{
		// ADD ALL DATA TYPES LIST IN MEMENTO
	// FROM THGE MOMENT A VARIABLE IS DERFINED USE THE BEST AND MIMUM MEMORY NEEDED TO SAVE THE VALUE
	// WHEN THE NUMBER IS LARGER THAN THE CURRENT DATA TYPE (FOR EX: SHORT INT VS INT), THEN SHIFT THE VARTIABLE TO LARGER SCOPE
	private:
		std::map <String, char> i8;
		std::map <String, short int> i16;
		std::map <String, int> i32;
		std::map <String, long long int> i64;
		std::map <String, float> f32;
		std::map <String, double> f64;
		std::map <String, long double> f96;
		std::map <String, String> text;
		std::map <String, bool> switches;
		std::map <String, Method> methods;
		std::map <String, TYPES> memblink; // member type linkings
		std::map <String, Memento> objects;
	public:
		auto look(String);
		
	};
}
#endif // !MODEL_H