#include "StimuliProducesResponseExpectation.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "IParty.h"

namespace ExpectationLib
{
	StimuliProducesResponseExpectation::StimuliProducesResponseExpectation(const std::shared_ptr<IStimulus>& stimulus)
	{
		this->stimulus = stimulus;
		this->response = stimulus->GetResponse();
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

	std::string StimuliProducesResponseExpectation::CreateId(const std::shared_ptr<IStimulus>& stimuli)
	{
		return stimuli->GetSender()->GetId() + stimuli->GetReceiver()->GetId() + stimuli->GetResponse()->GetId();
	}

	bool StimuliProducesResponseExpectation::Match(const std::shared_ptr<Observation> observation)
	{
		const auto observationStimulus = observation->GetStimulus();
		const auto observationStimulusSender =  observationStimulus->GetSender();
		const auto observationStimulusReceiver =  observationStimulus->GetReceiver();

		const auto sendersMatch =  observationStimulus->GetSender()->GetRole() == stimulus->GetSender()->GetRole() &&
			                            observationStimulus->GetSender()->GetId() == stimulus->GetSender()->GetId();
		const auto receiversMatch = observationStimulusReceiver->GetRole() == stimulus->GetReceiver()->GetRole() &&
			                             observationStimulusReceiver->GetId() == stimulus->GetReceiver()->GetId();
		const auto responseMatches = observation->GetResponse()->GetId() == response->GetId();

		bool matched = false;
		observation->GetResponse()->GetResult().Match(
			[&](libmonad::None none) { matched = false; },
			[&](const std::shared_ptr<IResult>& result)
			{
				const auto hasExpectedRelations = 
				result->GetSender()->HasRelationTo(observationStimulusReceiver, ContactResponse::ContactRelationName) &&
				result->GetReceiver()->HasRelationTo(observationStimulusSender, ContactResponse::ContactRelationName);

				matched = sendersMatch && receiversMatch && responseMatches && hasExpectedRelations;
			});
		return matched;
		
		
	}

	const std::string StimuliProducesResponseExpectation::GetId()
	{
	    return CreateId(stimulus);
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
