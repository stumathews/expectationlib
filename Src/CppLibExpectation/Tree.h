#pragma once
#include "Node.h"
#include "BinaryTreeStrategy.h"

namespace ExpectationLib
{
	template<typename T> 
		std::shared_ptr<Node<T>> GetNodeWithMaxChildren2( const std::shared_ptr<Node<T>>& x )
		{
		  using Item=std::shared_ptr<Node<T>>;
		  return *std::max_element(x->Children.begin(), x->Children.end(), [] (const Item & p1, const Item & p2) {
		        return p1->Children.size() < p2->Children.size();
		  }); 
		}

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

		int GetDepth() const
		{
			int depth = 0;

			std::shared_ptr<Node<T>> node = Root;
			while(node->Children.size() > 0)
			{
				std::shared_ptr<Node<T>> child = GetNodeWithMaxChildren2(node);		
				
				depth++;
				node = child;
								
								
			}
			return depth;
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
