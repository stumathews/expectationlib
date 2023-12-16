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
		for (auto o = 0; o < Observations.size(); o++) 
		{
			if (e > Expectations.size() - 1) continue;
			if (!Expectations[e]->Match(Observations[o])) continue; // can have other unmatched observations in between
			MatchedExpectations.push_back(Expectations[e]);
			if(countMatches == Expectations.size())
			{
				lastMatchedObservationIndex = o;
				return true;
			}
			e++;
			countMatches++;
		}
		return countMatches == Expectations.size();
	}

	int OrderedExpectationsPattern::GetLastProcessedObservationIndex()
	{
		return lastMatchedObservationIndex;
	}
}
