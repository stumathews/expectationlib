#pragma once
#include "IParty.h"
#include <string>

namespace ExpectationLib
{    
	class Party final : public IParty
	{
	public:
		Party(const std::string& id, const std::string& role = "");
		std::string GetId() override;    
	    std::string GetRole() override;

	private:
	    
	    std::string id;
	    std::string role;
	};
}
