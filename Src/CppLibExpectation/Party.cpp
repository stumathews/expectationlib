#include "Party.h"

namespace ExpectationLib
{
	Party::Party(const std::string& id, const std::string& role)
	{
		this->id = id;
		this->role = role;
	}

	const std::string Party::GetId()
	{
		return id;
	}

	std::string Party::GetRole()
	{
		return role;
	}
	
}
