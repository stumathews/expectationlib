#include "Party.h"

namespace ExpectationLib
{
	Party::Party(const std::string& id, const std::string& role)
	{
		this->id = id;
		this->role = role;
	}

	const std::string Party::GetId()
	{
		return id;
	}

	void Party::AddRelation(std::string name, std::shared_ptr<IParty> to)
	{
		relations.emplace_back(name, to);
	}

	std::vector<Relation>& Party::GetRelations()
	{
		return relations;
	}

	bool Party::HasRelationTo(const std::shared_ptr<IParty> to, const std::string relationName)
	{
		const auto found = std::ranges::find_if (relations, [&](const Relation& relation)
		{
			return relation.Name == relationName && relation.To->GetId() == to->GetId();
		});
		return found != relations.end();
	}

	std::string Party::GetRole()
	{
		return role;
	}
	
}
