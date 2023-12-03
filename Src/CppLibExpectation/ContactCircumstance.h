#pragma once
#include "ICircumstance.h"

namespace ExpectationLib
{
    // A particular response to a contact stimulus
    class ContactCircumstance : public ICircumstance {
    public:
        // Constructor
        ContactCircumstance(IStimulus* stimulus, std::string responseContext, IParty* overrideFrom = nullptr) {
            Stimulus = stimulus;
            From = overrideFrom ? overrideFrom : Stimulus->Receiver;
            _responseContext = responseContext;
        }

        // Getter for Stimulus
        IStimulus* getStimulus() {
            return Stimulus;
        }

        // Getter for Response
        IResponse* getResponse() {
            return new ContactResponse(_responseContext, From);
        }

    private:
        IStimulus* Stimulus;
        IParty* From;
        std::string _responseContext;
    };
}
}

