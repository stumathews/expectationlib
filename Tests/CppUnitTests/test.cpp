#include "pch.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "ContextualFlowsMonitor.h"
#include "ExpectationExistsPatternMatcher.h"
#include "Observer.h"
#include "OrderedExpectedObservationsPattern.h"
#include "Party.h"
#include "SequentialExpectedObservationsPattern.h"
#include "StimuliProducesResponseExpectation.h"

#include "ExpectedTestSituation.h"

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
    auto sender = std::make_shared<Party>("receiver1");
    auto receiver = std::make_shared<Party>("receiver2");            
    auto sender2 = std::make_shared<Party>("receiver2");
    auto receiver2 = std::make_shared<Party>("receiver2");
	const std::shared_ptr<IStimulus> stimulus1 = std::make_shared<ContactsStimulus>(sender, receiver);
	const std::shared_ptr<IStimulus> stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const std::shared_ptr<IResponse> response = std::make_shared<ContactResponse>("responseA", receiver);
	const auto response2 = std::make_shared<ContactResponse>("responseB", receiver);

    EXPECT_EQ(observer->Observations.size(), 0);

	const auto observation = observer->Observe(stimulus1, response, "");
    
    EXPECT_EQ(observer->Observations.size(), 1);
    EXPECT_EQ(observation->GetResponse(), response);
    EXPECT_EQ(observation->GetStimulus(), stimulus1);

	const auto observation2 = observer->Observe(stimulus2, response2, "");
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
	observer->Observe(stimulus, expectedResponse, "");

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

	const auto observation = observer->Observe(stimulus, expectedResponse,"");
	const auto observation2 = observer->Observe(stimulus, unexpectedResponse, "");

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
	auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);

	// Multiple observations occur ...
	observer->Observe(stimulus1, response1, "");
	observer->Observe(stimulus2, response2, "");
	observer->Observe(stimulus3, response3, "");

	// Make an observational expectation
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);

	// Check if the expectation exists in observations
	const auto matcher = std::make_shared<ExpectationExistsPatternMatcher>(myExpectation1, observer->Observations);
	EXPECT_TRUE(matcher->Match());
}

TEST(ExpectationTests, Test_SequentialMatches)
{
	const auto observer = std::make_shared<Observer>();
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender1");
	auto sender3 = std::make_shared<Party>("sender1");
	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
            
    // Make observations ob some behaviors between sender and receiver
	observer->Observe(stimulus1, response1, "");
	observer->Observe(stimulus2, response2, "");
	observer->Observe(stimulus3, response3, "");

	const auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(stimulus1, response1);
	const auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(stimulus2, response2);
	const auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(stimulus3, response3);

    // Expect that the expectations were met sequentially, i.e that their was a specific sequence of expected outcomes
	std::vector<std::shared_ptr<IExpectation>> expectedOrder1 = { myExpectation1, myExpectation2, myExpectation3  };
	std::vector<std::shared_ptr<IExpectation>> expectedOrder2 = { myExpectation1,  myExpectation3, myExpectation2 };

	const auto matcher1 = std::make_shared<SequentialExpectedObservationsPattern>(expectedOrder1, observer->Observations);
	const auto matcher2 = std::make_shared<SequentialExpectedObservationsPattern>(expectedOrder2, observer->Observations);

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

TEST(ExpectationTests, Test_OrderedMatches)
{
	auto observer = std::make_shared<Observer>();
	// The observer will consume or observe circumstances (circumstantial observations)
	auto sender1 = std::make_shared<Party>("sender1");
	auto sender2 = std::make_shared<Party>("sender1");
	auto sender3 = std::make_shared<Party>("sender1");
	auto sender4 = std::make_shared<Party>("sender1");
	auto sender5 = std::make_shared<Party>("sender1");
	auto sender6 = std::make_shared<Party>("sender1");
	auto receiver1 = std::make_shared<Party>("receiver1");
	auto receiver2 = std::make_shared<Party>("receiver2");
	auto receiver3 = std::make_shared<Party>("receiver3");
	auto receiver4 = std::make_shared<Party>("receiver4");
	auto receiver5 = std::make_shared<Party>("receiver5");
	auto receiver6 = std::make_shared<Party>("receiver6");
            
	const auto stimulus1 = std::make_shared<ContactsStimulus>(sender1, receiver1);
	auto stimulus2 = std::make_shared<ContactsStimulus>(sender2, receiver2);
	const auto stimulus3 = std::make_shared<ContactsStimulus>(sender3, receiver3);
	const auto stimulus4 = std::make_shared<ContactsStimulus>(sender4, receiver4);
	const auto stimulus5 = std::make_shared<ContactsStimulus>(sender5, receiver5);
	const auto stimulus6 = std::make_shared<ContactsStimulus>(sender6, receiver6);

	const auto response1 = std::make_shared<ContactResponse>("Response1", receiver1);
	auto response2 = std::make_shared<ContactResponse>("Response2", receiver2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", receiver3);
	const auto response4 = std::make_shared<ContactResponse>("Response4", receiver4);
	const auto response5 = std::make_shared<ContactResponse>("Response5", receiver5);
	const auto response6 = std::make_shared<ContactResponse>("Response6", receiver6);

    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = std::make_shared< ContactCircumstance>(stimulus1, response1->GetContext());
    auto circumstance2 = std::make_shared< ContactCircumstance>(stimulus2, response2->GetContext());
    auto circumstance3 = std::make_shared< ContactCircumstance>(stimulus3, response3->GetContext());
    auto circumstance4 = std::make_shared< ContactCircumstance>(stimulus4, response4->GetContext());
    auto circumstance5 = std::make_shared< ContactCircumstance>(stimulus5, response5->GetContext());
    auto circumstance6 = std::make_shared< ContactCircumstance>(stimulus6, response6->GetContext());
            
	// Simulate/Observe some circumstances (outcomes)...
	observer->Observe(circumstance1,""); // 1) we expect 
	observer->Observe(circumstance2, ""); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	observer->Observe(circumstance3, ""); // 3) we expect this to occur after 1)
	observer->Observe(circumstance3, ""); // ignore dup
	observer->Observe(circumstance3, ""); // ignore dup
	observer->Observe(circumstance4, ""); // 4) we expect this to occur after 3)
	observer->Observe(circumstance5, ""); // we ignore

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	auto myExpectation4 = std::make_shared<StimuliProducesResponseExpectation>(circumstance4);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectedObservationsPattern>(orderOfExpectedOutcomes, observer->Observations);

	EXPECT_TRUE(matcher1->Match());

	orderOfExpectedOutcomes = { myExpectation1,  myExpectation3, myExpectation4 };
	EXPECT_TRUE(SequenceEqual(matcher1->MatchedExpectations, orderOfExpectedOutcomes));
	EXPECT_EQ(matcher1->UnmatchedExpectations().size(), 0);

	// negative case: Some expectations are not met

	observer = std::make_shared<Observer>();


	auto myExpectation5 = std::make_shared<StimuliProducesResponseExpectation>(circumstance5);
	auto myExpectation6 = std::make_shared<StimuliProducesResponseExpectation>(circumstance6);
	
	orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4, myExpectation5, myExpectation6 };

	observer->Observe(stimulus1, response1,""); // we expect
	observer->Observe(stimulus2, response2,""); // ignore other
	observer->Observe(stimulus3, response3,""); // we expect
	observer->Observe(stimulus3, response3,""); // ignore dup
	observer->Observe(stimulus3, response3,""); // ignore dup
	observer->Observe(stimulus4, response4,""); // we expect
	// missing expectation 5
	// missing expectation 6

	
	matcher1 = std::make_shared< OrderedExpectedObservationsPattern>(orderOfExpectedOutcomes, observer->Observations);

	// The expected observational behavior was not found
	EXPECT_FALSE(matcher1->Match());

	// We have the first 3 matched expectations correct
	orderOfExpectedOutcomes = { myExpectation1, myExpectation3, myExpectation4 };
	EXPECT_TRUE(SequenceEqual(matcher1->MatchedExpectations,  orderOfExpectedOutcomes));

	// We did not match expectations 5 and 6
	orderOfExpectedOutcomes = { myExpectation5, myExpectation6 };
	EXPECT_TRUE(SequenceEqual(matcher1->UnmatchedExpectations(), orderOfExpectedOutcomes));
}

TEST(ExpectationTests, Test_ExpectedTestSituationFlowPass)
{
	auto cloudRequester = std::make_shared<Party>("cloudRequesterId");
    auto onPremComponent = std::make_shared<Party>( "onPremComponentId");
    auto primaryNode = std::make_shared<Party>( "primaryNodeId");
    auto secondaryNode = std::make_shared<Party>("secondaryNodeId");

    std::string transactionId = "NewTxnId123";

    // Model a specific hard-coded situation as the ordered expected behavior of 4 specific parties  
	const auto flow = std::make_shared<ExpectedTestSituation>(transactionId, cloudRequester, onPremComponent, primaryNode, secondaryNode);

	const auto contactSituation1 = ContactCircumstanceBuilder::Build(cloudRequester, onPremComponent, transactionId, primaryNode);
	const auto contactSituation2 = ContactCircumstanceBuilder::Build(primaryNode, secondaryNode, transactionId);
	const auto contactSituation3 = ContactCircumstanceBuilder::Build(secondaryNode, primaryNode, transactionId);
	const auto contactSituation4 = ContactCircumstanceBuilder::Build(primaryNode, cloudRequester, transactionId);

	const auto overseer = new Observer();

    overseer->Observe(contactSituation1,""); // cloudRequester -> onPremComponent
    overseer->Observe(contactSituation2,""); // primary -> secondary
    overseer->Observe(contactSituation3,""); // secondary -> primary
    overseer->Observe(contactSituation4, ""); // primary -> cloudRequester

    EXPECT_TRUE(flow->Match(overseer->Observations));
    EXPECT_EQ(flow->GetUnmatchedExpectations().size(), 0);
    EXPECT_EQ(flow->GetMatchedExpectations().size(), 4);
    EXPECT_GT(flow->ToString().length(), 0);
}


TEST(ExpectationTests, Test_ExpectedTestSituationFlowFail)
{
	const auto party1 = std::make_shared<Party>("party1");
	const auto party2 = std::make_shared<Party>( "party2");
	const auto party3 = std::make_shared<Party>( "party3");
	const auto party4 = std::make_shared<Party>("party4");

	std::string transactionId = "NewTxnId123";
	const auto flow = new ExpectedTestSituation(transactionId, party1, party2, party3, party4);

	const auto contactSituation1 = ContactCircumstanceBuilder::Build(party1, party2, transactionId, party3);
	// auto contactSituation2 = ContactCircumstanceBuilder.Build(party3, party4, transactionId);
	// auto contactSituation3 = ContactCircumstanceBuilder.Build(party4, party3, transactionId);
	const auto contactSituation4 = ContactCircumstanceBuilder::Build(party3, party1, transactionId);

	const auto overseer = new Observer();

	overseer->Observe(contactSituation1, ""); // party1 -> party2 (expectation order matched)
	// overseer.Observe(contactSituation2); // party3 -> party4 (expectation not found, tf not met)
	// overseer.Observe(contactSituation3); // party4 -> party3 (expectation not found, tf not met)
	overseer->Observe(contactSituation4, ""); // party3 -> party1 (expectation out of order (needs to occur after exepctation3 but occurs after expectation1))

	EXPECT_FALSE(flow->Match(overseer->Observations));
	EXPECT_EQ(flow->GetUnmatchedExpectations().size(), 3); // three expectations were either not present (#2,#3) or out of order (#4 - must happen after 3 and doesn't)
	EXPECT_EQ(flow->GetMatchedExpectations().size(), 1); // only expectation #1 happens in order (and is present)
	EXPECT_GT(flow->ToString().length(), 0);
}

std::shared_ptr<ContactCircumstance> MakeContactCircumstance(std::string senderId, std::string receiverId, std::string contextualResponseId)
        {
            auto testSender = std::make_shared<Party>(senderId);
            auto testReceiver = std::make_shared<Party>(receiverId);
            auto stimuli = std::make_shared<ContactsStimulus>(testSender, testReceiver);
            return std::make_shared< ContactCircumstance>(stimuli, contextualResponseId, testReceiver);
        }

TEST(ExpectationTests, Test_ContextualFlowsMonitor)
{
	const std::string transactionId = "NewTxnId123";
    auto overseer = ContextualFlowsMonitor::Get()->GetOverseer(transactionId);

    const std::string testSenderId = "testSenderId";
    const std::string testReceiverId = "testReceiverId";

	const auto circumstance1 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
	const auto circumstance2 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
	const auto circumstance3 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
    
    overseer->Observe(circumstance1, "");
    overseer->Observe(circumstance2, "");

    ContextualFlowsMonitor::Get()->RemoveOverseer(transactionId);

    overseer = ContextualFlowsMonitor::Get()->GetOverseer(transactionId);
    EXPECT_EQ(overseer->Observations.size(), 0);
    ContextualFlowsMonitor::Get()->RemoveOverseer(transactionId);
    
    overseer = ContextualFlowsMonitor::Get()->GetOverseer(transactionId);
    overseer->Observe(circumstance3, "");
    EXPECT_EQ(overseer->Observations.size(), 1);
    
    ContextualFlowsMonitor::Get()->RemoveOverseer(transactionId);
}

