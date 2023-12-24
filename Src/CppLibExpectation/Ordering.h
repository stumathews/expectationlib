#pragma once
#include <map>
#include <vector>
#include <xstring>
#include <string>
#include <vector>

#include "Observation.h"
#include "Tree.h"

namespace ExpectationLib
{
	typedef std::vector<std::shared_ptr<Observation>> ListOfObservations;
	typedef std::vector<std::tuple<std::string, std::string>> ListOfTuples;

	class Ordering
	{
	public:
		explicit Ordering(ListOfObservations observations);
		[[nodiscard]] Tree<std::string> CreateOrderTree(const std::vector<std::tuple<std::string, std::string>>& unorderedTuples) const;
		[[nodiscard]] std::map<std::tuple<std::string, std::string>, int> GetMapOrderOccurences() const;
		[[nodiscard]] std::vector<std::string> DetectOrder() const;
		Tree<std::string> BuildOrderedTree() const;
		static std::vector<std::string> ExtractOrderFromOrderTree(const Tree<std::string>& orderedTree);

	private:
		std::vector<std::shared_ptr<Observation>> observations;
	};
}



