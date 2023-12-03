#pragma once
#include "IParty.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	/// <summary>
    /// A contact stimulus is a generic action that occurs when a sender makes contact with a receiver
    /// </summary>
    class ContactsStimulus : public IStimulus {
    private:
        IParty* Sender;
        IParty* Receiver;
    public:
        ContactsStimulus(IParty* sender, IParty* receiver) {
            Sender = sender;
            Receiver = receiver;
        }
        std::string ToString() {
            return "Contact Stimulus: " + Sender->Role + " -> " + Receiver->Role;
        }
        static std::string CreateId(IParty* sender, IParty* receiver) {
            return sender->getId() + " -> " + receiver->getId();
        }
        std::string Id() {
            return CreateId(Sender, Receiver);
        }
    };
}
