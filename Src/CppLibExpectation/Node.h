#pragma once
#include <memory>
#include <vector>

namespace ExpectationLib
{
	template <typename T>
	class Node : public std::enable_shared_from_this<Node<T>>
	{
	public:
		explicit Node(T item) : Item(item) { }
		T Item;

		std::shared_ptr<Node<T>> Parent = nullptr;
		std::vector<std::shared_ptr<Node>> Children {};

		std::shared_ptr<Node<T>> FindChildItem(T item)
		{
			for (std::shared_ptr<Node<T>> child : Children)
			{
				if(child->Item == item)
				{
					return child;
				}
				auto childItem = child->FindChildItem(item);
				if(childItem != nullptr) {return childItem;}
				return nullptr;
			}
			return nullptr;
		}

		void AttachToChildren(std::shared_ptr<Node> beforeNode, std::shared_ptr<Node> afterNode)
		{
			for (const auto& node : Children)
			{
				// attach before
				if(node->Item == beforeNode->Item)
				{
					node->AddChild(afterNode);
					return;
				}
				if(node->Item == afterNode->Item)
				{
					// attach after
					afterNode->AddChild(node);
					return;
				}
				node->AttachToChildren(beforeNode, afterNode);
			}
		}

		void AddChild(std::shared_ptr<Node> child)
		{
			Children.push_back(child);
			child->Parent = this->shared_from_this();
		}
	};
}
