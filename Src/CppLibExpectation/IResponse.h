#pragma once
#include <string>
#include <memory>
#include "IHasId.h"

namespace ExpectationLib
{
	class IParty;
	class ICircumstance;
	class IStimulus;
	class IResponse : public virtual IHasId
	{
		public:
	    virtual std::shared_ptr<IParty> GetSender() = 0;
	    virtual std::shared_ptr<IParty> GetReceiver() = 0;
	    virtual std::string GetContext() = 0;
		virtual std::string ToString() = 0;
		virtual std::shared_ptr<ICircumstance> Trigger() = 0;
	    virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	};
}
