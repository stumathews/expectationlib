#pragma once

using namespace ExpectationLib;

// Represents an established S-R link, i.e where an event causes a response that produces a circumstance
class SrLink
{
public:

	SrLink(const std::shared_ptr<IStimulus>& stimulus, const std::shared_ptr<IResponse>& response)
	{
		this->circumstance = stimulus->Cause(response);
	}

	std::shared_ptr<ICircumstance> GetCircumstance() const { return circumstance; }
	std::shared_ptr<IResponse> GetResponse() const { return circumstance->GetResponse(); }

private:	
	std::shared_ptr<ICircumstance> circumstance;
};