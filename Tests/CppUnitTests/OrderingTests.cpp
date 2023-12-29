#include "pch.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "Observer.h"
#include "Ordering.h"
#include "Party.h"

using namespace ExpectationLib;

TEST(OrderingTests, Test1)
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

	const auto response1 = std::make_shared<ContactResponse>("Response1", stimulus1);
	const auto response2 = std::make_shared<ContactResponse>("Response2", stimulus2);
	const auto response3 = std::make_shared<ContactResponse>("Response3", stimulus3);
	const auto response4 = std::make_shared<ContactResponse>("Response4", stimulus4);
	const auto response5 = std::make_shared<ContactResponse>("Response5", stimulus5);
	const auto response6 = std::make_shared<ContactResponse>("Response6", stimulus6);

	stimulus1->Trigger(response1);
	stimulus2->Trigger(response2);
	stimulus3->Trigger(response3);
	stimulus4->Trigger(response4);
	stimulus5->Trigger(response5);
	stimulus6->Trigger(response6);

    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = std::make_shared<ContactCircumstance>(stimulus1);
    auto circumstance2 = std::make_shared<ContactCircumstance>(stimulus2);
    auto circumstance3 = std::make_shared<ContactCircumstance>(stimulus3);
    auto circumstance4 = std::make_shared<ContactCircumstance>(stimulus4);
    auto circumstance5 = std::make_shared<ContactCircumstance>(stimulus5);
    auto circumstance6 = std::make_shared<ContactCircumstance>(stimulus6);

	auto obs1 = observer->Observe(circumstance3); 
	auto obs2 = observer->Observe(circumstance2); 
	auto obs3 = observer->Observe(circumstance1); 
	auto obs4 = observer->Observe(circumstance3); 
	auto obs5 = observer->Observe(circumstance2); 
	auto obs6 = observer->Observe(circumstance1); 

	Ordering ordering(observer->Observations);
	auto orderedTree = ordering.BuildOrderedTree();
}
