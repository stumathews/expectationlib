#include "ContactStimulus.h"

namespace ExpectationLib
{
	ContactsStimulus::ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{
		this->sender = sender;
		this->receiver = receiver;
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

	std::string ContactsStimulus::CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{
		return sender->GetId() + " -> " + receiver->GetId();
	}

	std::string ContactsStimulus::GetId()
	{
		return CreateId(sender, receiver);
	}
}
