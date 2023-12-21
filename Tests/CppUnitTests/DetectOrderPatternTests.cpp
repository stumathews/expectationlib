#include "pch.h"

#include "ConsecutiveExpectationsPattern.h"
#include "ContactCircumstance.h"
#include "ContactCircumstanceBuilder.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "Observer.h"
#include "OrderedExpectationsPattern.h"
#include "Party.h"
#include "StimuliProducesResponseExpectation.h"

using namespace ExpectationLib;

TEST(DetectOrderTests, Test_DetectOrder1)
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
	auto obs1 = observer->Observe(circumstance1); // 1) we expect 
	auto obs2 = observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs3 = observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	auto obs4 = observer->Observe(circumstance4); // 3) we expect this to occur after 1)
	auto obs5 = observer->Observe(circumstance1); // 1) we expect 
	auto obs6 = observer->Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs7 = observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	auto obs8 = observer->Observe(circumstance5); // 3) we expect this to occur after 1)

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);
	auto myExpectation4 = std::make_shared<StimuliProducesResponseExpectation>(circumstance4);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation2, myExpectation3, myExpectation4  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	auto orders = matcher1->DetectOrder();
	EXPECT_EQ(obs1->GetId(), orders[0]);
	EXPECT_EQ(obs2->GetId(), orders[1]);
	EXPECT_EQ(obs3->GetId(), orders[2]);
	EXPECT_EQ(obs5->GetId(), orders[0]);
	EXPECT_EQ(obs6->GetId(), orders[1]);
	EXPECT_EQ(obs7->GetId(), orders[2]);
}

TEST(DetectOrderTests, Test_DetectOrder2)
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
	auto obs1 = observer->Observe(circumstance1); 
	auto obs2 = observer->Observe(circumstance2); 
	auto obs3 = observer->Observe(circumstance3); 
	auto obs4 = observer->Observe(circumstance1); 
	auto obs6 = observer->Observe(circumstance2); 
	auto obs7 = observer->Observe(circumstance3); 


	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation2, myExpectation3  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	auto orders = matcher1->DetectOrder();

	EXPECT_EQ(obs1->GetId(), orders[0]);
	EXPECT_EQ(obs2->GetId(), orders[1]);
	EXPECT_EQ(obs3->GetId(), orders[2]);
}

TEST(DetectOrderTests, Test_DetectOrder3)
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
	auto obs1 = observer->Observe(circumstance1); 
	auto obs2 = observer->Observe(circumstance2); 
	auto obs3 = observer->Observe(circumstance3); 
	auto obs4 = observer->Observe(circumstance4); 
	auto obs6 = observer->Observe(circumstance1);
	auto obs7 = observer->Observe(circumstance2);
	auto obs8 = observer->Observe(circumstance3); 
	auto obs9 = observer->Observe(circumstance3);


	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation2, myExpectation3  };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	auto orders = matcher1->DetectOrder();
	EXPECT_EQ(obs1->GetId(), orders[0]);
	EXPECT_EQ(obs2->GetId(), orders[1]);
	EXPECT_EQ(obs3->GetId(), orders[2]);
}

TEST(DetectOrderTests, Test_DetectOrder4)
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
	auto obs1 = observer->Observe(circumstance2); // 1) we expect 
	auto obs2 = observer->Observe(circumstance1); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs3 = observer->Observe(circumstance2); // 3) we expect this to occur after 1)
	auto obs4 = observer->Observe(circumstance1); // 3) we expect this to occur after 1)
	auto obs5 = observer->Observe(circumstance2); // 1) we expect 
	auto obs6 = observer->Observe(circumstance1); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs7 = observer->Observe(circumstance2); // 3) we expect this to occur after 1)
	auto obs8 = observer->Observe(circumstance1); // 3) we expect this to occur after 1)

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation1, myExpectation2 };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	auto orders = matcher1->DetectOrder();
	EXPECT_EQ(obs1->GetId(), orders[0]);
	EXPECT_EQ(obs2->GetId(), orders[1]);
}

TEST(DetectOrderTests, Test_DetectOrder5)
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
	auto obs1 = observer->Observe(circumstance2); // 1) we expect 
	auto obs2 = observer->Observe(circumstance1); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs3 = observer->Observe(circumstance3); // 3) we expect this to occur after 1)
	auto obs4 = observer->Observe(circumstance2); // 3) we expect this to occur after 1)
	auto obs5 = observer->Observe(circumstance1); // 1) we expect 
	auto obs6 = observer->Observe(circumstance3); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
	auto obs7 = observer->Observe(circumstance2); // 3) we expect this to occur after 1)
	auto obs8 = observer->Observe(circumstance1); // 3) we expect this to occur after 1)
	auto obs9 = observer->Observe(circumstance3); // 3) we expect this to occur after 1)

	// Make some expectations/predictions about that circumstances should have occurred
	auto myExpectation1 = std::make_shared<StimuliProducesResponseExpectation>(circumstance2);
	auto myExpectation2 = std::make_shared<StimuliProducesResponseExpectation>(circumstance1);
	auto myExpectation3 = std::make_shared<StimuliProducesResponseExpectation>(circumstance3);

	// Define a situation where an order in which those predictions were expected to occur in
	std::vector<std::shared_ptr<IExpectation>> orderOfExpectedOutcomes = { myExpectation2, myExpectation1, myExpectation3 };

	// Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
	auto matcher1 = std::make_shared< OrderedExpectationsPattern>(orderOfExpectedOutcomes, observer->Observations);
	EXPECT_TRUE(matcher1->Match());

	auto orders = matcher1->DetectOrder();
	EXPECT_EQ(obs1->GetId(), orders[0]);
	EXPECT_EQ(obs2->GetId(), orders[1]);
	EXPECT_EQ(obs3->GetId(), orders[2]);
}