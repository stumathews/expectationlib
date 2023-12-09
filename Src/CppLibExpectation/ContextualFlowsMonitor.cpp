#include "pch.h"
#include "ContextualFlowsMonitor.h"

namespace ExpectationLib
{
	ContextualFlowsMonitor* ContextualFlowsMonitor::Get()
	{
		if (instance == nullptr)
		{
			instance = new ContextualFlowsMonitor();
		}
		return instance;
	}
	std::shared_ptr<Observer> ContextualFlowsMonitor::GetOverseer(const std::string& context)
	{
		if(Overseers.count(context) != 0 )
		{
			return Overseers[context];
		}
		auto overseer = std::make_shared<Observer>();
		Overseers[context] = overseer;
		return overseer;
	}

	void ContextualFlowsMonitor::RemoveOverseer(const std::string& context)
	{
		Get()->Overseers.erase(context);
	}

	ContextualFlowsMonitor::~ContextualFlowsMonitor()
	{
		instance = nullptr;
	}


	ContextualFlowsMonitor* ContextualFlowsMonitor::instance = nullptr;
}
