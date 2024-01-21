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

	libmonad::Option<std::shared_ptr<IParty>> Party::FindRelatedParty(const std::string& partyId, const std::string& relationName)
	{
		const auto found = std::ranges::find_if (relations, [&](const Relation& relation)
		{
			return relation.To->GetId() == partyId && relation.Name == relationName;
		});

		if(found == relations.end()) return libmonad::None();

		return found->To;
	}

	void Party::AddRelation(std::string& name, std::shared_ptr<IParty>& to, std::string& context)
	{
		relations.emplace_back(name, to, context);
	}

	std::vector<Relation>& Party::GetRelations()
	{
		return relations;
	}

	bool Party::HasRelationTo(const std::shared_ptr<IParty>& to, const std::string& relationName)
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

	bool operator==(Party& lhs, Party& rhs)
	{
		return lhs.GetId() == rhs.GetId();
	}
}
