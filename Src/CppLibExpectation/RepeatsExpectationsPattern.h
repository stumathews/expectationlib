#pragma once
#include "IExpectedPattern.h"
#include "Observation.h"

namespace ExpectationLib
{
	class RepeatsExpectationsPattern final : public BaseExpectedPattern
	{
	public:
		explicit RepeatsExpectationsPattern(std::shared_ptr<IExpectedPattern> pattern, int minimumFrequencyRequirement);

		[[nodiscard]] int CountRepeats() const;


		bool Match() override;
		

	private:
		std::shared_ptr<IExpectedPattern> patternMatcher;
		int countRepeats;
		const int expectedRepeats;
	};
}





