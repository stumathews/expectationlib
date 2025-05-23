﻿#pragma once
#include "ICircumstance.h"
#include "IParty.h"
#include "Party.h"
#include "Tree.h"

namespace ExpectationLib
{
	class GraphBuilder
	{
	public:
		static Tree<Party> BuildRelationGraph(const std::shared_ptr<ICircumstance>& circumstance, bool startFromReceiver = true);
		static void AddRelationsAsChildren(const std::shared_ptr<Node<Party>>& node, std::vector<std::string>& visited);
	};
}
