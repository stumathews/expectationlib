#pragma once
#include <vector>

#include "IExpectation.h"
#include "IExpectedObservationsPattern.h"
#include "Observation.h"

namespace ExpectationLib
{
	class ConsecutiveExpectations : public IExpectedObservationsPattern
	{
	public:
		ConsecutiveExpectations(const std::vector<std::shared_ptr<IExpectation>>& expectations, const std::vector<std::shared_ptr<Observation>>& observations);
		bool Match() override;
		const std::vector<std::shared_ptr<IExpectation>>& expectations;
		const std::vector<std::shared_ptr<Observation>>& observations;
	};
}

