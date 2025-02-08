#pragma once
#include "ICircumstance.h"
#include "IParty.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ContactResponse;

	/// <summary>
    /// A contact stimulus is a relationship such that it occurs when a sender makes contact with a receiver
    /// </summary>
    class ContactsStimulus final : public virtual IStimulus, public std::enable_shared_from_this<ContactsStimulus>
	{
    public:
        ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, libmonad::Option<unsigned long> startTime = 1);
        
        static std::string CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver);

        const std::string GetId() override;
        std::string ToString() override;

        std::shared_ptr<IParty> GetSender() override;
        std::shared_ptr<IParty> GetReceiver() override;
        std::shared_ptr<IResponse> GetResponse() override;
        // Cause a response to produce a resulting circumstance
        std::shared_ptr<ICircumstance> Cause(libmonad::Option<std::shared_ptr<IResponse>> inResponse) override;
        std::shared_ptr<ICircumstance> Cause();
        std::shared_ptr<ICircumstance> GetCircumstance() override;
        std::string GetName() override { return Name; }
        libmonad::Option<unsigned long> GetStartTime() override;
        static std::shared_ptr<ContactsStimulus> Create(std::shared_ptr<IParty> sender, std::shared_ptr<IParty> receiver);
        inline static std::string Name = "ContactStimulus";

    private:
        std::shared_ptr<IParty> sender;
        std::shared_ptr<IParty> receiver;
        std::shared_ptr<IResponse> response;
        std::shared_ptr<ICircumstance> circumstance;
        libmonad::Option<unsigned long> startTime;
	};
}
