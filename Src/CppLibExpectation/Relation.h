#pragma once
#include <memory>
#include <string>

namespace ExpectationLib
{
	class IParty;

	class Relation
	{
	public:
		Relation(std::string name, std::shared_ptr<IParty> to, std::string& context);
		std::string Name;
		std::string Context;
		std::shared_ptr<IParty> To;
		[[nodiscard]] std::string GetId() const;
	};
}
