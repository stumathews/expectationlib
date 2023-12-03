#pragma once
#include "ICircumstance.h"
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
	class Circumstance : public ICircumstance
	{
	public:
	    IStimulus* stimulus;
	    IResponse* response;

	    Circumstance(IStimulus* stimulus, IResponse* response)
		{
	        this->stimulus = stimulus;
	        this->response = response;
	    }

	    IStimulus* getStimulus()
		{
	        return stimulus;
	    }

	    IResponse* getResponse()
		{
	        return response;
	    }
	};

}
