#pragma once
#include <vector>

#include "Observation.h"

namespace ExpectationLib
{
	// A situation is a specific coordinated collection circumstances
	class ISituation
	{
	public:
		virtual ~ISituation() = default;

		// Determines if this situation matches the observations
		virtual bool Match(std::vector<std::shared_ptr<Observation>> observations) = 0;
	};
}
