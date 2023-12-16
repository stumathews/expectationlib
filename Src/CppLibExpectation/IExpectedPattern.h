#pragma once
namespace ExpectationLib
{
	class IExpectedPattern
	{
	public:
		virtual ~IExpectedPattern() = default;
		virtual bool Match() = 0;
		virtual int GetLastProcessedObservationIndex() = 0;
		virtual void SetStartingObservationIndex(int index) = 0;		
	};

	class BaseExpectedPattern : public virtual IExpectedPattern
	{
	public:
		int GetLastProcessedObservationIndex() override { return lastMatchedObservationIndex; }
		void SetStartingObservationIndex(const int index) override { startingObservationIndex = index; }
	protected:
		virtual bool FoundAt(const int index)
		{
			this->lastMatchedObservationIndex = index;
			return true;			
		}
        int lastMatchedObservationIndex = -1;
        int startingObservationIndex = 0;
	};
}
