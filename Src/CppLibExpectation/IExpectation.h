#pragma once
#include "Observation.h"

namespace ExpectationLib
{
	class IExpectation
	{
		public:
		virtual ~IExpectation() = default;
		virtual bool Match(std::shared_ptr<Observation> observation) = 0;
		virtual std::string ToString() = 0;
	};
}
