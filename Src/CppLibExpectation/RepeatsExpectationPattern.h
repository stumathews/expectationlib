#pragma once
#include <vector>

#include "IExpectation.h"
#include "IExpectedPattern.h"
#include "Observation.h"

namespace ExpectationLib
{
	class RepeatsExpectationPattern final :  public IExpectedPattern
	{
	public:

		enum class Pattern
		{
			Exact,
			Ordered
		};

		RepeatsExpectationPattern(int minimumFrequencyRequirement, Pattern pattern, std::shared_ptr<IExpectation> repeatedExpectation, const std::vector<std::shared_ptr<Observation>>& observations);
		bool Match() override;
		int GetLastProcessedObservationIndex() override;

	private:
		
		const std::vector<std::shared_ptr<Observation>>& observations;
		int minimumFrequencyRequirement;
		std::shared_ptr<IExpectation> repeatedExpectation;
		Pattern pattern;
		int lastObservationMatchedIndex = -1;
	};
}

