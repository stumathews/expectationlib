#include "ContactStimulus.h"

#include "ContactResponse.h"

namespace ExpectationLib
{
	ContactsStimulus::ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{		
		this->sender = sender;
		this->receiver = receiver;
		// NB: Can't used shared_from_this() here as the pointer, this, is not created yet.
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
		std::shared_ptr<IResponse> expectedResponse = std::make_shared<ContactResponse>("aResponse", shared_from_this());
		return expectedResponse;
	}

	std::string ContactsStimulus::CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{
		return sender->GetId() + " -> " + receiver->GetId();
	}

	const std::string ContactsStimulus::GetId()
	{
		return CreateId(sender, receiver);
	}
}
