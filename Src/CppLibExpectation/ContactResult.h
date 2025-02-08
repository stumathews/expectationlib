#pragma once
#include <memory>

#include "IResult.h"

namespace ExpectationLib
{
	class ContactResult : public IResult
	{
	public:
		ContactResult(std::shared_ptr<IParty> sender, std::shared_ptr<IParty> receiver): sender(std::move(sender)),
			receiver(std::move(receiver))
		{
			
		}

		std::shared_ptr<IParty> GetSender() const override
		{
			return sender;
		}

		std::shared_ptr<IParty> GetReceiver() const override
		{
			return receiver;
		}


		std::shared_ptr<IParty> sender;
		std::shared_ptr<IParty> receiver;
	};
}
