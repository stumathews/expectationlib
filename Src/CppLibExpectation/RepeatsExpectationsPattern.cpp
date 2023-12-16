#include "RepeatsExpectationsPattern.h"

namespace ExpectationLib
{
	RepeatsExpectationsPattern::RepeatsExpectationsPattern(std::shared_ptr<IExpectedPattern> pattern, const int minimumFrequencyRequirement)
	: patternMatcher(std::move(pattern)), countRepeats(0), expectedRepeats(minimumFrequencyRequirement)
{
	}

	bool RepeatsExpectationsPattern::Match()
	{
		countRepeats = 0;
		patternMatcher->SetStartingObservationIndex(startingObservationIndex);
		while(patternMatcher->Match())
		{
			lastMatchedObservationIndex = patternMatcher->GetLastProcessedObservationIndex();
			patternMatcher->SetStartingObservationIndex(lastMatchedObservationIndex + 1);				
			countRepeats++;
		}
		return countRepeats  == expectedRepeats;
	}
	
}
