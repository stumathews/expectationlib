﻿#include "pch.h"

#include <gtest/gtest.h>

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

	const std::shared_ptr<IResponse> response1 = std::make_shared<ContactResponse>("Response1", stimulus1);
	const std::shared_ptr<IResponse> response2 = std::make_shared<ContactResponse>("Response2", stimulus2);
	const std::shared_ptr<IResponse> response3 = std::make_shared<ContactResponse>("Response3", stimulus3);
	const std::shared_ptr<IResponse> response4 = std::make_shared<ContactResponse>("Response4", stimulus4);
	const std::shared_ptr<IResponse> response5 = std::make_shared<ContactResponse>("Response5", stimulus5);
	const std::shared_ptr<IResponse> response6 = std::make_shared<ContactResponse>("Response6", stimulus6);


    // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
    auto circumstance1 = stimulus1->Cause(response1);
    auto circumstance2 = stimulus2->Cause(response2);
    auto circumstance3 = stimulus3->Cause(response3);
    auto circumstance4 = stimulus4->Cause(response4);
    auto circumstance5 = stimulus5->Cause(response5);
    auto circumstance6 = stimulus6->Cause(response6);

	auto obs1 = observer->Observe(circumstance3); 
	auto obs2 = observer->Observe(circumstance2); 
	auto obs3 = observer->Observe(circumstance1); 
	auto obs4 = observer->Observe(circumstance3); 
	auto obs5 = observer->Observe(circumstance2); 
	auto obs6 = observer->Observe(circumstance1); 

	Ordering ordering(observer->Observations);
	auto orderedTree = ordering.BuildOrderedTree();
}
