#include "Ordering.h"
#include <map>
#include <vector>
#include "Node.h"
#include "Tree.h"

namespace ExpectationLib
{
	template<typename KeyType, typename ValueType> 
	std::pair<KeyType,ValueType> GetMaxOccurancesCount( const std::map<KeyType,ValueType>& x )
	{
	  using Pairtype=std::pair<KeyType,ValueType>; 
	  return *std::max_element(x.begin(), x.end(), [] (const Pairtype & p1, const Pairtype & p2) {
	        return p1.second < p2.second;
	  }); 
	}
	
	template<typename T> 
	std::shared_ptr<Node<T>> GetNodeWithMaxChildren( const std::shared_ptr<Node<T>>& x )
	{
	  using Item=std::shared_ptr<Node<T>>;
	  return *std::max_element(x->Children.begin(), x->Children.end(), [] (const Item & p1, const Item & p2) {
	        return p1->Children.size() < p2->Children.size();
	  }); 
	}

	Ordering::Ordering(ListOfObservations observations): observations(std::move(observations))
	{
		
	}

	std::vector<std::string> Ordering::DetectOrder() const
	{
		// Get Collection of tuples that show which items are encountered before others
		auto orders = GetOrderOccurances();

		// Get the orders that occurred the most
		const auto maxOccurredCount = GetMaxOccurancesCount(orders).second;

		// Remove other orders (keep most occurring orders)
		std::erase_if(orders, [=](const std::pair<std::tuple<std::string, std::string>, int> & item)
		{			
			auto const& [key, value] = item;
			return value != maxOccurredCount;
		});					

		// add orders that occur the most together in one list
		auto unorderedTuples = std::vector<std::tuple<std::string, std::string>>();

		for(auto& item : orders)
		{
			auto const& [key, value] = item;
			unorderedTuples.push_back(key);
		}

		// Order the tuples into an ordered list of items 
		return ExtractOrderFromOrderTree(CreateOrderTree(unorderedTuples));			
	}

	std::vector<std::string> Ordering::ExtractOrderFromOrderTree(const Tree<std::string>& orderedTree)
	{
		auto node = orderedTree.Root;

		// Collect the most frequent orders and order them
		auto orderedPattern = std::vector<std::string>();

		orderedPattern.push_back(node->Item);

		// Add nodes from the orderedTree with the most children as the longest ordered pattern.
		while(!node->Children.empty())
		{
			node = GetNodeWithMaxChildren(node);			
			orderedPattern.push_back(node->Item);
		}				

		return orderedPattern;
	}

	Tree<std::string> Ordering::CreateOrderTree(const std::vector<std::tuple<std::string, std::string>>& unorderedTuples) const
	{
		Tree<std::string> tree;
		for (const auto& unorderedTuple : unorderedTuples)
		{
			const auto& tuple = unorderedTuple;
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
		return tree;
	}

	std::map<std::tuple<std::string, std::string>, int> Ordering::GetOrderOccurances() const
	{
		std::map<std::tuple<std::string, std::string>, int> orders;

		for(auto oo = 0; oo < observations.size();oo++)
		{
			const auto outerObservation = observations[oo];
			int innerObservationIndex = oo+1;
			while(innerObservationIndex <= observations.size()-1 && observations[innerObservationIndex]->GetId() != outerObservation->GetId())
			{
				const auto innerObservation = observations[innerObservationIndex];
				// store [outerObservation, innerObservation]
				orders[std::tuple(outerObservation->GetId(),innerObservation->GetId())]++;
				innerObservationIndex++; // next inner observation
			}			
		}

		return orders;
	}

	

}
