#pragma once
#include <vector>

#include "Observation.h"

namespace ExpectationLib
{	
	class ISituation
	{
	public:
		virtual ~ISituation() = default;
		virtual bool Match(std::vector<std::shared_ptr<Observation>> observations) = 0;
	};
}
