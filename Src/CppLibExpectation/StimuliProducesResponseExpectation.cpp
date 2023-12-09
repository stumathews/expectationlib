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
		const auto sendersMatch = observation->GetStimulus()->GetSender()->GetRole() == stimulus->GetSender()->GetRole() &&
			                           observation->GetStimulus()->GetSender()->GetId() == stimulus->GetSender()->GetId();
		const auto receiversMatch = observation->GetStimulus()->GetReceiver()->GetRole() == stimulus->GetReceiver()->GetRole() &&
			                             observation->GetStimulus()->GetReceiver()->GetId() == stimulus->GetReceiver()->GetId();
		const auto responseMatches = observation->GetResponse()->GetContext() == response->GetContext();

		return sendersMatch && receiversMatch && responseMatches;
	}

	std::string StimuliProducesResponseExpectation::GetId()
	{
	    return CreateId(stimulus, response);
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
