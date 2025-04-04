#pragma once
#include <iostream>
#include "Option.h"

namespace ExpectationLib
{
	class IResponse;
    class IParty;
    class ICircumstance;

	// A stimulus is the kind of relationship between a sender and a receiver
    class IStimulus : public virtual IHasId
	{
    public:

        // Sender is the party that initiates the relationship
        virtual std::shared_ptr<IParty> GetSender() = 0;

        // Receiver is the party that subjected to the relationship
	    virtual std::shared_ptr<IParty> GetReceiver() = 0;

        // Get the response that results when this stimulus occurs
        virtual std::shared_ptr<IResponse> GetResponse() = 0;

        virtual std::shared_ptr<ICircumstance> GetCircumstance() = 0;

        // String representation of a party
        virtual std::string ToString() = 0;

        // Cause a response to produce a resulting circumstance
        virtual std::shared_ptr<ICircumstance> Cause(libmonad::Option<std::shared_ptr<IResponse>> response) = 0;

        virtual std::string GetName() = 0;
        virtual libmonad::Option<unsigned long> GetStartTime() = 0;
        
    };
}


