#pragma once
#include "IParty.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	/// <summary>
    /// A contact stimulus is a generic action that occurs when a sender makes contact with a receiver
    /// </summary>
    class ContactsStimulus : public IStimulus
	{
    public:
        ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver);
        
        static std::string CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver);
        std::string GetId() override;
        std::string ToString() override;

        std::shared_ptr<IParty> GetSender() override;
        std::shared_ptr<IParty> GetReceiver() override;

    private:
        std::shared_ptr<IParty> sender;
        std::shared_ptr<IParty> receiver;
    };
}
