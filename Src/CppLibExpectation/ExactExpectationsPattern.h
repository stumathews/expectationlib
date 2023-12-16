#pragma once
#include <vector>
#include "IExpectation.h"

namespace ExpectationLib
{
	class ExactExpectationsPattern : public BaseExpectedPattern
	{
	public:
	    std::vector<std::shared_ptr<IExpectation>> Expectations;
	    std::vector<std::shared_ptr<Observation>> Observations;

	    ExactExpectationsPattern(const std::vector<std::shared_ptr<IExpectation>>& expectations, const std::vector<std::shared_ptr<Observation>>& observations)
		{
	        Expectations = expectations;
	        Observations = observations;
	    }

	    bool Match() override
		{
	        if (Expectations.size() != Observations.size()) 
			{
	            return false;
	        }

	        for (int i = 0; i < Expectations.size(); i++)
			{
	            if (!Expectations[i]->Match(Observations[i]))
				{
	                return false;
	            }
	        }

			lastMatchedObservationIndex = Observations.size()-1;
	        return true;
	    }
	};
}
