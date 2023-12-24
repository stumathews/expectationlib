#pragma once
#include "Node.h"
#include <queue>

namespace ExpectationLib
{

	template <typename T>
	class Tree
	{
	public:
		void AddRoot(std::shared_ptr<Node<T>> root)
		{
			Root = root;
			empty = false;
			index = 0;
			LastParentNode = root;
			SwingNode = nullptr;
		}

		bool IsEmpty() const
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

		void AddNode(const std::shared_ptr<Node<std::string>>& node)
		{
			if(empty)
			{
				AddRoot(node);
			}
			else
			{
				// ignore item if its the same as the last parent node (3-2, 3-1)... only take 2 & 1 ignore leading 3s)
				if(LastParentNode->Item == node->Item) return;

				// Add child to the last parent
				LastParentNode->AddChild(node);

				index++; // Tree Index ( tree is can only have 2 children per node (child 0 & child 1 only).

				// exception-case: add first node as swing node.
				if(LastParentNode->Children.size() == 1 && index == 1)
				{
					swingQueue.push(node);
				}

				if(LastParentNode->Children.size() == 2)
				{
					// Swing to the other side.

					// use last child as future swinging node
					swingQueue.push(node);

					// Set the next parent to be the swing node, effectively swing sides
					LastParentNode = swingQueue.front();

					// no need to swing from this node anymore
					swingQueue.pop();
				}				
			}
		}

		std::shared_ptr<Node<T>> LastParentNode = nullptr;
		std::shared_ptr<Node<std::string>> SwingNode = nullptr;
		std::shared_ptr<Node<T>> Root {};
	private:
		std::queue<std::shared_ptr<Node<std::string>>> swingQueue;
		bool empty = true;
		short index = 0;
	};
}