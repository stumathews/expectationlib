#pragma once
#include <string>

namespace ExpectationLib
{
	class IHasId {
	public:
	    virtual std::string getId() = 0;
	};
}
