#pragma once
#include "ICircumstance.h"
#include "IExpectation.h"

namespace ExpectationLib
{
    class StimuliProducesResponseExpectation : public virtual IExpectation, public virtual IHasId
	{
    public:
        StimuliProducesResponseExpectation(const std::shared_ptr<IStimulus>& stimulus);
        StimuliProducesResponseExpectation(const std::shared_ptr<ICircumstance>& circumstance);
        
        std::string ToString() override;
        static std::string CreateId(const std::shared_ptr<IStimulus>& stimuli);
        bool Match(std::shared_ptr<Observation> observation) override;
        const std::string GetId() override;

        std::shared_ptr<IStimulus> GetStimulus();
        std::shared_ptr<IResponse> GetResponse();

    private:
        
        std::shared_ptr<IStimulus> stimulus;
        std::shared_ptr<IResponse> response;
    };
}
