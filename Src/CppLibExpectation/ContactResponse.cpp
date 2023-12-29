#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus): stimulus(stimulus)
	{
		From = stimulus->GetReceiver();
		Context = context;

		// modify the state of the sender or receiver.
			
		// this could also be a point in which a user provided delegate is called
	}

	std::string ContactResponse::ToString()
	{
		return Context;
	}

	const std::string ContactResponse::GetId()
	{
		return GetContext() + GetStimulus()->GetId();
	}

	std::shared_ptr<IStimulus> ContactResponse::GetStimulus()
	{
		return stimulus;
	}
	
	std::string ContactResponse::GetContext()
	{
		return Context;
	}
}
