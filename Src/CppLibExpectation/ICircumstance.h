#pragma once
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ICircumstance : virtual public IHasId
	{
	public:
		virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	    virtual std::shared_ptr<IResponse> GetResponse() = 0;
	};
}
