#include "Observation.h"

namespace ExpectationLib
{
	Observation::Observation(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response, const std::string& context)
	{
		this->stimulus = stimulus;
		this->response = response;
		this->context = context;
	}

	Observation::Observation(const std::shared_ptr<ICircumstance>& circumstance, const std::string& context)
		: Observation(circumstance->GetStimulus(), circumstance->GetResponse(), context)
	{
	}

	std::string Observation::CreateId(const std::shared_ptr<IStimulus>& stimulus,
		const std::shared_ptr<IResponse>& response)
	{
		return stimulus->GetSender()->GetId() + stimulus->GetReceiver()->GetId() + response->GetFrom()->GetId() + response->GetId();
	}

	std::string Observation::GetId()
	{
		return CreateId(stimulus, response);
	}
}
