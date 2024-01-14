#include "ContactStimulus.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactsStimulus::ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{		
		this->sender = sender;
		this->receiver = receiver;
		// NB: Can't used shared_from_this() here as this object is not created yet.
	}

	std::string ContactsStimulus::ToString()
	{
		return "Contact Stimulus: " + sender->GetRole() + " -> " + receiver->GetRole();
	}

	std::shared_ptr<IParty> ContactsStimulus::GetSender()
	{
		return sender;
	}

	std::shared_ptr<IParty> ContactsStimulus::GetReceiver()
	{
		return receiver;
	}

	std::shared_ptr<IResponse> ContactsStimulus::GetResponse()
	{
		return response;
	}

	std::shared_ptr<ICircumstance> ContactsStimulus::Trigger(std::shared_ptr<IResponse> inResponse)
	{
		// Trigger a response
		this->response = inResponse ? inResponse : std::make_shared<ContactResponse>("NoResponseContext", shared_from_this());

		// Establishes the contact relation between sender and receiver
		this->circumstance = this->response->Trigger();

		return circumstance;
	}

	std::shared_ptr<ICircumstance> ContactsStimulus::GetCircumstance()
	{
		return circumstance;
	}
	
	std::string ContactsStimulus::CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{
		return Name + "|" +sender->GetId() + " -> " + receiver->GetId();
	}

	const std::string ContactsStimulus::GetId() const
	{
		return CreateId(sender, receiver);
	}
}
