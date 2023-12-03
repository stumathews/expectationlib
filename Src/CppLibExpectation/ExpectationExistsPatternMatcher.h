#pragma once
#include <vector>

#include "IExpectatedObservationsPattern.h"
#include "Observation.h"
#include "StimuliProducesResponseExpectation.h"

namespace ExpectationLib
{
	
class ExpectationExistsPatternMatcher : public IExpectatedObservationsPattern {
public:
    StimuliProducesResponseExpectation* stimuliProducesResponseExpectation;
    std::vector<Observation> observations;

    ExpectationExistsPatternMatcher(StimuliProducesResponseExpectation* stimuliProducesResponseExpectation, std::vector<Observation> observations) {
        this->stimuliProducesResponseExpectation = stimuliProducesResponseExpectation;
        this->observations = observations;
    }

    bool Match() {
        for (const auto& o : observations) {
            if (o.stimulus->getSender()->getId() == stimuliProducesResponseExpectation->stimuli->getSender()->getId() &&
                o.stimulus->getReceiver()->getId() == stimuliProducesResponseExpectation->stimuli->getReceiver()->getId() &&
                o.response->getId() == stimuliProducesResponseExpectation->response->getId()) {
                return true;
            }
        }
        return false;
    }
};
}
