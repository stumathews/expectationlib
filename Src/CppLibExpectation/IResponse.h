#pragma once
#include <string>
#include <memory>
#include "IHasId.h"

namespace ExpectationLib
{
	class IStimulus;
	class IResponse : public virtual IHasId
	{
		public:
	    virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	    virtual std::string GetContext() = 0;
		virtual std::string ToString() = 0;
	};
}
