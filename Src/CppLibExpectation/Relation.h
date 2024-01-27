#pragma once
#include <memory>
#include <string>

#include "Option.h"

namespace ExpectationLib
{
	class IParty;

	class Relation
	{
	public:
		Relation(std::string name, std::shared_ptr<IParty> to, std::string& context, libmonad::Option<unsigned long> startTime, libmonad::Option<unsigned long> endTime);
		std::string Name;
		std::string Context;
		std::shared_ptr<IParty> To;
		libmonad::Option<unsigned long> StartTime;
		libmonad::Option<unsigned long> EndTime;
		[[nodiscard]] std::string GetId() const;
	};
}
