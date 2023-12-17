#include "Observation.h"

namespace ExpectationLib
{
	Observation::Observation(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response, const std::string& observationContext)
	{
		this->stimulus = stimulus;
		this->response = response;
		this->context = observationContext;
	}

	Observation::Observation(const std::shared_ptr<ICircumstance>& circumstance, const std::string& observationContext)
		: Observation(circumstance->GetStimulus(), circumstance->GetResponse(), observationContext)
	{
	}

	bool Observation::operator==(Observation& other)
	{
		return this->GetId() == other.GetId();
	}

	std::string Observation::CreateId(const std::shared_ptr<IStimulus>& stimulus,
	                                  const std::shared_ptr<IResponse>& response)
	{
		return stimulus->GetSender()->GetId() + stimulus->GetReceiver()->GetId() + response->GetFrom()->GetId() + response->GetId();
	}

	const std::string Observation::GetId()
	{
		return CreateId(stimulus, response);
	}
}
