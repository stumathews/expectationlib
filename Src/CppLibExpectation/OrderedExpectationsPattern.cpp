#include "OrderedExpectationsPattern.h"

#include <map>

namespace ExpectationLib
{
	OrderedExpectationsPattern::OrderedExpectationsPattern(
		const std::vector<std::shared_ptr<IExpectation>>& expectations,
		const std::vector<std::shared_ptr<Observation>>& observations)
	{
		Expectations = expectations;
		Observations = observations;
	}

	std::vector<std::shared_ptr<IExpectation>> OrderedExpectationsPattern::UnmatchedExpectations()
	{
		std::vector<std::shared_ptr<IExpectation>> unmatched;
		for (const auto& expectation : Expectations) 
		{
			if (std::ranges::find(MatchedExpectations, expectation) == MatchedExpectations.end()) 
			{
				unmatched.push_back(expectation);
			}
		}
		return unmatched;
	}

	template<typename KeyType, typename ValueType> 
	std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x )
	{
	  using pairtype=std::pair<KeyType,ValueType>; 
	  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
	        return p1.second < p2.second;
	  }); 
	}

	std::vector<std::string>
	OrderedExpectationsPattern::DetectOrder() const
	{
		std::map<std::tuple<std::string, std::string>, int> orders;

		for(auto oo = 0; oo < Observations.size();oo++)
		{
			const auto outerObservation = Observations[oo];
			int innerObservationIndex = oo+1;
			while(innerObservationIndex < Observations.size()-1 && Observations[innerObservationIndex]->GetId() != outerObservation->GetId())
			{
				const auto innerObservation = Observations[innerObservationIndex];
				// store [outerObservation, innerObservation]
				orders[std::tuple(outerObservation->GetId(),innerObservation->GetId())]++;
				innerObservationIndex++; // next inner observation
			}			
		}

		// get the most repeated pattern, forget the other smaller patterns
		const auto max = get_max(orders).second;
		std::erase_if(orders, [=](const std::pair<std::tuple<std::string, std::string>, int> & item)
		{			
			auto const& [key, value] = item;
			return value != max;
		});

		// assign numerical order to before -> after groups
		auto orderedObservations = std::vector<std::string>();
		int i = 0;
		for(auto& item : orders)
		{
			auto const& [key, value] = item;
			auto const& [before, after] = key;

			if(i == 0)
			{
				orderedObservations.push_back(before);
				orderedObservations.push_back(after);
			}
			else
			{
				if(std::ranges::find(orderedObservations, before) == orderedObservations.end())
					orderedObservations.push_back(before);
				if(std::ranges::find(orderedObservations, after) == orderedObservations.end())
					orderedObservations.push_back(after);
			}

			i++;
		}

		return orderedObservations;
	}

	bool OrderedExpectationsPattern::Match()
	{
		int countMatches = 0;
		int e = 0;
		for (auto o = startingObservationIndex; o < Observations.size(); o++) 
		{
			if (e > Expectations.size() - 1) continue;
			if (!Expectations[e]->Match(Observations[o])) continue; // can have other unmatched observations in between
			MatchedExpectations.push_back(Expectations[e]);			
			e++;
			countMatches++;
			if(countMatches == Expectations.size())
			{
				return FoundAt(o);
			}
		}
		return countMatches == Expectations.size();
	}
}
