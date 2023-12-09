#include "OrderedExpectedObservationsPattern.h"

namespace ExpectationLib
{
	OrderedExpectedObservationsPattern::OrderedExpectedObservationsPattern(
		const std::vector<std::shared_ptr<IExpectation>>& expectations,
		const std::vector<std::shared_ptr<Observation>> observations)
	{
		Expectations = expectations;
		Observations = observations;
	}

	std::vector<std::shared_ptr<IExpectation>> OrderedExpectedObservationsPattern::UnmatchedExpectations()
	{
		std::vector<std::shared_ptr<IExpectation>> unmatched;
		for (auto expectation : Expectations) 
		{
			if (std::find(MatchedExpectations.begin(), MatchedExpectations.end(), expectation) == MatchedExpectations.end()) 
			{
				unmatched.push_back(expectation);
			}
		}
		return unmatched;
	}

	bool OrderedExpectedObservationsPattern::Match()
	{
		int countMatches = 0;
		int i = 0;
		for (auto observation : Observations) 
		{
			if (i > Expectations.size() - 1) continue;
			if (!Expectations[i]->Match(observation)) continue; // can have other unmatched observations in between
			MatchedExpectations.push_back(Expectations[i]);
			i++;
			countMatches++;
		}
		return countMatches == Expectations.size();
	}
}
