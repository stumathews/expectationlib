#include "OrderedExpectationsPattern.h"

namespace ExpectationLib
{
	OrderedExpectationsPattern::OrderedExpectationsPattern(
		const std::vector<std::shared_ptr<IExpectation>>& expectations,
		const std::vector<std::shared_ptr<Observation>> observations)
	{
		Expectations = expectations;
		Observations = observations;
	}

	std::vector<std::shared_ptr<IExpectation>> OrderedExpectationsPattern::UnmatchedExpectations()
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

	bool OrderedExpectationsPattern::Match()
	{
		int countMatches = 0;
		int e = 0;
		for (auto o = startingObservationIndex; o < Observations.size(); o++) 
		{
			if (e > Expectations.size() - 1) continue;
			if (!Expectations[e]->Match(Observations[o])) continue; // can have other unmatched observations in between
			MatchedExpectations.push_back(Expectations[e]);			
			e++;
			countMatches++;
			if(countMatches == Expectations.size())
			{
				return FoundAt(o);
			}
		}
		return countMatches == Expectations.size();
	}
}
