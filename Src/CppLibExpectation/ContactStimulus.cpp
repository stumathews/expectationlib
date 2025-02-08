#include "ContactStimulus.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"

using namespace std;

namespace ExpectationLib
{
	ContactsStimulus::ContactsStimulus(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, const libmonad::Option<unsigned long> startTime): startTime(startTime) {		
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
	
	std::shared_ptr<ICircumstance> ContactsStimulus::Cause(libmonad::Option<std::shared_ptr<IResponse>> inResponse)
	{
		// Get or create a response
		this->response = inResponse.WhenNone([this](){
			return std::dynamic_pointer_cast<IResponse>(std::make_shared<ContactResponse>("NoResponseContext", shared_from_this()));
		});

		// Trigger response: establishes the contact relation between sender and receiver
		this->circumstance = this->response->Start();

		return circumstance;
	}

	std::shared_ptr<ICircumstance> ContactsStimulus::Cause()
	{		
		this->response = std::dynamic_pointer_cast<IResponse>(std::make_shared<ContactResponse>("NoResponseContext", shared_from_this()));		
		this->circumstance = this->response->Start();

		return circumstance;
	}

	std::shared_ptr<ICircumstance> ContactsStimulus::GetCircumstance()
	{
		return circumstance;
	}

	libmonad::Option<unsigned long> ContactsStimulus::GetStartTime()
	{
		return startTime;
	}

	std::shared_ptr<ContactsStimulus> ContactsStimulus::Create(std::shared_ptr<IParty> sender, std::shared_ptr<IParty> receiver)
	{
		return std::make_shared<ContactsStimulus>(sender, receiver);
	}

	std::string ContactsStimulus::CreateId(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
	{
		return Name + "|" +sender->GetId() + " -> " + receiver->GetId();
	}

	const std::string ContactsStimulus::GetId()
	{
		return CreateId(sender, receiver);
	}
}
