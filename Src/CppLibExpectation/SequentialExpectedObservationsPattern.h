#pragma once
#include <vector>

#include "IExpectation.h"

namespace ExpectationLib
{
	class SequentialExpectedObservationsPattern {
	public:
	    std::vector<IExpectation*> Expectations;
	    std::vector<ContactCircumstance*> Observations;
	    SequentialExpectedObservationsPattern(std::vector<IExpectation*> expectations, std::vector<ContactCircumstance*> observations) {
	        Expectations = expectations;
	        Observations = observations;
	    }
	    bool Match() {
	        if (Expectations.size() != Observations.size()) {
	            return false;
	        }
	        for (int i = 0; i < Expectations.size(); i++) {
	            if (!Expectations[i]->Match(Observations[i])) {
	                return false;
	            }
	        }
	        return true;
	    }
	};
}
