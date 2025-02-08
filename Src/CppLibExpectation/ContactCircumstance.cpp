#include "ContactCircumstance.h"
#include <sstream>
#include "ContactResponse.h"
#include "ContactStimulus.h"


namespace ExpectationLib
{
	ContactCircumstance::ContactCircumstance(const std::shared_ptr<IResponse>& response)
	{
		this->response = response;
		this->stimulus = response->GetStimulus();

		std::stringstream circumstanceId;

		this->GetResponse()->GetResult().Match(
			[](libmonad::None none)
			{
				throw std::exception("ContactCircumstance: No response result");
			},
			[&](const std::shared_ptr<IResult>& result)
			{
				
				this->from = result->GetReceiver();
				circumstanceId << result->GetSender()->GetId()
					   << "-[" << GetResponse()->GetContext() << "]->"
					   << result->GetReceiver()->GetId();
			});

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
