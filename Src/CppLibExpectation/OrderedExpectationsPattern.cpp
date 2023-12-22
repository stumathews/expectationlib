#include "OrderedExpectationsPattern.h"

#include <map>
#include "Node.h"
#include "Ordering.h"
#include "Tree.h"

namespace ExpectationLib
{	
	OrderedExpectationsPattern::OrderedExpectationsPattern(
		const std::vector<std::shared_ptr<IExpectation>>& expectations,
		const std::vector<std::shared_ptr<Observation>>& observations)
	{
		Expectations = expectations;
		Observations = observations;
	}

	std::vector<std::shared_ptr<IExpectation>> OrderedExpectationsPattern::UnmatchedExpectations()
	{
		std::vector<std::shared_ptr<IExpectation>> unmatched;
		for (const auto& expectation : Expectations) 
		{
			if (std::ranges::find(MatchedExpectations, expectation) == MatchedExpectations.end()) 
			{
				unmatched.push_back(expectation);
			}
		}
		return unmatched;
	}


	std::vector<std::string>
	OrderedExpectationsPattern::DetectOrder() const
	{
		Ordering ordering(Observations);
		return ordering.DetectOrder();
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
