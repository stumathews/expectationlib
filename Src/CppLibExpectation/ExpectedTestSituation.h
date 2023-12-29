#pragma once
#include <string>
#include <vector>

#include "IExpectation.h"
#include "ISituation.h"
#include "Observation.h"
#include "Party.h"


namespace ExpectationLib
{
	class ExpectedTestSituation final : public ISituation
	{
	public:
	    std::shared_ptr<IParty> Party1;
	    std::shared_ptr<IParty> Party2;
	    std::shared_ptr<IParty> Party3;
	    std::shared_ptr<IParty> Party4;

	    std::vector<std::shared_ptr<IExpectation>> GetMatchedExpectations();
	    std::vector<std::shared_ptr<IExpectation>> GetUnmatchedExpectations();

	    ExpectedTestSituation(
			const std::shared_ptr<IParty>& party1, 
			const std::shared_ptr<IParty>& party2, 
			const std::shared_ptr<IParty>& party3, 
			const std::shared_ptr<IParty>& party4);

	    [[nodiscard]] std::string ToString() const;
	    bool Match(std::vector<std::shared_ptr<Observation>> observations) override;

    private:
	    std::vector<std::shared_ptr<IExpectation>> matchedExpectations;
	    std::vector<std::shared_ptr<IExpectation>> unmatchedExpectations;
	};
}

