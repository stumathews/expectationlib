#include "GraphBuilder.h"

#include "Party.h"

namespace ExpectationLib
{

	Tree<Party> GraphBuilder::Build(const std::shared_ptr<ICircumstance>& circumstance)
	{
		auto sender = circumstance->GetResponse()->GetSender();
		const auto receiver = circumstance->GetResponse()->GetReceiver();

		Tree<Party> tree;

		

		const auto node = std::make_shared<Node<Party>>(*std::dynamic_pointer_cast<Party>(receiver));

		AddRelationsAsChildren(node);

		tree.AddRoot(node);

		return tree;
	}

	void GraphBuilder::AddRelationsAsChildren(const std::shared_ptr<Node<Party>>& node)
	{
		for(const auto& relation : node->Item.GetRelations())
		{
			Party item = *std::dynamic_pointer_cast<Party>(relation.To);
			const auto newChild = std::make_shared<Node<Party>>(item);
			if(node->Parent != nullptr && !node->Parent->FindChildItem(newChild->Item))
			{
				node->AddChild(newChild);
				AddRelationsAsChildren(newChild);
			}
		}			
	};
}
