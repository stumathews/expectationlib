#include "pch.h"
#include "Observer.h"

namespace ExpectationLib
{
	std::shared_ptr<Observation> Observer::Observe(const std::shared_ptr<ICircumstance>& circumstance,
	                                               const std::string context = "")
	{
		return Observe(circumstance->GetStimulus(), circumstance->GetResponse(), context);
	}

	std::shared_ptr<Observation> Observer::Observe(const std::shared_ptr<IStimulus>& stimulus,
	                                               const std::shared_ptr<IResponse>& response,
	                                               const std::string& context = "")
	{
		auto observation = std::make_shared<Observation>(stimulus, response, context);
		Observations.push_back(observation);
		return observation;
	}
}
