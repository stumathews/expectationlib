#pragma once
#include <string>

#include "IHasId.h"

namespace ExpectationLib {
    /// <summary>
    /// A sender or of recipient of a stimulus
    /// </summary>
    class IParty : public IHasId
	{
    public:
        /// <summary>
        /// A general, non-unique role that the party plays.
        /// <remarks>Eg. 'Accountant' or 'Logging System'</remarks>
        /// </summary>
        virtual std::string Role() = 0;
        std::string getId() override = 0;
    };
}



