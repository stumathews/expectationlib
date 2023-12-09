#pragma once
namespace ExpectationLib
{
	class IExpectedObservationsPattern
	{
	public:
		virtual ~IExpectedObservationsPattern() = default;
		virtual bool Match() = 0;
	};
}
