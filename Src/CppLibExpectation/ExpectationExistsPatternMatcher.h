#pragma once
#include <vector>

#include "IExpectedObservationsPattern.h"
#include "Observation.h"
#include "StimuliProducesResponseExpectation.h"

namespace ExpectationLib
{	
	class ExpectationExistsPatternMatcher final : public IExpectedObservationsPattern
	{
	public:
	    std::shared_ptr<StimuliProducesResponseExpectation> stimuliProducesResponseExpectation;
	    std::vector<std::shared_ptr<Observation>> Observations;

	    ExpectationExistsPatternMatcher(const std::shared_ptr<StimuliProducesResponseExpectation>& stimuliProducesResponseExpectation, const std::vector<std::shared_ptr<Observation>>& observations);

	    bool Match() override;
	};
}
