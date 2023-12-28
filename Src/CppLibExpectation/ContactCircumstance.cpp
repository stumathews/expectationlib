#include "ContactCircumstance.h"

#include "ContactResponse.h"


namespace ExpectationLib
{
	ContactCircumstance::ContactCircumstance(const std::shared_ptr<IStimulus>& stimulus,
		const std::string& responseContext, const std::shared_ptr<IParty>& overrideFrom)
	{
		this->stimulus = stimulus;            
		this-> responseContext = responseContext;
		from = overrideFrom ? overrideFrom : stimulus->GetReceiver();
	}

	std::shared_ptr<IStimulus> ContactCircumstance::GetStimulus()
	{
		return stimulus;
	}

	std::shared_ptr<IResponse> ContactCircumstance::GetResponse()
	{
		return std::make_shared<ContactResponse>(responseContext, stimulus);
	}

	std::shared_ptr<IParty> ContactCircumstance::GetFrom()
	{
		return from;
	}
}
