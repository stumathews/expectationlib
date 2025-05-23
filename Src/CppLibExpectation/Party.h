#pragma once
#include "IParty.h"
#include <string>

namespace ExpectationLib
{    
	class Party final : public virtual IParty
	{
	public:
		explicit Party(const std::string& id, const std::string& role = "");

	    std::string GetRole() override;
		void AddRelation(std::string& name, std::shared_ptr<IParty>& to, std::string& context, libmonad::Option<unsigned long> startTime, libmonad::Option<unsigned long> endTime) override;
		std::vector<Relation>& GetRelations() override;
		bool HasRelationTo(const std::shared_ptr<IParty>& to, const std::string& relationName) override;
		[[nodiscard]] const std::string GetId() override;
		friend bool operator== (const Party& lhs, const Party& rhs);
		libmonad::Option<std::shared_ptr<IParty>> FindRelatedParty(const std::string& partyId, const std::string& relationName) override;
		int GetHashCode() override;
		static std::shared_ptr<Party> Create(const std::string& name);

	private:
	    
	    std::string id;
	    std::string role;
		std::vector<Relation> relations;
	};
}
