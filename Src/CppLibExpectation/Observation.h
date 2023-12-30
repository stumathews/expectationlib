#pragma once
#include <memory>
#include <string>
#include "ICircumstance.h"
#include "IResponse.h"
#include "IStimulus.h"

namespace ExpectationLib
{
    /// <summary>
    /// An Observation is an observed association between a Stimuli and a Context
    /// </summary>
    class Observation : public virtual IHasId
	{
    public:
        Observation(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response, const std::string& observationContext);

        Observation(const std::shared_ptr<ICircumstance>& circumstance, const std::string& observationContext);

        bool operator==(const Observation& other) const;

        /// <summary>
        /// Reconstruct an Observation GetId from its constituent parts
        /// </summary>
        /// <param name="stimulus">Stimulus</param>
        /// <param name="response">Context</param>
        /// <returns></returns>
        static std::string CreateId(const std::shared_ptr<IStimulus>& stimulus,
                                    const std::shared_ptr<IResponse>& response);

        /// <inheritdoc />
        [[nodiscard]] const std::string GetId() const override;

        std::shared_ptr<IStimulus> GetStimulus() { return stimulus; }
        std::shared_ptr<IResponse> GetResponse() { return response; }

    private:
        std::shared_ptr<IStimulus> stimulus;
        std::shared_ptr<IResponse> response;
        std::string context;

    };
}


