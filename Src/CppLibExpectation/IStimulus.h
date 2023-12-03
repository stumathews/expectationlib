#pragma once
#include <iostream>

#include "IHasId.h"
#include "IParty.h"

namespace ExpectationLib {
    // A stimulus represents an action taken by a sender that is directed at a receiver
    class IStimulus : public IHasId {
    public:
        // The initiator of the stimulus
        virtual IParty* getSender() = 0;
        // The recipient of the stimulus
	    virtual IParty* getReceiver() = 0;
        std::string getId() override;
    };
}


