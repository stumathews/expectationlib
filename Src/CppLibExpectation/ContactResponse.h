#pragma once
#include <memory>
#include <string>
#include "IParty.h"
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	// A response that adds contact relations between sender and receiver upon triggering
	class ContactResponse final : public IResponse, public std::enable_shared_from_this<ContactResponse>
	{
	public:
	    std::string Context;
	    std::shared_ptr<IParty> From;
	    libmonad::Option<unsigned long> Time;

	    ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus, libmonad::Option<unsigned long> time  = 1);

	    std::string ToString() override;
	    const std::string GetId() override;

	    std::string GetContext() const override;
	    std::shared_ptr<ICircumstance> Trigger() override;
	    std::shared_ptr<IParty> GetSender() const override;
	    std::shared_ptr<IParty> GetReceiver() const override;
	    std::shared_ptr<IStimulus> GetStimulus() override;

	    inline static std::string ContactRelationName = "contacted";

    private:		
	    const std::shared_ptr<IStimulus> stimulus;
		std::shared_ptr<IParty> sender;
		std::shared_ptr<IParty> receiver;

	};
}
