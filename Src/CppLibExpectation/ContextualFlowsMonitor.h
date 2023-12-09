#pragma once
#include <map>
#include <string>
#include "Observer.h"

namespace ExpectationLib
{
	class ContextualFlowsMonitor
	{
	public:
		static ContextualFlowsMonitor* Get();
	    std::map<std::string, std::shared_ptr<Observer>> Overseers {};
	    std::shared_ptr<Observer> GetOverseer(const std::string& context);
		void RemoveOverseer(const std::string& context);
		~ContextualFlowsMonitor();

	protected:
		static ContextualFlowsMonitor* instance;
	};

}
