#pragma once
#include "IParty.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	/// <summary>
    /// A contact stimulus is a relationship such that it occurs when a sender makes contact with a receiver
    /// </summary>
    class ContactsStimulus final : public virtual IStimulus, public std::enable_shared_from_this<ContactsStimulus>
	{
    public:
        ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver);
        
        static std::string CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver);

        const std::string GetId() override;
        std::string ToString() override;
        
        std::shared_ptr<IParty> GetSender() override;
        std::shared_ptr<IParty> GetReceiver() override;
        std::shared_ptr<IResponse> GetResponse() override;

    private:
        std::shared_ptr<IParty> sender;
        std::shared_ptr<IParty> receiver;
    };
}
