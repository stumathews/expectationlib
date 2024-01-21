#pragma once
#include <memory>

#include "ContactResponse.h"
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
			return stimulus->Trigger(libmonad::None());
	    }

		static std::shared_ptr<ICircumstance> Build(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, libmonad::Option<const std::string> type)
	    {
			const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver);

			const auto response = type.Map<std::shared_ptr<IResponse>>(
				[&](const std::string& context)
				{
					return std::dynamic_pointer_cast<IResponse>(std::make_shared<ContactResponse>(context, stimulus));
				});

			return stimulus->Trigger(response);
		}
	};

}
