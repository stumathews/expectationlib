#include "ConsecutiveExpectations.h"

ExpectationLib::ConsecutiveExpectations::ConsecutiveExpectations(
	const std::vector<std::shared_ptr<IExpectation>>& expectations,
	const std::vector<std::shared_ptr<Observation>>& observations): expectations(expectations), observations(observations)
{
			
}

bool ExpectationLib::ConsecutiveExpectations::Match()
{
	auto matches = 0;
	for (auto o = 0; o < observations.size(); o++)
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
			if(matches == expectations.size()) return true;
			if(o+1 < observations.size()) o++; // move to next observation, if we still have observations
		}
	}
	return false;
}
