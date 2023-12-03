#pragma once
#include "ContactCircumstance.h"

namespace ExpectationLib
{
	class IExpectation {
	public:
	    virtual bool Match(ContactCircumstance* observation) = 0;
	};
}
