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
	    static std::shared_ptr<ICircumstance> Build(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, libmonad::Option<unsigned long> time = 1)
		{
			const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver, time);
			return stimulus->Cause(libmonad::None());
	    }

		static std::shared_ptr<ICircumstance> Build(const std::shared_ptr<IParty>& sender, const std::shared_ptr<IParty>& receiver, libmonad::Option<const std::string> type, libmonad::Option<unsigned long> time = 1)
	    {
			const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver, time);

			const auto response = type.Map<std::shared_ptr<IResponse>>(
				[&](const std::string& context)
				{
					return std::dynamic_pointer_cast<IResponse>(std::make_shared<ContactResponse>(context, stimulus, time));
				});

			return stimulus->Cause(response);
		}
	};

}
