#pragma once
#include <vector>

#include "IExpectedPattern.h"
#include "Observation.h"
#include "StimuliProducesResponseExpectation.h"

namespace ExpectationLib
{	
	class ExpectationExistsPattern final : public IExpectedPattern
	{
	public:
	    std::shared_ptr<StimuliProducesResponseExpectation> stimuliProducesResponseExpectation;
	    std::vector<std::shared_ptr<Observation>> Observations;

	    ExpectationExistsPattern(const std::shared_ptr<StimuliProducesResponseExpectation>& stimuliProducesResponseExpectation, const std::vector<std::shared_ptr<Observation>>& observations);

	    bool Match() override;
	    int GetLastProcessedObservationIndex() override;
	private:
		int lastMatchedObservationIndex = -1;
	};
}
