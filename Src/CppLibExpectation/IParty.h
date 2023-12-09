#pragma once
#include <string>
#include "IHasId.h"

namespace ExpectationLib
{
    class IParty : public IHasId
	{
    public:
        virtual std::string GetRole() = 0;
        std::string GetId() override = 0;
    };
}



