#pragma once
#include <memory>

#include "ContactCircumstance.h"
#include "ContactStimulus.h"
#include "ICircumstance.h"

namespace ExpectationLib
{	
	class ContactCircumstanceBuilder
	{
	public:
	    static std::shared_ptr<ICircumstance> Build(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, const std::shared_ptr<IParty>&
		                                                overrideFrom = nullptr)
		{
			const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver);
			stimulus->Trigger();
	        return std::make_shared<ContactCircumstance>(stimulus->GetResponse());
	    }
	};

}
