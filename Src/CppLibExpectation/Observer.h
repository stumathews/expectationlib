#pragma once
#include <vector>
#include "IObserver.h"

namespace ExpectationLib
{
	class Observer final : IObserver
	{
	public:
		std::vector<std::shared_ptr<Observation>> Observations;
		std::shared_ptr<Observation> Observe(const std::shared_ptr<ICircumstance>& circumstance, std::string observationContext = "") override;
		std::shared_ptr<Observation> Observe(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response, const std::string& observationContext = "") override;
	};
}
