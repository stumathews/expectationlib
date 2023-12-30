#pragma once
#include <memory>
#include <queue>
#include <string>
#include "ITreeNodeStrategy.h"
#include "Node.h"

namespace ExpectationLib
{
	template <typename T>
	class BinaryTreeNodeStrategy final : virtual public ITreeNodeStrategy<T>
	{
	public:
		BinaryTreeNodeStrategy()
		{			
			index = 0;
			lastParentNode = nullptr;
			swingNode = nullptr;
		}

		void AddNode(const std::shared_ptr<Node<T>>& node, const std::shared_ptr<Node<T>>& root) override
		{
			if(lastParentNode == nullptr) lastParentNode = root;

			// Add child to the last parent
			lastParentNode->AddChild(node);

			index++; // Tree Index ( tree is can only have 2 children per node (child 0 & child 1 only).

			// exception-case: add first node as swing node.
			if(lastParentNode->Children.size() == 1 && index == 1)
			{
				swingQueue.push(node);
			}

			if(lastParentNode->Children.size() == 2)
			{
				// Swing to the other side.

				// use last child as future swinging node
				swingQueue.push(node);

				// Set the next parent to be the swing node, effectively swing sides
				lastParentNode = swingQueue.front();

				// no need to swing from this node anymore
				swingQueue.pop();
			}					
		}
	private:
		std::shared_ptr<Node<T>> lastParentNode = nullptr;
		std::shared_ptr<Node<T>> swingNode = nullptr;
		std::queue<std::shared_ptr<Node<T>>> swingQueue;		
		short index = 0;
	};
}
