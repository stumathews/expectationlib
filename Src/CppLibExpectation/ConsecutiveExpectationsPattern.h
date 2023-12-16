#pragma once
#include <vector>

#include "IExpectation.h"
#include "IExpectedPattern.h"
#include "Observation.h"

namespace ExpectationLib
{
	class ConsecutiveExpectationsPattern : public IExpectedPattern
	{
	public:
		ConsecutiveExpectationsPattern(const std::vector<std::shared_ptr<IExpectation>>& expectations, const std::vector<std::shared_ptr<Observation>>& observations);
		bool Match() override;
		int GetLastProcessedObservationIndex() override;
		const std::vector<std::shared_ptr<IExpectation>>& expectations;
		const std::vector<std::shared_ptr<Observation>>& observations;
	private:
		int lastMatchedObservationIndex = -1;
	};
}

