#pragma once
#include <string>
#include "IHasId.h"

namespace ExpectationLib
{
    class IParty : public virtual IHasId
	{
    public:
        virtual std::string GetRole() = 0;
    };
}



