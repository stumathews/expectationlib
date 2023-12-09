#include "pch.h"
#include "Observer.h"

namespace ExpectationLib
{
	void Observer::Observe(const std::shared_ptr<ContactCircumstance>& circumstance)
	{
		Observations.push_back(circumstance);
	}
}
