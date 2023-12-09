#pragma once
#include <string>

namespace ExpectationLib
{
	class IHasId
	{
	public:
		virtual ~IHasId() = default;
		virtual std::string GetId() = 0;
	};
}
