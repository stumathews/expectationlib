#pragma once
#include <iostream>

#include "IHasId.h"
#include "IParty.h"

namespace ExpectationLib
{
    // A stimulus represents an action taken by a sender that is directed at a receiver
    class IStimulus : public IHasId
	{
    public:
        virtual std::shared_ptr<IParty> GetSender() = 0;
	    virtual std::shared_ptr<IParty> GetReceiver() = 0;
        virtual std::string GetId() = 0;
        virtual std::string ToString() = 0;
    };
}


