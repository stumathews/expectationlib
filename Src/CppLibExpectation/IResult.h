#pragma once

namespace ExpectationLib
{
	class IParty;

	class IResult
	{
	public:
		virtual ~IResult() = default;
		[[nodiscard]] virtual std::shared_ptr<IParty> GetSender() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IParty> GetReceiver() const = 0;
	};
	
}
