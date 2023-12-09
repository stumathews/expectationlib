#pragma once
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ICircumstance
	{
	public:
		virtual ~ICircumstance() = default;
		virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	    virtual std::shared_ptr<IResponse>  GetResponse() = 0;
	};
}
