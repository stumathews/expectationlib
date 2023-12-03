#pragma once
#include <string>

#include "IResponse.h"
#include "IStimulus.h"
#include "Observation.h"

namespace ExpectationLib
{
	class IObserver {
public:
    virtual Observation* Observe(IStimulus* stimulus, IResponse* response, std::string context = "") = 0;
};
}
