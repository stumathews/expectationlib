#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus): stimulus(stimulus)
	{
		From = stimulus->GetReceiver();
		Context = context;

		// Modify the sender and receiver in response to stimulus
		stimulus->GetSender()->AddRelation(ContactRelationName, stimulus->GetReceiver());
		stimulus->GetReceiver()->AddRelation(ContactRelationName, stimulus->GetSender());
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
