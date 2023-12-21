#include "OrderedExpectationsPattern.h"

#include <map>
#include "Node.h"
#include "Tree.h"

namespace ExpectationLib
{	
	template<typename KeyType, typename ValueType> 
	std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x )
	{
	  using pairtype=std::pair<KeyType,ValueType>; 
	  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
	        return p1.second < p2.second;
	  }); 
	}
	
	template<typename T> 
	std::shared_ptr<Node<T>> GetNodeWithMaxChildren( const std::shared_ptr<Node<T>>& x )
	{
	  using item=std::shared_ptr<Node<T>>;
	  return *std::max_element(x->Children.begin(), x->Children.end(), [] (const item & p1, const item & p2) {
	        return p1->Children.size() < p2->Children.size();
	  }); 
	}

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


	std::vector<std::string>
	OrderedExpectationsPattern::DetectOrder() const
	{
		std::map<std::tuple<std::string, std::string>, int> orders;

		for(auto oo = 0; oo < Observations.size();oo++)
		{
			const auto outerObservation = Observations[oo];
			int innerObservationIndex = oo+1;
			while(innerObservationIndex <= Observations.size()-1 && Observations[innerObservationIndex]->GetId() != outerObservation->GetId())
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
				
		
		
		auto unorderedTuples = std::vector<std::tuple<std::string, std::string>>();
		auto unorderedPattern = std::vector<std::string>();

		for(auto& item : orders)
		{
			auto const& [key, value] = item;
			auto const& [before, after] = key;

			unorderedTuples.push_back(key);
			unorderedPattern.push_back(before);
			unorderedPattern.push_back(after);
		}

		//auto tree = std::vector<std::shared_ptr<Node<std::string>>>();
		Tree<std::string> tree;
		for (const auto& unorderedTuple : unorderedTuples)
		{
			auto tuple = unorderedTuple;
			const auto & [before, after] = tuple;

			if(tree.IsEmpty())
			{				
				const auto afterNode = std::make_shared<Node<std::string>>(after);
				const auto beforeNode = std::make_shared<Node<std::string>>(before);
				beforeNode->AddChild(afterNode);
			
				tree.AddRoot(beforeNode);
				continue;
			}

			const auto afterNode = std::make_shared<Node<std::string>>(after);
			const auto beforeNode = std::make_shared<Node<std::string>>(before);
			beforeNode->AddChild(afterNode);
			
			for (const std::shared_ptr<Node<std::string>>& currentTreeItem : tree.Root->Children)
			{				
				if(currentTreeItem->Item == beforeNode->Item)
				{
					// attach after current
					currentTreeItem->AddChild(afterNode);
					break;
				}

				if(currentTreeItem->Item == afterNode->Item)
				{
					// attach before current
					currentTreeItem->Parent->AddChild(afterNode->Parent);
					break;
				}			
				
				// look through mu children to add to one of them
				currentTreeItem->AttachToChildren(beforeNode, afterNode);				
			
			}	
		}

		auto orderedPattern = std::vector<std::string>();
		auto node = tree.Root;
		orderedPattern.push_back(node->Item);
		while(!node->Children.empty())
		{
			node = GetNodeWithMaxChildren(node);			
			orderedPattern.push_back(node->Item);
		}				

		return orderedPattern;
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
