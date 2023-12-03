#pragma once
namespace ExpectationLib
{
	class IExpectatedObservationsPattern {
public:
    virtual bool Match() = 0;
};
}
