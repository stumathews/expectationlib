#include "Party.h"

namespace ExpectationLib
{
	Party::Party(const std::string& id, const std::string& role)
	{
		this->id = id;
		this->role = role;
	}

	const std::string Party::GetId() const
	{
		return id;
	}

	std::shared_ptr<IParty> Party::FindRelatedParty(const std::string& partyId, const std::string& relationName)
	{
		const auto found = std::ranges::find_if (relations, [&](const Relation& relation)
		{
			return relation.To->GetId() == partyId && relation.Name == relationName;
		});

		if(found == relations.end()) return nullptr;

		return found->To;
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

	bool operator==(const Party& lhs, const Party& rhs)
	{
		return lhs.GetId() == rhs.GetId();
	}
}
