#pragma once
#include <memory>
#include <string>
#include "IParty.h"
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ContactResponse final : public IResponse, public std::enable_shared_from_this<ContactResponse>
	{
	public:
	    std::string Context;
	    std::shared_ptr<IParty> From;

	    ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus);

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
