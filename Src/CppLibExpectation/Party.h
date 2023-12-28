#pragma once
#include "IParty.h"
#include <string>

namespace ExpectationLib
{    
	class Party final : public virtual IParty
	{
	public:
		Party(const std::string& id, const std::string& role = "");

	    std::string GetRole() override;
		const std::string GetId() override;
		void AddRelation(std::string name, std::shared_ptr<IParty> to) override;
		std::vector<Relation>& GetRelations() override;
		bool HasRelationTo(const std::shared_ptr<IParty> to, const std::string relationName) override;

	private:
	    
	    std::string id;
	    std::string role;
		std::vector<Relation> relations;
	};
}
