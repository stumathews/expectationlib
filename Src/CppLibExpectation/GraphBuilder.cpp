#include "GraphBuilder.h"
#include "Party.h"

namespace ExpectationLib
{

	Tree<Party> GraphBuilder::BuildRelationGraph(const std::shared_ptr<ICircumstance>& circumstance, const bool startFromReceiver)
	{		
		std::vector<std::string> visitedPartyIds;
		Tree<Party> tree;		

		// Construct the root node as the the party that received the stimulus resulting in this circumstance
		auto rootNode = std::make_shared<Node<Party>>(*std::dynamic_pointer_cast<Party>(startFromReceiver 
			? circumstance->GetResponse()->GetReceiver()
			: circumstance->GetResponse()->GetSender()));

		// Work backwards through its relations to create a tree of parties eg: party4 -> party3 -> party2 -> party1
		AddRelationsAsChildren(rootNode, visitedPartyIds);

		tree.AddRoot(rootNode);

		return tree;
	}

	void GraphBuilder::AddRelationsAsChildren(const std::shared_ptr<Node<Party>>& node, std::vector<std::string>& visited)
	{
		for(const auto& relation : node->Item.GetRelations())
		{
			const auto toParty = std::dynamic_pointer_cast<Party>(relation.To);
			const auto alreadyVisited = visited.end() != std::ranges::find_if(visited.begin(), visited.end(), [=]( const std::string& id){ return id == toParty->GetId(); });

			 // Skip relations back to to me or I have already visited
			if(toParty->GetId() == node->Item.GetId() || alreadyVisited) 
			{
				continue;
			}

			// Add the child to this node
			const auto newChild = std::make_shared<Node<Party>>(*toParty); // caution: this creates a copy
			node->AddChild(newChild);

			// we wont want to visited links to this party again...
			visited.push_back(node->Item.GetId());

			// Visit the children
			AddRelationsAsChildren(newChild, visited);			
		}			
	};
}
