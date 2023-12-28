#pragma once
#include <memory>
#include <string>
#include "IParty.h"
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ContactResponse final : public IResponse
	{
	public:
	    std::string Context;
	    std::shared_ptr<IParty> From;

	    ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus);

	    std::string ToString() override;
	    const std::string GetId() override;

	    std::shared_ptr<IStimulus> GetStimulus() override;

	    std::string GetContext() override;
	    void SetContext(std::string context) override;
	    inline static std::string ContactRelationName = "contact";
	private:		
	    const std::shared_ptr<IStimulus> stimulus;

	};
}
