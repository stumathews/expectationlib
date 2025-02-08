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
		[[nodiscard]] virtual std::shared_ptr<IParty> GetSender() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IParty> GetReceiver() const = 0;
		[[nodiscard]] virtual std::string GetContext() const = 0;
		virtual std::string ToString() = 0;
		virtual std::shared_ptr<ICircumstance> Start() = 0;
	    virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	};
}
