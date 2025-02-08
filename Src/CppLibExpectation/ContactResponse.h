#pragma once
#include <memory>
#include <string>

#include "ContactStimulus.h"
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
	    std::shared_ptr<ICircumstance> Start() override;
	    std::shared_ptr<IStimulus> GetStimulus() override;
	    static std::shared_ptr<ContactResponse> Create(const std::string& context, const std::shared_ptr<ContactsStimulus> stimulus);
	    [[nodiscard]] libmonad::Option<std::shared_ptr<IResult>> GetResult() override;

	    inline static std::string ContactRelationName = "contacted";

    private:		
	    const std::shared_ptr<IStimulus> stimulus;
		libmonad::Option<std::shared_ptr<IResult>> result;

	};
}
