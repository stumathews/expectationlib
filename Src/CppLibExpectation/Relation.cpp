#include "Relation.h"

#include "IParty.h"

namespace ExpectationLib
{
	Relation::Relation(std::string name, std::shared_ptr<IParty> to, std::string& context,
	                   const libmonad::Option<unsigned long> startTime,
	                   const libmonad::Option<unsigned long> endTime) : Name(std::move(name)), Context(
		                                                                    std::move(context)), To(std::move(to)), StartTime(startTime), EndTime(endTime)
	{
	}

	std::string Relation::GetId() const
	{
		return Name + To->GetId();
	}
}
