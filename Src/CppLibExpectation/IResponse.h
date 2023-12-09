#pragma once
#include <string>
#include <memory>
#include "IHasId.h"
#include "IParty.h"

namespace ExpectationLib
{
	class IResponse : public IHasId
	{
		public:
	    virtual std::shared_ptr<IParty> GetFrom() = 0;
	    virtual void SetFrom(std::shared_ptr<IParty>from) = 0;
	    virtual std::string GetContext() = 0;
	    virtual void SetContext(std::string context) = 0;
	    virtual std::string GetId() = 0;
		virtual std::string ToString() = 0;
	};
}
