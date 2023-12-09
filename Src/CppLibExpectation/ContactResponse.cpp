#include "pch.h"
#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IParty>& from)
	{
		From = from;
		Context = context;
	}

	std::string ContactResponse::ToString()
	{
		return Context;
	}

	std::string ContactResponse::GetId()
	{
		return GetContext()+ GetFrom()->GetId();
	}

	std::shared_ptr<IParty> ContactResponse::GetFrom()
	{
		return From;
	}

	void ContactResponse::SetFrom(const std::shared_ptr<IParty> from)
	{
		this->From = from;
	}

	std::string ContactResponse::GetContext()
	{
		return Context;
	}

	void ContactResponse::SetContext(const std::string context)
	{
		this->Context = context;
	}
}
