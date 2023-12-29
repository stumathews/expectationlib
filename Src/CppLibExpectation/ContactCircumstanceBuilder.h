#pragma once
#include <memory>

#include "ContactStimulus.h"
#include "ICircumstance.h"

namespace ExpectationLib
{	
	class ContactCircumstanceBuilder
	{
	public:
	    static std::shared_ptr<ICircumstance> Build(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver)
		{
			const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver);
			return stimulus->Trigger();
	    }
	};

}
