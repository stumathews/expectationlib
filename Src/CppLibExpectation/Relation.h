#pragma once
#include <memory>
#include <string>

namespace ExpectationLib
{
	class IParty;

	class Relation
	{
	public:
		Relation(std::string name, std::shared_ptr<IParty> to);
		std::string Name;
		std::shared_ptr<IParty> To;
	};
}
