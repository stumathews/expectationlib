#pragma once
#include "ContactResponse.h"
#include "ICircumstance.h"
#include "IExpectation.h"

namespace ExpectationLib
{

    class StimuliProducesResponseExpectation : public IExpectation, public IHasId {
    private:
        IStimulus* Stimuli;
        IResponse* Response;
    public:
        StimuliProducesResponseExpectation(IStimulus* stimuli, IResponse* response) {
            Stimuli = stimuli;
            Response = response;
        }
        StimuliProducesResponseExpectation(ICircumstance* circumstance) {
            Stimuli = circumstance->getStimulus();
            Response = circumstance->getResponse();
        }
        std::string Id() {
            return CreateId(Stimuli, Response);
        }
        std::string ToString() {
            return Stimuli->ToString() + " (Response: " + Response->ToString() + ")";
        }
        static std::string CreateId(IStimulus* stimuli, IResponse* response) {
            return stimuli->getSender()->getId() + stimuli->getReceiver()->getId() + response->getId();
        }
        bool Match(Observation* observation) {
            return observation->Stimulus->getSender()->Equals(Stimuli->getSender()) &&
                   observation->Stimulus->getReceiver()->Equals(Stimuli->getReceiver()) &&
                   observation->Response->Equals(Response);
        }
        bool Equals(StimuliProducesResponseExpectation* other) {
            return Stimuli->Equals(other->Stimuli) && Response->Equals(other->Response);
        }
        bool Equals(void* obj) {
            if (obj == nullptr) return false;
            if (this == obj) return true;
            if (typeid(obj) != typeid(this)) return false;
            return Equals((StimuliProducesResponseExpectation*)obj);
        }
        int GetHashCode() {
            return std::hash<StimuliProducesResponseExpectation*>()(this);
        }

        std::string getId() override;
        bool Match(ContactCircumstance* observation) override;
    };
}
