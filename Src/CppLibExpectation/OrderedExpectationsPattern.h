#pragma once
#include <memory>
#include <vector>
#include "IExpectedPattern.h"
#include "IExpectation.h"
#include "Observation.h"

namespace ExpectationLib
{
	 /// A pattern matcher that expects observations to meet a list expectation that must occur in order
    /// Other observations that do not meet expectation can occur in between
    class OrderedExpectationsPattern final : public BaseExpectedPattern
	{
    public:
        /// A matcher that expects observations to meet a list expectation that must occur in order
        /// \param expectations Expectations where each must not match before the prior expectation
        /// \param observations Observations that must match the list of ordered expectations
        OrderedExpectationsPattern(const std::vector<std::shared_ptr<IExpectation>>& expectations, std::vector<std::shared_ptr<Observation>> observations);

        std::vector<std::shared_ptr<Observation>> Observations;
        std::vector<std::shared_ptr<IExpectation>> Expectations;
        std::vector<std::shared_ptr<IExpectation>> UnmatchedExpectations();
        std::vector<std::shared_ptr<IExpectation>> MatchedExpectations;
        bool Match() override;
	};
}
