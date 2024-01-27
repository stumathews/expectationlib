#pragma once
#include <memory>
#include <string>
#include "IHasId.h"
#include "Relation.h"
#include <vector>
#include "Option.h"

namespace ExpectationLib
{
    class IParty : public virtual IHasId
	{
    public:

        // A description for the role the party plays - useful for identifying the kind or type of party that is involved
        virtual std::string GetRole() = 0;
        virtual void AddRelation(std::string& name, std::shared_ptr<IParty>& to, std::string& context, libmonad::Option<unsigned long> startTime, libmonad::Option<unsigned long> endTime ) = 0;
        virtual std::vector<Relation>& GetRelations() = 0;
        virtual bool HasRelationTo(const std::shared_ptr<IParty>& to, const std::string& relationName) = 0;
        virtual libmonad::Option<std::shared_ptr<IParty>> FindRelatedParty(const std::string& partyId, const std::string& relationName) = 0;
        virtual int GetHashCode() = 0;
	};
}



