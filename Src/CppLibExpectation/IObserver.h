#pragma once
#include <string>

#include "IResponse.h"
#include "IStimulus.h"
#include "Observation.h"

namespace ExpectationLib
{
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual std::shared_ptr<Observation> Observe(const std::shared_ptr<ICircumstance>& circumstance, std::string context = "") = 0;
		virtual std::shared_ptr<Observation> Observe(const std::shared_ptr<IStimulus>& stimulus, const std::string& context = "") = 0;
	protected:
		
		virtual std::shared_ptr<Observation> Observe(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response, const std::string& context = "") = 0;
	};
}
