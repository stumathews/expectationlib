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
		virtual void Observe(const std::shared_ptr<ContactCircumstance>& circumstance) = 0;
	};
}
