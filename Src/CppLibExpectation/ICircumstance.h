#pragma once
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class ICircumstance
	{
	public:
	    virtual IStimulus* getStimulus() = 0;
	    virtual IResponse* getResponse() = 0;
	};
}
