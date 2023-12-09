#include "pch.h"
#include "Party.h"

namespace ExpectationLib
{
	Party::Party(const std::string& id, const std::string& role)
	{
		this->id = id;
		this->role = role;
	}

	std::string Party::GetId()
	{
		return id;
	}

	std::string Party::GetRole()
	{
		return role;
	}

	bool Party::operator==(const Party& other) const
	{
		return id == other.id && role == other.role;
	}
}
