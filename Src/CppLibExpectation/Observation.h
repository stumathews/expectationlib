#pragma once

#include <string>

namespace ExpectationLib {
    /// <summary>
    /// An Observation is an observed association between a Stimuli and a Response
    /// </summary>
    class Observation : IHasId {
    private:
        /// <summary>
        /// The Stimulus
        /// </summary>
        IStimulus* Stimulus;
        /// <summary>
        /// The Response
        /// </summary>
        IResponse* Response;
        /// <summary>
        /// Observational Context
        /// </summary>
        std::string Context;

    public:
        Observation(IStimulus* stimulus, IResponse* response, std::string context) {
            Stimulus = stimulus;
            Response = response;
            Context = context;
        }

        Observation(ICircumstance* circumstance, std::string context) : Observation(circumstance->getStimulus(), circumstance->getResponse(), context) {
        }

        /// <summary>
        /// Reconstruct an Observation Id from its constituent parts
        /// </summary>
        /// <param name="stimulus">Stimulus</param>
        /// <param name="response">Response</param>
        /// <returns></returns>
        static std::string CreateId(IStimulus* stimulus, IResponse* response) {
            return stimulus->getSender()->getId() + stimulus->getReceiver()->getId() + response->getFrom()->getId() + response->getId();
        }

        /// <inheritdoc />
        std::string Id() {
            return CreateId(Stimulus, Response);
        }
    };
}


