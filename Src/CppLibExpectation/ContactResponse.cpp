#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus): stimulus(stimulus)
	{
		From = stimulus->GetReceiver();
		Context = context;

		// Now what we could do here is manipulate the relations in both sender and receiver such that
		// this contact response results in changes/modifications to their state. 
	}

	std::string ContactResponse::ToString()
	{
		return Context;
	}

	const std::string ContactResponse::GetId()
	{
		return GetContext()+ GetStimulus()->GetId();
	}

	std::shared_ptr<IStimulus> ContactResponse::GetStimulus()
	{
		return stimulus;
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
