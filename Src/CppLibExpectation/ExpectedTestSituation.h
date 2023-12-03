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
	class ExpectedTestSituation : public ISituation {
public:
    std::string TransactionId;
    IParty* Party1;
    IParty* Party2;
    IParty* Party3;
    IParty* Party4;
    std::vector<IExpectation*> GetMatchedExpectations() {
        return _matchedExpectations;
    }
    std::vector<IExpectation*> GetUnmatchedExpectations() {
        return _unmatchedExpectations;
    }
    ExpectedTestSituation(std::string transactionId, IParty* party1, IParty* party2, IParty* party3, IParty* party4) {
        TransactionId = transactionId;
        Party1 = party1;
        Party2 = party2;
        Party3 = party3;
        Party4 = party4;
    }
    std::string ToString() {
        std::string result;
        int i = 0;
        for (auto expectation : _matchedExpectations) {
            result += " #" + std::to_string(++i) + ": Expectation: " + expectation + "\n";
        }
        i = 0;
        for (auto expectation : _unmatchedExpectations) {
            result += " #" + std::to_string(++i) + ": Expectation: " + expectation + " ** Unmatched ** \n";
        }
        return result;
    }
    bool Match(std::vector<Observation*> observations) override {
        std::string sharedResponseContext = TransactionId;
        auto contactCircumstance1 = ContactCircumstanceBuilder::Build(Party1, Party2, sharedResponseContext, Party3);
        auto contactCircumstance2 = ContactCircumstanceBuilder::Build(Party3, Party4, sharedResponseContext);
        auto contactCircumstance3 = ContactCircumstanceBuilder::Build(Party4, Party3, sharedResponseContext);
        auto contactCircumstance4 = ContactCircumstanceBuilder::Build(Party3, Party1, sharedResponseContext);
        auto expect1 = new StimuliProducesResponseExpectation(contactCircumstance1);
        auto expect2 = new StimuliProducesResponseExpectation(contactCircumstance2);
        auto expect3 = new StimuliProducesResponseExpectation(contactCircumstance3);
        auto expect4 = new StimuliProducesResponseExpectation(contactCircumstance4);
        std::vector<IExpectation*> orderedExpectations = { expect1, expect2, expect3, expect4 };
        auto matcher = new OrderedExpectedObservationsPattern(orderedExpectations, observations);
        bool wasMatch = matcher->Match();
        _unmatchedExpectations = matcher->UnmatchedExpectations;
        _matchedExpectations = matcher->MatchedExpectations;
        return wasMatch;
    }

private:
    std::vector<IExpectation*> _matchedExpectations;
    std::vector<IExpectation*> _unmatchedExpectations;
};
}

