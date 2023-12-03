#pragma once
#include <vector>

#include "Observation.h"

namespace ExpectationLib
{	
	class ISituation
	{
	public:
	    virtual bool Match(std::vector<Observation*> observations) = 0;
	};
}
