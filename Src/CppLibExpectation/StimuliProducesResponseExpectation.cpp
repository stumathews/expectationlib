#include "pch.h"
#include "StimuliProducesResponseExpectation.h"

namespace ExpectationLib
{
	StimuliProducesResponseExpectation::StimuliProducesResponseExpectation(const std::shared_ptr<IStimulus>& stimuli, const std::shared_ptr<IResponse>& response)
	{
		this->stimulus = stimuli;
		this->response = response;
	}

	StimuliProducesResponseExpectation::StimuliProducesResponseExpectation(const std::shared_ptr<ICircumstance>& circumstance)
	{
		stimulus = circumstance->GetStimulus();
		response = circumstance->GetResponse();
	}

	std::string StimuliProducesResponseExpectation::Id() const
	{
		return CreateId(stimulus, response);
	}

	std::string StimuliProducesResponseExpectation::ToString()
	{
		return stimulus->ToString() + " (Context: " + response->ToString() + ")";
	}

	std::string StimuliProducesResponseExpectation::CreateId(const std::shared_ptr<IStimulus>& stimuli, const std::shared_ptr<IResponse>& response)
	{
		return stimuli->GetSender()->GetId() + stimuli->GetReceiver()->GetId() + response->GetId();
	}

	bool StimuliProducesResponseExpectation::Match(const std::shared_ptr<Observation> observation)
	{
		return observation->GetStimulus()->GetSender() == stimulus->GetSender() &&
			observation->GetStimulus()->GetReceiver() == stimulus->GetReceiver() &&
			observation->GetResponse() == response;
	}

	std::string StimuliProducesResponseExpectation::GetId()
	{
	    return Id();
	}

	std::shared_ptr<IStimulus> StimuliProducesResponseExpectation::GetStimulus()
	{
		return stimulus;
	}

	std::shared_ptr<IResponse> StimuliProducesResponseExpectation::GetResponse()
	{
		return response;
	}
}
