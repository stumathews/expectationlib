#include "ConsecutiveExpectationsPattern.h"

ExpectationLib::ConsecutiveExpectationsPattern::ConsecutiveExpectationsPattern(
	const std::vector<std::shared_ptr<IExpectation>>& expectations,
	const std::vector<std::shared_ptr<Observation>>& observations): expectations(expectations), observations(observations)
{
			
}

bool ExpectationLib::ConsecutiveExpectationsPattern::Match()
{
	auto matches = 0;
	for (auto o = startingObservationIndex; o < observations.size(); o++)
	{
		for(auto e = 0; e < expectations.size();e++)
		{			
			if(!expectations[e]->Match(observations[o])) 
			{
				if(matches > 0) o--;
				matches = 0;
				break;
			}
			
			matches++;			
			if(matches == expectations.size()) { return FoundAt(o); }
			if(o+1 < observations.size()) o++; // move to next observation, if we still have observations
		}
	}
	return false;
}
