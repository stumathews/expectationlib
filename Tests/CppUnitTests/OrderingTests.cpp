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

    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = std::make_shared<ContactCircumstance>(stimulus1, response1->GetContext());
    auto circumstance2 = std::make_shared<ContactCircumstance>(stimulus2, response2->GetContext());
    auto circumstance3 = std::make_shared<ContactCircumstance>(stimulus3, response3->GetContext());
    auto circumstance4 = std::make_shared<ContactCircumstance>(stimulus4, response4->GetContext());
    auto circumstance5 = std::make_shared<ContactCircumstance>(stimulus5, response5->GetContext());
    auto circumstance6 = std::make_shared<ContactCircumstance>(stimulus6, response6->GetContext());

	auto obs1 = observer->Observe(circumstance3); 
	auto obs2 = observer->Observe(circumstance2); 
	auto obs3 = observer->Observe(circumstance1); 
	auto obs4 = observer->Observe(circumstance3); 
	auto obs5 = observer->Observe(circumstance2); 
	auto obs6 = observer->Observe(circumstance1); 

	Ordering ordering(observer->Observations);
	auto orderedTree = ordering.BuildOrderedTree();
	auto index0 = orderedTree.Root;
	auto index1 = orderedTree.Root->Children[0];
	auto index2 = orderedTree.Root->Children[1];
	auto index3 = index1->Children[0];
	auto index4 = index1->Children[1];
	auto index5 = index2->Children[0];
	auto index6 = index2->Children[1];
	auto index7 = index4->Children[0];
	auto index8 = index4->Children[1];
	auto index9 = index6->Children[0];
	
	EXPECT_EQ(index0->Item, obs1->GetId());                             
	EXPECT_EQ(index1->Item, obs2->GetId()); 
	EXPECT_EQ(index2->Item, obs3->GetId());
	EXPECT_EQ(index3->Item, obs3->GetId());
	EXPECT_EQ(index4->Item, obs4->GetId());
	EXPECT_EQ(index5->Item, obs4->GetId());
	EXPECT_EQ(index6->Item, obs5->GetId());
	EXPECT_EQ(index7->Item, obs5->GetId());
	EXPECT_EQ(index8->Item, obs3->GetId());
	EXPECT_EQ(index9->Item, obs3->GetId());	
}
