#pragma once
#include <string>

namespace ExpectationLib
{
	class IHasId
	{
	public:
		virtual ~IHasId() = default;

		// Unique identifier
		virtual const std::string GetId() const = 0;
	};
}
