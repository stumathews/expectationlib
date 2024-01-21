#include "ContactResponse.h"

#include "ContactCircumstance.h"
#include "ContactStimulus.h"
#include "Party.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus)
	: stimulus(stimulus)
	{
		From = stimulus->GetReceiver();
		Context = context;
	}

	std::string ContactResponse::ToString()
	{
		return Context;
	}

	const std::string ContactResponse::GetId()
	{
		return GetReceiver()->GetId() + GetContext() + GetSender()->GetId();
	}

		
	std::string ContactResponse::GetContext() const
	{
		return Context;
	}

	std::shared_ptr<ICircumstance> ContactResponse::Trigger() 
	{
		// copy sender
		sender = std::make_shared<Party>(*std::dynamic_pointer_cast<Party>(stimulus->GetSender()));

		// copy receiver
		receiver = std::make_shared<Party>(*std::dynamic_pointer_cast<Party>(stimulus->GetReceiver()));
		
		//Cause relations to occur between the affected parties in response to the stimulus
		auto context = GetContext();
		sender->AddRelation(ContactRelationName, receiver, context);
		receiver->AddRelation(ContactRelationName, sender, context);

		return std::make_shared<ContactCircumstance>(shared_from_this());
	}

	std::shared_ptr<IParty> ContactResponse::GetSender() const
	{
		return sender;
	}

	std::shared_ptr<IParty> ContactResponse::GetReceiver() const
	{
		return receiver;
	}

	std::shared_ptr<IStimulus> ContactResponse::GetStimulus()
	{
		return stimulus;
	}
}
