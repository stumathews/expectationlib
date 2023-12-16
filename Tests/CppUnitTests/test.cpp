#include "pch.h"

#include "ConsecutiveExpectationsPattern.h"
#include "ContactCircumstance.h"
#include "ContactCircumstanceBuilder.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "ContextualFlowsMonitor.h"
#include "ExpectationExistsPattern.h"
#include "Observer.h"
#include "OrderedExpectationsPattern.h"
#include "Party.h"
#include "ExactExpectationsPattern.h"
#include "StimuliProducesResponseExpectation.h"
#include "ExpectedTestSituation.h"
#include "RepeatsExpectationsPattern.h"
#include "RepeatsExpectationPattern.h"

using namespace ExpectationLib;

TEST(ExpectationTests, Test_Sender)
{
    auto senderId = "senderId";
    const auto sender = std::make_shared<Party>(senderId);

	EXPECT_EQ(sender->GetId(), senderId);
}

TEST(ExpectationTests, Test_Receiver)
{
    auto receiverId = "receiverId";
    const auto receiver = std::make_shared<Party>(receiverId);
    EXPECT_EQ(receiver->GetId(), receiverId);
}

TEST(ExpectationTests, Test_CustomStimulus)
{
    auto sender = std::make_shared<Party>("sender1");
    auto receiver = std::make_shared<Party>("receiver");

    const auto stimulus = std::make_shared<ContactsStimulus>(sender, receiver);

    EXPECT_EQ(stimulus->GetSender(), sender);
    EXPECT_EQ(stimulus->GetReceiver(), receiver);
    EXPECT_EQ(stimulus->GetId(), ContactsStimulus::CreateId(sender, receiver));
}

TEST(ExpectationTests, Test_Overseer)
{
	const auto observer = std::make_shared<Observer>();
    auto sender = std::make_shared<Party>("sender1");	        
    auto sender2 = std::make_shared<Party>("sender2");
    auto receiver = std::make_shared<Party>("receiver1");    
    auto receiver2 = std::make_shared<Party>("receiver2");

	const std::shared_ptr<IStimulus> stimulus1 = std::make_shared<ContactsStimulus>(sender, receiver);
	const std::shared_ptr<IStimulus> stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);

	const std::shared_ptr<IResponse> response = std::make_shared<ContactResponse>("responseA", receiver);

	const auto response2 = std::make_shared<ContactResponse>("responseB", receiver);

    EXPECT_EQ(observer->Observations.size(), 0);

	const auto observation = observer->Observe(stimulus1, response);
    
    EXPECT_EQ(observer->Observations.size(), 1);
    EXPECT_EQ(observation->GetResponse(), response);
    EXPECT_EQ(observation->GetStimulus(), stimulus1);

	const auto observation2 = observer->Observe(stimulus2, response2);
    EXPECT_EQ(observer->Observations.size(), 2);
    EXPECT_EQ(observation2->GetResponse(), response2);
    EXPECT_EQ(observation2->GetStimulus(), stimulus2);
}

TEST(ExpectationTests, Test_Expectation)
{
	const auto observer = std::make_shared<Observer>();
	auto sender = std::make_shared<Party>("Stuart");
	auto receiver = std::make_shared<Party>("Jenny");

	// create a certain kind of stimulus Mechanosensory (Contact) from sender -> receiver
	std::shared_ptr<IStimulus> stimulus = std::make_shared<ContactsStimulus>(sender, receiver);

	std::shared_ptr<IResponse> expectedResponse = std::make_shared<ContactResponse>("aResponse", receiver);

	// Create an expectation
	const auto myExpectation = std::make_shared<StimuliProducesResponseExpectation>(stimulus, expectedResponse);

	// perform a stimulus .. sender contacts receiver and a contact response is produced

	// make sure the observer observes it
	observer->Observe(stimulus, expectedResponse);

	// Ensure the expectation is met by observations

	EXPECT_EQ(myExpectation->GetStimulus(), stimulus);
	EXPECT_EQ(myExpectation->GetStimulus()->GetSender(), stimulus->GetSender());
	EXPECT_EQ(myExpectation->GetStimulus()->GetReceiver(), stimulus->GetReceiver());
	EXPECT_EQ(myExpectation->GetId(), StimuliProducesResponseExpectation::CreateId(stimulus, expectedResponse));
}

TEST(ExpectationTests, Test_ExpectationNegative)
{
	const auto observer = std::make_shared<Observer>();
	auto sender = std::make_shared<Party>("Stuart");
	auto receiver = std::make_shared<Party>("Jenny");

	// create a certain kind of stimulus Mechanosensory (Contact) from sender -> receiver
	const std::shared_ptr<IStimulus> stimulus = std::make_shared<ContactsStimulus>(sender, receiver);

	const auto expectedResponse = std::make_shared<ContactResponse>("aResponse", receiver);
	const auto unexpectedResponse = std::make_shared<ContactResponse>("bResponse", receiver);

	// Create an expectation
	const auto myExpectation = std::make_shared<StimuliProducesResponseExpectation>(stimulus, expectedResponse);

	const auto observation = observer->Observe(stimulus, expectedResponse);
	const auto observation2 = observer->Observe(stimulus, unexpectedResponse);

	EXPECT_TRUE(myExpectation->Match(observation));
	EXPECT_FALSE(myExpectation->Match(observation2));

}

TEST(ExpectationTests, Test_ExpectationExistsPatternMatcher)
{
	const auto observer = std::make_shared<Observer>();

	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender1");
	auto sender3 = std::make_shared<Party>("sender1");
	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");

	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);

	// Multiple observations occur ...
	observer->Observe(stimulus1, response1);
	observer->Observe(stimulus2, response2);
	observer->Observe(stimulus3, response3);

	// Make an observational expectation
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(stimulus1, response2);

	// Check if the expectation exists in observations
	const auto matcher1 = std::make_shared<ExpectationExistsPattern>(myExpectation1, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	const auto matcher2 = std::make_shared<ExpectationExistsPattern>(myExpectation2, observer->Observations);
	EXPECT_FALSE(matcher2->Match());
}

TEST(ExpectationTests, Test_ExactExpectations)
{
	const auto observer = std::make_shared<Observer>();

	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");

	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
            
    // Make observations ob some behaviors between sender and receiver
	observer->Observe(stimulus1, response1);
	observer->Observe(stimulus2, response2);
	observer->Observe(stimulus3, response3);

	const auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus1, response1);
	const auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);
	const auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(stimulus3, response3);

    // Expect that the expectations were met sequentially, i.e that their was a specific sequence of expected outcomes
	std::vector<std::shared_ptr<IExpectation>> expectedOrder1 = { myExpectation1, myExpectation2, myExpectation3  };
	std::vector<std::shared_ptr<IExpectation>> expectedOrder2 = { myExpectation1,  myExpectation3, myExpectation2 };

	const auto matcher1 = std::make_shared<ExactExpectationsPattern>(expectedOrder1, observer->Observations);
	const auto matcher2 = std::make_shared<ExactExpectationsPattern>(expectedOrder2, observer->Observations);

    EXPECT_TRUE(matcher1->Match());
    EXPECT_FALSE(matcher2->Match());
}

template <typename T>
bool SequenceEqual(std::vector<T> one, std::vector<T> two)
{
	for (auto i = 0; i < one.size();i++)
	{
		if(one[i] != two[i]) return false;
	}
	return true;
}

TEST(ExpectationTests, Test_OrderedExpectations)
{
	auto observer = std::make_shared<Observer>();

	// The observer will consume or observe circumstances (circumstantial observations)
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");
	auto sender4 = std::make_shared<Party>("sender4");
	auto sender5 = std::make_shared<Party>("sender5");
	auto sender6 = std::make_shared<Party>("sender6");

	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
	auto receiver4 = std::make_shared<Party>("receiver4");
	auto receiver5 = std::make_shared<Party>("receiver5");
	auto receiver6 = std::make_shared<Party>("receiver6");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);
	const auto stimulus4 = std::make_shared<ContactsStimulus>(sender4, receiver4);
	const auto stimulus5 = std::make_shared<ContactsStimulus>(sender5, receiver5);
	const auto stimulus6 = std::make_shared<ContactsStimulus>(sender6, receiver6);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
	const auto response4 = std::make_shared<ContactResponse>("Response4", receiver4);
	const auto response5 = std::make_shared<ContactResponse>("Response5", receiver5);
	const auto response6 = std::make_shared<ContactResponse>("Response6", receiver6);

    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = std::make_shared<ContactCircumstance>(stimulus1, response1->GetContext());
    auto circumstance2 = std::make_shared<ContactCircumstance>(stimulus2, response2->GetContext());
    auto circumstance3 = std::make_shared<ContactCircumstance>(stimulus3, response3->GetContext());
    auto circumstance4 = std::make_shared<ContactCircumstance>(stimulus4, response4->GetContext());
    auto circumstance5 = std::make_shared<ContactCircumstance>(stimulus5, response5->GetContext());
    auto circumstance6 = std::make_shared<ContactCircumstance>(stimulus6, response6->GetContext());
            
	// Simulate/Observe some circumstances (outcomes)...
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5); // we ignore

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	auto myExpectation4 = std::make_shared<StimuliProducesResponseExpectation>(circumstance4);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());	
	EXPECT_TRUE(SequenceEqual(matcher1->MatchedExpectations, orderOfExpectedOutcomes));
	EXPECT_EQ(matcher1->UnmatchedExpectations().size(), 0);

	// negative case: Some expectations are not met

	observer = std::make_shared<Observer>();

	auto myExpectation5 = std::make_shared<StimuliProducesResponseExpectation>(circumstance5);
	auto myExpectation6 = std::make_shared<StimuliProducesResponseExpectation>(circumstance6);
	
	orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4, myExpectation5, myExpectation6 };

	observer->Observe(circumstance1); // we expect
	observer->Observe(circumstance2); // ignore other
	observer->Observe(circumstance3); // we expect
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // we expect
	// missing expectation 5
	// missing expectation 6
		
	matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);

	// The expected observational behavior was not found
	EXPECT_FALSE(matcher1->Match());

	// We have the first 3 matched expectations correct
	orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4 };
	EXPECT_TRUE(SequenceEqual(matcher1->MatchedExpectations,  orderOfExpectedOutcomes));

	// We did not match expectations 5 and 6
	std::vector<std::shared_ptr<IExpectation>> orderOfUnmatchedExpectations = { myExpectation5, myExpectation6 };
	EXPECT_TRUE(SequenceEqual(matcher1->UnmatchedExpectations(), orderOfUnmatchedExpectations));
}

TEST(ExpectationTests, Test_ExpectedTestSituationFlowPass)
{
	auto party1 = std::make_shared<Party>("party1");
    auto party2 = std::make_shared<Party>( "party2");
    auto party3 = std::make_shared<Party>( "party3");
    auto party4 = std::make_shared<Party>("party4");

    std::string transactionId = "SharedContextString";

    // Model a specific hard-coded situation as the ordered expected behavior of 4 specific parties  
	const auto situation = std::make_shared<ExpectedTestSituation>(transactionId, party1, party2, party3, party4);

	const auto contactSituation1 = ContactCircumstanceBuilder::Build(party1, party2, transactionId, party3);
	const auto contactSituation2 = ContactCircumstanceBuilder::Build(party3, party4, transactionId);
	const auto contactSituation3 = ContactCircumstanceBuilder::Build(party4, party3, transactionId);
	const auto contactSituation4 = ContactCircumstanceBuilder::Build(party3, party1, transactionId);

	const auto overseer = std::make_shared<Observer>();

    overseer->Observe(contactSituation1); // party1 -> party2
    overseer->Observe(contactSituation2); // party3 -> party4
    overseer->Observe(contactSituation3); // party4 -> party3
    overseer->Observe(contactSituation4); // party3 -> party1

    EXPECT_TRUE(situation->Match(overseer->Observations));
    EXPECT_EQ(situation->GetUnmatchedExpectations().size(), 0);
    EXPECT_EQ(situation->GetMatchedExpectations().size(), 4);
    EXPECT_GT(situation->ToString().length(), 0);
}


TEST(ExpectationTests, Test_ExpectedTestSituationFlowFail)
{
	const auto party1 = std::make_shared<Party>("party1");
	const auto party2 = std::make_shared<Party>( "party2");
	const auto party3 = std::make_shared<Party>( "party3");
	const auto party4 = std::make_shared<Party>("party4");

	std::string transactionId = "SharedContextString";
	const auto flow = std::make_shared<ExpectedTestSituation>(transactionId, party1, party2, party3, party4);

	const auto contactSituation1 = ContactCircumstanceBuilder::Build(party1, party2, transactionId, party3);
	// auto contactSituation2 = ContactCircumstanceBuilder.Build(party3, party4, transactionId);
	// auto contactSituation3 = ContactCircumstanceBuilder.Build(party4, party3, transactionId);
	const auto contactSituation4 = ContactCircumstanceBuilder::Build(party3, party1, transactionId);

	const auto overseer = std::make_shared<Observer>();

	overseer->Observe(contactSituation1); // party1 -> party2 (expectation order matched)
	// overseer.Observe(contactSituation2); // party3 -> party4 (expectation not found, tf not met)
	// overseer.Observe(contactSituation3); // party4 -> party3 (expectation not found, tf not met)
	overseer->Observe(contactSituation4); // party3 -> party1 (expectation out of order (needs to occur after exepctation3 but occurs after expectation1))

	EXPECT_FALSE(flow->Match(overseer->Observations));
	EXPECT_EQ(flow->GetUnmatchedExpectations().size(), 3); // three expectations were either not present (#2,#3) or out of order (#4 - must happen after 3 and doesn't)
	EXPECT_EQ(flow->GetMatchedExpectations().size(), 1); // only expectation #1 happens in order (and is present)
	EXPECT_GT(flow->ToString().length(), 0);
}

std::shared_ptr<ContactCircumstance> MakeContactCircumstance(const std::string& senderId, const std::string& receiverId, const std::string& contextualResponseId)
{
    auto testSender = std::make_shared<Party>(senderId);
    auto testReceiver = std::make_shared<Party>(receiverId);
    auto stimuli = std::make_shared<ContactsStimulus>(testSender, testReceiver);
    return std::make_shared< ContactCircumstance>(stimuli, contextualResponseId, testReceiver);
}

TEST(ExpectationTests, Test_ContextualFlowsMonitor)
{
	const std::string sharedContextString = "SharedContextString";
    auto overseer = ContextualFlowsMonitor::Get()->GetOverseer(sharedContextString);

    const std::string testSenderId = "testSenderId";
    const std::string testReceiverId = "testReceiverId";

	const auto circumstance1 = MakeContactCircumstance(testSenderId, testReceiverId, sharedContextString);
	const auto circumstance2 = MakeContactCircumstance(testSenderId, testReceiverId, sharedContextString);
	const auto circumstance3 = MakeContactCircumstance(testSenderId, testReceiverId, sharedContextString);
    
    overseer->Observe(circumstance1);
    overseer->Observe(circumstance2);

    ContextualFlowsMonitor::Get()->RemoveOverseer(sharedContextString);

	// Creates a new one as the previous one was removed
    overseer = ContextualFlowsMonitor::Get()->GetOverseer(sharedContextString);
    EXPECT_EQ(overseer->Observations.size(), 0);
    ContextualFlowsMonitor::Get()->RemoveOverseer(sharedContextString);

	// Creates a new one as the previous one was removed
    overseer = ContextualFlowsMonitor::Get()->GetOverseer(sharedContextString);
    overseer->Observe(circumstance3);
    EXPECT_EQ(overseer->Observations.size(), 1);
    
    ContextualFlowsMonitor::Get()->RemoveOverseer(sharedContextString);
}


TEST(ExpectationTests, Test_RepeatedExpectation)
{
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");
	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
		
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);	
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);	
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);	
	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);

	auto observer = std::make_shared<Observer>();

	const auto circumstance1 = std::make_shared<ContactCircumstance>(stimulus1, response1->GetContext());
	const auto circumstance2 = std::make_shared<ContactCircumstance>(stimulus2, response2->GetContext());
	const auto circumstance3 = std::make_shared<ContactCircumstance>(stimulus3, response3->GetContext());

	observer->Observe(circumstance1);
	observer->Observe(circumstance3);
	observer->Observe(circumstance1);
	observer->Observe(circumstance3);
	observer->Observe(circumstance2);
	observer->Observe(circumstance2);
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	observer->Observe(circumstance2);
	observer->Observe(circumstance1);
	observer->Observe(circumstance3);

	auto repeatExpectation = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);

	// Expect the 2nd circumstance to repeat 3 times
	const auto repeatedPattern = std::make_shared<RepeatsExpectationPattern>(3, RepeatsExpectationPattern::Pattern::Ordered, repeatExpectation, observer->Observations);
	EXPECT_TRUE(repeatedPattern->Match());

	// Do not expect the 2nd circumstance to repeat 4 times
	const auto repeatedPattern2 = std::make_shared<RepeatsExpectationPattern>(4, RepeatsExpectationPattern::Pattern::Ordered, repeatExpectation, observer->Observations);
	EXPECT_FALSE(repeatedPattern2->Match());

	// Expect the 1st circumstance  to repeat 3 times
	repeatExpectation = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	const auto repeatedPattern3 = std::make_shared<RepeatsExpectationPattern>(3, RepeatsExpectationPattern::Pattern::Ordered, repeatExpectation, observer->Observations);
	EXPECT_TRUE(repeatedPattern3->Match());

	// Expect the 3rd circumstance  to repeat 5 times
	repeatExpectation = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	const auto repeatedPattern4 = std::make_shared<RepeatsExpectationPattern>(5, RepeatsExpectationPattern::Pattern::Ordered, repeatExpectation, observer->Observations);
	EXPECT_TRUE(repeatedPattern4->Match());

	// Expect the 2nd circumstance to repear sequentially 6 times
	observer = std::make_shared<Observer>();
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	observer->Observe(circumstance3);
	repeatExpectation = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	const auto repeatedPattern5 = std::make_shared<RepeatsExpectationPattern>(6, RepeatsExpectationPattern::Pattern::Exact, repeatExpectation, observer->Observations);
	EXPECT_TRUE(repeatedPattern5->Match());

}

TEST(ExpectationTests, ConsecutiveExpectations)
{
	auto observer = std::make_shared<Observer>();

	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");

	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
            
    // Make observations ob some behaviors between sender and receiver
	observer->Observe(stimulus1, response1); // expect
	observer->Observe(stimulus2, response2); // expect
	observer->Observe(stimulus3, response3); // expect

	const auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus1, response1);
	const auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);
	const auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(stimulus3, response3);
	
	std::vector<std::shared_ptr<IExpectation>> expectedOrder1 = { myExpectation1, myExpectation2, myExpectation3  };

	const auto matcher1 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher1->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *

	const auto matcher2 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher2->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *
	observer->Observe(stimulus1, response1); // ignore

	const auto matcher3 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher3->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus3, response3); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *
	observer->Observe(stimulus1, response1); // ignore

	const auto matcher4 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher4->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore

	const auto matcher5 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher5->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore

	const auto matcher6 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_FALSE(matcher6->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *

	const auto matcher7 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_TRUE(matcher7->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore

	const auto matcher8 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_FALSE(matcher8->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(stimulus3, response3);  // ignore
	observer->Observe(stimulus3, response3);  // ignore
	observer->Observe(stimulus3, response3);  // ignore
	observer->Observe(stimulus3, response3);  //  ignore
	observer->Observe(stimulus3, response3);  // ignore

	const auto matcher9 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

    EXPECT_FALSE(matcher9->Match());

}

TEST(ExpectationTests, RepeatedConsecutiveExpectationsPattern)
{
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");

	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
	
	const auto circumstance1 = ContactCircumstanceBuilder::Build(sender1, receiver1, response1->Context);
	const auto circumstance2 = ContactCircumstanceBuilder::Build(sender2, receiver2, response1->Context);
	const auto circumstance3 = ContactCircumstanceBuilder::Build(sender3, receiver3, response1->Context);
		
	const auto observer = std::make_shared<Observer>();

	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *
	observer->Observe(stimulus1, response1); // ignore
	observer->Observe(stimulus2, response2); // ignore
	observer->Observe(stimulus1, response1); // expect *
	observer->Observe(stimulus2, response2); // expect *
	observer->Observe(stimulus3, response3); // expect *

	const auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus1, response1);
	const auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);
	const auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(stimulus3, response3);

	const std::vector<std::shared_ptr<IExpectation>> expectedOrder1 = { myExpectation1, myExpectation2, myExpectation3  };

	const auto matcher1 = std::make_shared<ConsecutiveExpectationsPattern>(expectedOrder1, observer->Observations);

	auto repeatMatcher1 = RepeatsExpectationsPattern(matcher1, 3);
	EXPECT_TRUE(repeatMatcher1.Match());

	/* Singular-observation:
	 * -------------------------
	 * StimuliProducesResponse
	 * Repeats Expectation
	 *
	 * Multiple observations:
	 * -----------------------
	 *
	 * Consecutive Expectations  ..123..
	 * Ordered Expectations      1..2...3
	 * Exact Expectations        123
	 *
	 * Groups of Expectations
	 * -----------------------
	 *  ...123...123...123       (3 groups of consecutive expectations)
	 *	...1..2...3...1...2.3   ( 2 groups of ordered expectations)
	 */
}


TEST(ExpectationTests, RepeatedOrderedExpectationsPattern)
{
	auto observer = std::make_shared<Observer>();

	// The observer will consume or observe circumstances (circumstantial observations)
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender2");
	auto sender3 = std::make_shared<Party>("sender3");
	auto sender4 = std::make_shared<Party>("sender4");
	auto sender5 = std::make_shared<Party>("sender5");
	auto sender6 = std::make_shared<Party>("sender6");

	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
	auto receiver4 = std::make_shared<Party>("receiver4");
	auto receiver5 = std::make_shared<Party>("receiver5");
	auto receiver6 = std::make_shared<Party>("receiver6");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	const auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);
	const auto stimulus4 = std::make_shared<ContactsStimulus>(sender4, receiver4);
	const auto stimulus5 = std::make_shared<ContactsStimulus>(sender5, receiver5);
	const auto stimulus6 = std::make_shared<ContactsStimulus>(sender6, receiver6);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
	const auto response4 = std::make_shared<ContactResponse>("Response4", receiver4);
	const auto response5 = std::make_shared<ContactResponse>("Response5", receiver5);
	const auto response6 = std::make_shared<ContactResponse>("Response6", receiver6);

    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = std::make_shared<ContactCircumstance>(stimulus1, response1->GetContext());
    auto circumstance2 = std::make_shared<ContactCircumstance>(stimulus2, response2->GetContext());
    auto circumstance3 = std::make_shared<ContactCircumstance>(stimulus3, response3->GetContext());
    auto circumstance4 = std::make_shared<ContactCircumstance>(stimulus4, response4->GetContext());
    auto circumstance5 = std::make_shared<ContactCircumstance>(stimulus5, response5->GetContext());
    auto circumstance6 = std::make_shared<ContactCircumstance>(stimulus6, response6->GetContext());
            
	// Simulate/Observe some circumstances (outcomes)...
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5); // we ignore
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5); // we ignore
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5); // we ignore

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	auto myExpectation4 = std::make_shared<StimuliProducesResponseExpectation>(circumstance4);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared<OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	auto matcher2 = std::make_shared<RepeatsExpectationsPattern>(matcher1, 3);
	EXPECT_TRUE(matcher2->Match());

	observer = std::make_shared<Observer>();
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance1); // 1) we expect 
	observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance3); // ignore dup
	observer->Observe(circumstance4); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5); // we ignore
	auto matcher3 = std::make_shared<OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	auto matcher4 = std::make_shared<RepeatsExpectationsPattern>(matcher3, 1);

	EXPECT_TRUE(matcher4->Match());
}