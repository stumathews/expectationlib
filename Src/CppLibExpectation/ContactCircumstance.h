#pragma once
#include "ICircumstance.h"

namespace ExpectationLib
{
    // A particular response to a contact stimulus
    class ContactCircumstance final : public ICircumstance
	{
    public:
        
        ContactCircumstance(const std::shared_ptr<IResponse>& response);
        
        std::shared_ptr<IStimulus> GetStimulus() override;
        std::shared_ptr<IResponse> GetResponse() override;
        std::shared_ptr<IParty> GetFrom();
        const std::string GetId() override;
        ;
    private:
        std::shared_ptr<IStimulus> stimulus;
        std::shared_ptr<IParty> from;
        std::shared_ptr<IResponse> response;
        std::string id;
	};

}

