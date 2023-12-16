#include "ExpectationExistsPattern.h"

namespace ExpectationLib
{
	ExpectationExistsPattern::ExpectationExistsPattern(
		const std::shared_ptr<StimuliProducesResponseExpectation>& stimuliProducesResponseExpectation,
		const std::vector<std::shared_ptr<Observation>>& observations)
	{
		this->stimuliProducesResponseExpectation = stimuliProducesResponseExpectation;
		this->Observations = observations;
	}

	bool ExpectationExistsPattern::Match()
	{
		for (auto o = 0; o < Observations.size(); o++) 
		{
			if (Observations[o]->GetStimulus()->GetSender()->GetId() == stimuliProducesResponseExpectation->GetStimulus()->GetSender()->GetId() &&
				Observations[o]->GetStimulus()->GetReceiver()->GetId() == stimuliProducesResponseExpectation->GetStimulus()->GetReceiver()->GetId() &&
				Observations[o]->GetResponse()->GetId() == stimuliProducesResponseExpectation->GetResponse()->GetId())
			{
				lastMatchedObservationIndex = o;
				return true;
			}
		}
		return false;
	}

	int ExpectationExistsPattern::GetLastProcessedObservationIndex()
	{
		return lastMatchedObservationIndex;
	}
}
