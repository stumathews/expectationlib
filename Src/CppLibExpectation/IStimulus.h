#pragma once
#include <iostream>

#include "IHasId.h"
#include "IParty.h"

namespace ExpectationLib
{
    // A stimulus is the kind of relationship between a sender and a receiver
    class IStimulus : public IHasId
	{
    public:

        // Sender is the party that initiates the relationship
        virtual std::shared_ptr<IParty> GetSender() = 0;

        // Receiver is the party that subjected to the relationship
	    virtual std::shared_ptr<IParty> GetReceiver() = 0;

        // Unique party identifier
        virtual std::string GetId() = 0;

        // String representation of a party
        virtual std::string ToString() = 0;
    };
}


