#include "ContactResponse.h"

#include <sstream>

#include "ContactCircumstance.h"
#include "ContactStimulus.h"
#include "Party.h"

namespace ExpectationLib
{
	ContactResponse::ContactResponse(const std::string& context, const std::shared_ptr<IStimulus>& stimulus, const libmonad::Option<unsigned long> time)
	: Time(time), stimulus(stimulus)
{
		From = stimulus->GetReceiver();
		Context = context;
	}

	const std::string ContactResponse::GetId()
	{
		return GetReceiver()->GetId() + GetContext() + GetSender()->GetId();
	}	

	std::shared_ptr<ICircumstance> ContactResponse::Start() 
	{
		// copy sender
		sender = std::make_shared<Party>(*std::dynamic_pointer_cast<Party>(stimulus->GetSender()));

		// copy receiver
		receiver = std::make_shared<Party>(*std::dynamic_pointer_cast<Party>(stimulus->GetReceiver()));
		
		// Cause relations to occur between the affected parties in response to the stimulus (copy of stimulus' parties are modified)
		auto context = GetContext();

		// If a response time is not provided, use the stimulus start to (this indicates the response occurred immediately as the stimulus was triggerd)
		const auto endTime = Time.IsNone() ? stimulus->GetStartTime() : Time;

		sender->AddRelation(ContactRelationName, receiver, context, stimulus->GetStartTime(), endTime);
		receiver->AddRelation(ContactRelationName, sender, context, stimulus->GetStartTime(), endTime);

		return std::make_shared<ContactCircumstance>(shared_from_this());
	}
		
	std::string ContactResponse::ToString() { return Context;}	
	std::string ContactResponse::GetContext() const { return Context; }
	std::shared_ptr<IParty> ContactResponse::GetSender() const { return sender; }
	std::shared_ptr<IParty> ContactResponse::GetReceiver() const { return receiver; }
	std::shared_ptr<IStimulus> ContactResponse::GetStimulus() { return stimulus; }

	std::shared_ptr<ContactResponse> ContactResponse::Create(const std::string& context,
		const std::shared_ptr<ContactsStimulus> stimulus) 
	{
		return std::make_shared<ContactResponse>(context, stimulus);
	}
}
