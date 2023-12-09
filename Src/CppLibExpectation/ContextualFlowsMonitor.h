#pragma once
#include <map>
#include <string>
#include "Observer.h"

namespace ExpectationLib
{
	class ContextualFlowsMonitor
	{
	public:
	    static std::map<std::string, std::shared_ptr<Observer>> Overseers;
	    static std::shared_ptr<Observer> GetOverseer(const std::string& context);
	    static void RemoveOverseer(const std::string& context);
	};

}
