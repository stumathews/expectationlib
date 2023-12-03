#pragma once
#include "Circumstance.h"
#include "ContactStimulus.h"
#include "ICircumstance.h"

namespace ExpectationLib
{
	
class ContactCircumstanceBuilder {
public:
    static ICircumstance* Build(IParty* sender, IParty* receiver, std::string responseContext, IParty* overrideFrom = nullptr) {
        return new Circumstance(new ContactsStimulus(sender, receiver), responseContext, overrideFrom);
    }
};
}
