#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"


namespace ExpectationLib
{
	ContactCircumstance::ContactCircumstance(const std::shared_ptr<IResponse>& response)
	{
		this->from = response->GetReceiver();
		this->response = response;
	}

	std::shared_ptr<IStimulus> ContactCircumstance::GetStimulus()
	{
		return response->GetStimulus();
	}

	std::shared_ptr<IResponse> ContactCircumstance::GetResponse()
	{
		return response;
	}

	std::shared_ptr<IParty> ContactCircumstance::GetFrom()
	{
		return from;
	}
}
