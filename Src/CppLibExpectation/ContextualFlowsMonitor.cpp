#include "pch.h"
#include "ContextualFlowsMonitor.h"

namespace ExpectationLib
{
	std::shared_ptr<Observer> ContextualFlowsMonitor::GetOverseer(const std::string& context)
	{
		if(Overseers.count(context) == 0 )
		{
			return Overseers[context];
		}
		auto overseer = std::make_shared<Observer>();
		Overseers[context] = overseer;
		return overseer;
	}

	void ContextualFlowsMonitor::RemoveOverseer(const std::string& context)
	{
		Overseers.erase(context);
	}
}
