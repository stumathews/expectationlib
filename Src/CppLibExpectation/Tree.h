#pragma once

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
		
		std::shared_ptr<Node<T>> Root {};
	private:
		bool empty = true;
	};
}