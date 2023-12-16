#pragma once
namespace ExpectationLib
{
	class IExpectedPattern
	{
	public:
		virtual ~IExpectedPattern() = default;
		virtual bool Match() = 0;
		virtual int GetLastProcessedObservationIndex() = 0;
	};
}
