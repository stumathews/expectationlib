#include "pch.h"

#include <gtest/gtest.h>

#include "ContactCircumstanceBuilder.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "GraphBuilder.h"
#include "Observer.h"
#include "Ordering.h"
#include "Party.h"
#include "Option.h"
#include "SRLink.h"

using namespace ExpectationLib;

TEST(Demos, CreateCircumstance)
{
	/* Represent as S-R link (i.e, a circumstance) */

	// Prepare the parties that will be involved in the stimulus event
	const auto sender1 = Party::Create("sender1");
	const auto receiver1 = Party::Create("receiver1");
	
	/* Circumstance is created when a stimulus event triggers a resulting response */

	// Set up the stimulus event between the two parties
	const auto stimulusEvent = 	ContactsStimulus::Create(sender1, receiver1);
		
	// Cause an specific response resulting in a circumstance (i.e, a S-R link)
	const auto circumstance = stimulusEvent->Cause();
	
	// S-R link is an alias for a circumstance that was produced by an event that caused a particular response
	auto& srLink = circumstance;
		
	EXPECT_TRUE(srLink->GetResponse()->GetResult().ThrowIfNone()->GetSender()->HasRelationTo(receiver1, ContactResponse::ContactRelationName));
	EXPECT_TRUE(srLink->GetResponse()->GetResult().ThrowIfNone()->GetReceiver()->HasRelationTo(sender1, ContactResponse::ContactRelationName));
}

TEST(Demos, CreateCircumstance2)
{
	/* Represent as S-R link (i.e, a circumstance) */

	// Prepare the parties that will be involved in the stimulus event
	const auto sender1 = Party::Create("sender1");
	const auto receiver1 = Party::Create("receiver1");
	
	/* Circumstance is created when a stimulus event triggers a resulting response */

	// Set up the stimulus event between the two parties
	const auto stimulusEvent = 	ContactsStimulus::Create(sender1, receiver1);
	
	// Set up the response that should result
	const auto response = ContactResponse::Create("context", stimulusEvent);

	// Use abstract version of the response
	const auto abstractResponse = std::dynamic_pointer_cast<IResponse>(response);

	// Cause an specific response resulting in a circumstance (i.e, a S-R link)
	const auto circumstance = stimulusEvent->Cause(abstractResponse);
	
	// S-R link is an alias for a circumstance that was produced by an event that caused a particular response
			
	EXPECT_TRUE(circumstance->GetResponse()->GetResult().ThrowIfNone()->GetSender()->HasRelationTo(receiver1, ContactResponse::ContactRelationName));
	EXPECT_TRUE(circumstance->GetResponse()->GetResult().ThrowIfNone()->GetReceiver()->HasRelationTo(sender1, ContactResponse::ContactRelationName));
}

TEST(Demos, Create_SRLink)
{
	const auto sender1 = Party::Create("sender1");
	const auto receiver1 = Party::Create("receiver1");
	
	const auto stimulusEvent = 	ContactsStimulus::Create(sender1, receiver1);
	
	const auto response = ContactResponse::Create("context", stimulusEvent);
	const auto abstractResponse = std::dynamic_pointer_cast<IResponse>(response);

	// Establish a link
	const SrLink srLink(stimulusEvent, abstractResponse);

	// Test it
		
	EXPECT_TRUE(srLink.GetSender()->HasRelationTo(receiver1, ContactResponse::ContactRelationName));
	EXPECT_TRUE(srLink.GetReceiver()->HasRelationTo(sender1, ContactResponse::ContactRelationName));

	EXPECT_STREQ(srLink.GetResponse()->GetContext().c_str(), response->GetContext().c_str());
}