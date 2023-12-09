#pragma once
#include "Observation.h"

namespace ExpectationLib
{
	class IExpectation
	{
		public:
		virtual ~IExpectation() = default;
		virtual bool Match(std::shared_ptr<Observation> observation) = 0;

		// string representation of an expectation for identification purposes
		virtual std::string ToString() = 0;
	};
}
