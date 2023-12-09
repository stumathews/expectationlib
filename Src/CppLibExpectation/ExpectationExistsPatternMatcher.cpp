#include "pch.h"
#include "ExpectationExistsPatternMatcher.h"

namespace ExpectationLib
{
	ExpectationExistsPatternMatcher::ExpectationExistsPatternMatcher(
		const std::shared_ptr<StimuliProducesResponseExpectation>& stimuliProducesResponseExpectation,
		const std::vector<std::shared_ptr<Observation>>& observations)
	{
		this->stimuliProducesResponseExpectation = stimuliProducesResponseExpectation;
		this->Observations = observations;
	}

	bool ExpectationExistsPatternMatcher::Match()
	{
		for (const auto& o : Observations) 
		{
			if (o->GetStimulus()->GetSender()->GetId() == stimuliProducesResponseExpectation->GetStimulus()->GetSender()->GetId() &&
				o->GetStimulus()->GetReceiver()->GetId() == stimuliProducesResponseExpectation->GetStimulus()->GetReceiver()->GetId() &&
				o->GetResponse()->GetId() == stimuliProducesResponseExpectation->GetResponse()->GetId())
			{
				return true;
			}
		}
		return false;
	}
}
