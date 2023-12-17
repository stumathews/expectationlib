#pragma once
#include <memory>
#include <string>
#include "IParty.h"
#include "IResponse.h"

namespace ExpectationLib
{
	class ContactResponse final : public IResponse
	{
	public:
	    std::string Context;
	    std::shared_ptr<IParty> From;

	    ContactResponse(const std::string& context, const std::shared_ptr<IParty>& from);

	    std::string ToString() override;
	    const std::string GetId() override;

	    std::shared_ptr<IParty> GetFrom() override;
	    void SetFrom(std::shared_ptr<IParty> from) override;

	    std::string GetContext() override;
	    void SetContext(std::string context) override;
	};
}
