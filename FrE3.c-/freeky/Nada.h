#pragma once
#ifndef Nada_h
#define Nada_h

#include "String.h"
#include <vector>

// nothing value
namespace Freeky
{
	
	class Nada {
		private:
			String err;
		public:
			
			inline String type() { return "Nada";  }
	};
}
#endif // !Nada_h

