#pragma once
#include <string>
#include <memory>
#include "IHasId.h"
#include "IResult.h"
#include "Option.h"

namespace ExpectationLib
{
	class IParty;
	class ICircumstance;
	class IStimulus;
	class IResponse : public virtual IHasId
	{
		public:
		[[nodiscard]] virtual libmonad::Option<std::shared_ptr<IResult>> GetResult() = 0;
		[[nodiscard]] virtual std::string GetContext() const = 0;
		virtual std::string ToString() = 0;

		// Start this response (should modify/update/data in the response as a result of being started by a stimulus event)
		virtual std::shared_ptr<ICircumstance> Start() = 0;

		// Stimulus that caused this response
	    virtual std::shared_ptr<IStimulus> GetStimulus() = 0;
	};
}
