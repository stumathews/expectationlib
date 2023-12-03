#pragma once
#include <string>

#include "IHasId.h"
#include "IParty.h"

namespace ExpectationLib
{
	class IResponse : public IHasId
	{
		public:
	    virtual IParty* getFrom() = 0;
	    virtual void setFrom(IParty* from) = 0;
	    virtual std::string getContext() = 0;
	    virtual void setContext(std::string context) = 0;
	    std::string getId() override;
	};
}
