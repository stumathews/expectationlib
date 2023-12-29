#include "ContactCircumstance.h"
#include "ContactResponse.h"


namespace ExpectationLib
{
	ContactCircumstance::ContactCircumstance(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IParty>& overrideFrom)
	{
		this->stimulus = stimulus ;
		this->responseContext = stimulus->GetResponse()->GetContext();
		from = overrideFrom ? overrideFrom : stimulus->GetReceiver();

		// (Modify) Cause relations to occur between the affected parties in response to the stimulus
		stimulus->GetSender()->AddRelation(ContactRelationName, stimulus->GetReceiver());
		stimulus->GetReceiver()->AddRelation(ContactRelationName, stimulus->GetSender());
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
