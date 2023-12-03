#pragma once
#include <string>

#include "IParty.h"
#include "IResponse.h"

namespace ExpectationLib
{
	class ContactResponse : public IResponse {
	public:
	    std::string Response;
	    IParty* Receiver;
	    ContactResponse(std::string response, IParty* receiver) {
	        Response = response;
	        Receiver = receiver;
	    }

	    std::string getId() override;
	    IParty* getFrom() override;
	    void setFrom(IParty* from) override;
	    std::string getContext() override;
	    void setContext(std::string context) override;
	};
}
