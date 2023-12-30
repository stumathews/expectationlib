#pragma once
#include "Node.h"

namespace ExpectationLib
{
	template <typename T>
	class ITreeNodeStrategy
	{
	public:
		virtual ~ITreeNodeStrategy() = default;
		virtual void AddNode(const std::shared_ptr<Node<T>>& node, const std::shared_ptr<Node<T>>& root) = 0;
	};
}
