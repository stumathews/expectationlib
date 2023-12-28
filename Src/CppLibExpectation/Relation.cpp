#include "Relation.h"

namespace ExpectationLib
{
	Relation::Relation(std::string name, std::shared_ptr<IParty> to): Name(std::move(name)), To(std::move(to))
	{
	}
}
