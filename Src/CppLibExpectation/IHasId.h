#pragma once
#include <string>

namespace ExpectationLib
{
	class IHasId
	{
	public:
		virtual ~IHasId() = default;

		// Unique identifier
		virtual std::string GetId() = 0;
	};
}
