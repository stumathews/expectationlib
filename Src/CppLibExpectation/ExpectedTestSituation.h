#pragma once
#include <string>
#include <vector>

#include "ContactCircumstance.h"
#include "ContactCircumstanceBuilder.h"
#include "IExpectation.h"
#include "ISituation.h"
#include "Observation.h"
#include "OrderedExpectedObservationsPattern.h"
#include "Party.h"
#include "StimuliProducesResponseExpectation.h"


namespace ExpectationLib
{
	class ExpectedTestSituation final : public ISituation
	{
	public:
	    std::string TransactionId;
	    std::shared_ptr<IParty> Party1;
	    std::shared_ptr<IParty> Party2;
	    std::shared_ptr<IParty> Party3;
	    std::shared_ptr<IParty> Party4;

	    std::vector<std::shared_ptr<IExpectation>> GetMatchedExpectations()
		{
	        return _matchedExpectations;
	    }

	    std::vector<std::shared_ptr<IExpectation>> GetUnmatchedExpectations()
		{
			return _unmatchedExpectations;
	    }

	    ExpectedTestSituation(const std::string& transactionId, const std::shared_ptr<IParty>& party1, const std::shared_ptr<IParty>
	                          & party2, const std::shared_ptr<IParty>& party3, const std::shared_ptr<IParty>& party4)
		{
	        TransactionId = transactionId;
	        Party1 = party1;
	        Party2 = party2;
	        Party3 = party3;
	        Party4 = party4;
	    }

	    std::string ToString() const
	    {
	        std::string result;
	        int i = 0;
	        for (const auto& expectation : _matchedExpectations)
			{
	            result += " #" + std::to_string(++i) + ": Expectation: " + expectation->ToString() + "\n";
	        }
	        i = 0;

	        for (const auto& expectation : _unmatchedExpectations)
			{
	            result += " #" + std::to_string(++i) + ": Expectation: " + expectation->ToString() + " ** Unmatched ** \n";
	        }
	        return result;
	    }

	    bool Match(std::vector<std::shared_ptr<Observation>> observations) override {
	        std::string sharedResponseContext = TransactionId;
	        auto contactCircumstance1 = ContactCircumstanceBuilder::Build(Party1, Party2, sharedResponseContext, Party3);
	        auto contactCircumstance2 = ContactCircumstanceBuilder::Build(Party3, Party4, sharedResponseContext);
	        auto contactCircumstance3 = ContactCircumstanceBuilder::Build(Party4, Party3, sharedResponseContext);
	        auto contactCircumstance4 = ContactCircumstanceBuilder::Build(Party3, Party1, sharedResponseContext);
	        auto expect1 = std::make_shared<StimuliProducesResponseExpectation>(contactCircumstance1);
	        auto expect2 = std::make_shared< StimuliProducesResponseExpectation>(contactCircumstance2);
	        auto expect3 = std::make_shared< StimuliProducesResponseExpectation>(contactCircumstance3);
	        auto expect4 = std::make_shared< StimuliProducesResponseExpectation>(contactCircumstance4);
	        const std::vector<std::shared_ptr<IExpectation>> orderedExpectations = { expect1, expect2, expect3, expect4 };
	        auto matcher = new OrderedExpectedObservationsPattern(orderedExpectations, observations);
	        bool wasMatch = matcher->Match();
	        _unmatchedExpectations = matcher->UnmatchedExpectations();
	        _matchedExpectations = matcher->MatchedExpectations;
	        return wasMatch;
	    }

	private:
	    std::vector<std::shared_ptr<IExpectation>> _matchedExpectations;
	    std::vector<std::shared_ptr<IExpectation>> _unmatchedExpectations;
	};
}

