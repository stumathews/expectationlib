#pragma once
#include "ICircumstance.h"

namespace ExpectationLib
{
    // A particular response to a contact stimulus
    class ContactCircumstance final : public ICircumstance
	{
    public:
        
        ContactCircumstance(const std::shared_ptr<IStimulus>& stimulus, const std::string& responseContext, const std::shared_ptr<IParty>& overrideFrom = nullptr);

        std::shared_ptr<IStimulus> GetStimulus() override;
        std::shared_ptr<IResponse> GetResponse() override;
        std::shared_ptr<IParty> GetFrom();

    private:
        std::shared_ptr<IStimulus> stimulus;
        std::shared_ptr<IParty> from;
        std::string responseContext;
    };

}

