#include "RepeatedExpectation.h"

#include "OrderedExpectations.h"
#include "ExactExpectations.h"

ExpectationLib::RepeatedExpectation::RepeatedExpectation(int minimumFrequencyRequirement, Pattern pattern, std::shared_ptr<IExpectation> repeatedExpectation, const std::vector<std::shared_ptr<Observation>>& observations)
: observations(observations), minimumFrequencyRequirement(minimumFrequencyRequirement), repeatedExpectation(std::move(repeatedExpectation)), pattern(pattern)
{
			
}

bool ExpectationLib::RepeatedExpectation::Match()
{
	std::vector<std::shared_ptr<IExpectation>> expectations;

	for(auto i = 0; i < minimumFrequencyRequirement; i++)
	{
		expectations.push_back(repeatedExpectation);
	}
	
	if(pattern == Pattern::Ordered) return std::make_shared<OrderedExpectations>(expectations, observations)->Match();
	if(pattern == Pattern::Exact) return std::make_shared<ExactExpectations>(expectations, observations)->Match();
	return false;
}
