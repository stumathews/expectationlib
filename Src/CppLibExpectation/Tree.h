#pragma once
#include "Node.h"
#include "BinaryTreeStrategy.h"

namespace ExpectationLib
{	

	template <typename T>
	class Tree
	{
	public:
		
		enum class TreeType { Binary };

		explicit Tree(TreeType treeType = TreeType::Binary)
		{

			if(treeType == TreeType::Binary)
			{
				treeStrategy = std::make_shared<BinaryTreeNodeStrategy<T>>();
			}
			else
			{
				throw std::exception("Tree: Unsupported tree type.");
			}
		}
		void AddRoot(std::shared_ptr<Node<T>>& root)
		{
			Root = root;
			empty = false;
		}

		[[nodiscard]] bool IsEmpty() const
		{
			return empty;
		}

		std::shared_ptr<Node<T>> FindNodeItem(T item)
		{
			for (std::shared_ptr<Node<T>> child : Root->Children)
			{
				if(child->Item == item)
				{
					return child;
				}

				auto childFound = child->FindChildItem(item);
				if(childFound != nullptr) { return childFound;}
				return nullptr;		
				
			}
			return nullptr;
		}

		void AddNode(std::shared_ptr<Node<T>>& node)
		{
			if(empty)
			{				
				AddRoot(node);
			}
			else
			{
				treeStrategy->AddNode(node, Root);
			}
		}

		std::shared_ptr<Node<T>> Root;
	private:
		std::shared_ptr<ITreeNodeStrategy<T>> treeStrategy;
		
		bool empty = true;
	};
}
