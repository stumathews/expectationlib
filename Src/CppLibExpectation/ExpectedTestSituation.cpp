#include "ExpectedTestSituation.h"

#include "ContactCircumstanceBuilder.h"
#include "OrderedExpectedObservationsPattern.h"
#include "StimuliProducesResponseExpectation.h"

namespace ExpectationLib
{
	std::vector<std::shared_ptr<IExpectation>> ExpectedTestSituation::GetMatchedExpectations()
	{
		return matchedExpectations;
	}

	std::vector<std::shared_ptr<IExpectation>> ExpectedTestSituation::GetUnmatchedExpectations()
	{
		return unmatchedExpectations;
	}

	ExpectedTestSituation::ExpectedTestSituation(const std::string& transactionId,
		const std::shared_ptr<IParty>& party1, const std::shared_ptr<IParty>& party2,
		const std::shared_ptr<IParty>& party3, const std::shared_ptr<IParty>& party4)
	{
		CommonContext = transactionId;
		Party1 = party1;
		Party2 = party2;
		Party3 = party3;
		Party4 = party4;
	}

	std::string ExpectedTestSituation::ToString() const
	{
		std::string result;
		int i = 0;
		for (const auto& expectation : matchedExpectations)
		{
			result += " #" + std::to_string(++i) + ": Expectation: " + expectation->ToString() + "\n";
		}
		i = 0;

		for (const auto& expectation : unmatchedExpectations)
		{
			result += " #" + std::to_string(++i) + ": Expectation: " + expectation->ToString() + " ** Unmatched ** \n";
		}
		return result;
	}

	bool ExpectedTestSituation::Match(std::vector<std::shared_ptr<Observation>> observations)
	{
		std::string sharedResponseContext = CommonContext;
		auto contactCircumstance1 = ContactCircumstanceBuilder::Build(Party1, Party2, sharedResponseContext, Party3);
		auto contactCircumstance2 = ContactCircumstanceBuilder::Build(Party3, Party4, sharedResponseContext);
		auto contactCircumstance3 = ContactCircumstanceBuilder::Build(Party4, Party3, sharedResponseContext);
		auto contactCircumstance4 = ContactCircumstanceBuilder::Build(Party3, Party1, sharedResponseContext);

		const auto expect1 = std::make_shared<StimuliProducesResponseExpectation>(contactCircumstance1);
		const auto expect2 = std::make_shared<StimuliProducesResponseExpectation>(contactCircumstance2);
		const auto expect3 = std::make_shared<StimuliProducesResponseExpectation>(contactCircumstance3);
		const auto expect4 = std::make_shared<StimuliProducesResponseExpectation>(contactCircumstance4);

		const std::vector<std::shared_ptr<IExpectation>> orderedExpectations = { expect1, expect2, expect3, expect4 };
		const auto matcher = std::make_shared< OrderedExpectedObservationsPattern>(orderedExpectations, observations);
		const bool wasMatch = matcher->Match();

		unmatchedExpectations = matcher->UnmatchedExpectations();
		matchedExpectations = matcher->MatchedExpectations;
		return wasMatch;
	}
}
