#pragma once
#include <string>
#include "IHasId.h"

namespace ExpectationLib
{
    class IParty : public virtual IHasId
	{
    public:

        // A description for the role the party plays - useful for identifying the kind or type of party that is involved
        virtual std::string GetRole() = 0;
    };
}



