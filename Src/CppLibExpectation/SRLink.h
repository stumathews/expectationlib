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

	// Get original stimulus (never changes)
	[[nodiscard]] std::shared_ptr<IStimulus> GetStimulus() const
	{
		// Remember: stimulus never changes, even after it causes a response.
		// For results that occured due to stimulus, inspect response object
		return GetResponse()->GetStimulus();
	}

	// Get changes to sender that resulted from stimulus event causing the response 
	[[nodiscard]] std::shared_ptr<IParty> GetSender() const
	{
		const auto responseResult = circumstance->GetResponse()->GetResult().ThrowIfNone();
		return responseResult->GetSender();
	}

	// Get changes to receiver that resulted from stimulus event causing the response 
	[[nodiscard]] std::shared_ptr<IParty> GetReceiver() const
	{
		const auto responseResult = circumstance->GetResponse()->GetResult().ThrowIfNone();
		return responseResult->GetReceiver();
	}

	[[nodiscard]] std::shared_ptr<ICircumstance> GetCircumstance() const
	{
		return circumstance;
	}

	[[nodiscard]] std::shared_ptr<IResponse> GetResponse() const
	{
		return circumstance->GetResponse();
	}

private:	
	std::shared_ptr<ICircumstance> circumstance;
};