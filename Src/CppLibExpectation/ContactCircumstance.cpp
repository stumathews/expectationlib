#include "ContactCircumstance.h"
#include <sstream>
#include "ContactResponse.h"
#include "ContactStimulus.h"


namespace ExpectationLib
{
	ContactCircumstance::ContactCircumstance(const std::shared_ptr<IResponse>& response)
	{
		this->from = response->GetReceiver();
		this->response = response;
		this->stimulus = response->GetStimulus();

		std::stringstream circumstanceId;
		circumstanceId << GetResponse()->GetSender()->GetId()
					   << "-[" << GetResponse()->GetContext() << "]->"
					   << GetResponse()->GetReceiver()->GetId();
		this->id = circumstanceId.str();
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

	const std::string ContactCircumstance::GetId()
	{		
		return id;
	}
}
