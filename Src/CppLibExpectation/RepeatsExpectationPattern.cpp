#include "RepeatsExpectationPattern.h"

#include "ConsecutiveExpectationsPattern.h"
#include "OrderedExpectationsPattern.h"
#include "ExactExpectationsPattern.h"

ExpectationLib::RepeatsExpectationPattern::RepeatsExpectationPattern(const int minimumFrequencyRequirement, Pattern pattern, std::shared_ptr<IExpectation> repeatedExpectation, const std::vector<std::shared_ptr<Observation>>& observations)
: observations(observations), minimumFrequencyRequirement(minimumFrequencyRequirement), repeatedExpectation(std::move(repeatedExpectation)), pattern(pattern)
{
			
}

bool ExpectationLib::RepeatsExpectationPattern::Match()
{
	std::vector<std::shared_ptr<IExpectation>> expectations;

	for(auto i = 0; i < minimumFrequencyRequirement; i++)
	{
		expectations.push_back(repeatedExpectation);
	}

	if(pattern == Pattern::Ordered) return std::make_shared<OrderedExpectationsPattern>(expectations, observations)->Match();
	if(pattern == Pattern::Exact) return std::make_shared<ExactExpectationsPattern>(expectations, observations)->Match();
	return false;
}

int ExpectationLib::RepeatsExpectationPattern::GetLastProcessedObservationIndex()
{
	return lastObservationMatchedIndex;
}
