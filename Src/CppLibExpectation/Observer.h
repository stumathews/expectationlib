#pragma once
#include <vector>

#include "ContactCircumstance.h"
#include "IObserver.h"

namespace ExpectationLib
{
	class Observer : IObserver {
public:
    std::vector<ContactCircumstance*> Observations;
    void Observe(ContactCircumstance* circumstance)
	{
        Observations.push_back(circumstance);
    }

    Observation* Observe(IStimulus* stimulus, IResponse* response, std::string context) override;
	};
}
