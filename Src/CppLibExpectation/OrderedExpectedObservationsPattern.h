#pragma once
#include <vector>

#include "IExpectatedObservationsPattern.h"
#include "IExpectation.h"

namespace ExpectationLib
{
	 /// A pattern matcher that expects observations to meet a list expectation that must occur in order
    /// Other observations that do not meet expectation can occur in between
    class OrderedExpectedObservationsPattern : public IExpectatedObservationsPattern {
    public:
        /// A matcher that expects observations to meet a list expectation that must occur in order
        /// \param expectations Expectations where each must not match before the prior expectation
        /// \param observations Observations that must match the list of ordered expectations
        OrderedExpectedObservationsPattern(std::vector<IExpectation*> expectations, std::vector<Observation*> observations) {
            Expectations = expectations;
            Observations = observations;
        }

        /// Expectations
        std::vector<Observation*> Observations;
        /// Expectations
        std::vector<IExpectation*> Expectations;
        /// Unmatched expectations
        std::vector<IExpectation*> UnmatchedExpectations() {
            std::vector<IExpectation*> unmatched;
            for (auto expectation : Expectations) {
                if (std::find(MatchedExpectations.begin(), MatchedExpectations.end(), expectation) == MatchedExpectations.end()) {
                    unmatched.push_back(expectation);
                }
            }
            return unmatched;
        }
        /// Matched expectations
        std::vector<IExpectation*> MatchedExpectations;

        /// Match
        bool Match() {
            int countMatches = 0;
            int i = 0;
            for (auto observation : Observations) {
                if (i > Expectations.size() - 1) continue;
                if (!Expectations[i]->Match(observation)) continue; // can have other unmatched observations in between
                MatchedExpectations.push_back(Expectations[i]);
                i++;
                countMatches++;
            }
            return countMatches == Expectations.size();
        }
    };
}
