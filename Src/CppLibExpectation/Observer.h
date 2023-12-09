#pragma once
#include <vector>

#include "ContactCircumstance.h"
#include "IObserver.h"

namespace ExpectationLib
{
	class Observer final : IObserver
	{
	public:
		std::vector<std::shared_ptr<ContactCircumstance>> Observations;
		void Observe(const std::shared_ptr<ContactCircumstance>& circumstance) override;
	};
}
