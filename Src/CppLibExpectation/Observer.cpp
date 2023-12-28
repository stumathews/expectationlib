#include "Observer.h"

namespace ExpectationLib
{
	std::shared_ptr<Observation> Observer::Observe(const std::shared_ptr<ICircumstance>& circumstance,
	                                               const std::string observationContext)
	{
		return Observe(circumstance->GetStimulus(), circumstance->GetResponse(), observationContext);
	}

	std::shared_ptr<Observation> Observer::Observe(const std::shared_ptr<IStimulus>& stimulus,
	                                               const std::shared_ptr<IResponse>& response,
	                                               const std::string& observationContext)
	{
		auto observation = std::make_shared<Observation>(stimulus, response, observationContext);
		Observations.push_back(observation);
		return observation;
	}

	std::shared_ptr<Observation> Observer::Observe(const std::shared_ptr<IStimulus>& stimulus,
		const std::string& observationContext)
	{
		const std::shared_ptr<IResponse> stimulusResponse = stimulus->GetResponse();
		return Observe(stimulus, stimulusResponse,observationContext);
	}
}
