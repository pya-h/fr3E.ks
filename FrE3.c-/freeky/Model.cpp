#include "Model.h"

namespace Freeky 
{
	// Method
	

	// Memento
	auto Memento::look(String member)
	{
		// check if member exists in memblinks key values
		// then return the auto value
		const int count = memblink.count(member);
		if (count > 0)
		{
			switch (memblink[member]) {
			case $_F32_$:
				return f32[member];
			//case $_I32$:
			//	return i32[member];
		//use std:: any???
			}
		}

	}


}
