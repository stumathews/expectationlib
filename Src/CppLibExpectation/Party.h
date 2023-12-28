#pragma once
#include "IParty.h"
#include <string>

namespace ExpectationLib
{    
	class Party final : public virtual IParty
	{
	public:
		Party(const std::string& id, const std::string& role = "");

	    std::string GetRole() override;
		const std::string GetId() override;		
	private:
	    
	    std::string id;
	    std::string role;
	};
}
