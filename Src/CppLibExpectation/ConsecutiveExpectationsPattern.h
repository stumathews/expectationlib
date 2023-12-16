#pragma once
#include <vector>

#include "IExpectation.h"
#include "IExpectedPattern.h"
#include "Observation.h"

namespace ExpectationLib
{
	class ConsecutiveExpectationsPattern final : public BaseExpectedPattern
	{
	public:
		ConsecutiveExpectationsPattern(const std::vector<std::shared_ptr<IExpectation>>& expectations, const std::vector<std::shared_ptr<Observation>>& observations);
		bool Match() override;
		const std::vector<std::shared_ptr<IExpectation>>& expectations;
		const std::vector<std::shared_ptr<Observation>>& observations;
	};
}

