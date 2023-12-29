#include "pch.h"
#include "pch.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "Observer.h"
#include "Ordering.h"
#include "Party.h"
#include "StimuliProducesResponseExpectation.h"

using namespace ExpectationLib;

TEST(RelationshipTests, RelationIsSet)
{

	const auto observer = std::make_shared<Observer>();
	auto sender = std::make_shared<Party>("Stuart");
	auto receiver = std::make_shared<Party>("Jenny");

	// create a certain kind of stimulus Mechanosensory (Contact) from sender -> receiver
	const std::shared_ptr<IStimulus> stimulus = std::make_shared<ContactsStimulus>(sender, receiver); // should this modify the sender/receiver to manipulate the effect this had on its state?
	const auto circumstance = stimulus->Trigger();

	// Perform a stimulus .. sender contacts receiver and a contact response is produced
	// make sure the observer observes it: Create a stimulus that produces a response when it is observed
	observer->Observe(circumstance);

	EXPECT_EQ(sender->GetRelations().size(), 0); // expect no changes to original stimulus
	EXPECT_EQ(receiver->GetRelations().size(), 0); // expect no changes to original stimulus

	EXPECT_EQ(circumstance->GetResponse()->GetSender()->GetRelations().size(), 1);
	EXPECT_EQ(circumstance->GetResponse()->GetReceiver()->GetRelations().size(), 1);

	EXPECT_EQ(circumstance->GetResponse()->GetReceiver()->GetRelations()[0].Name, ContactResponse::ContactRelationName);
	EXPECT_EQ(circumstance->GetResponse()->GetReceiver()->GetRelations()[0].To, sender);
	EXPECT_EQ(circumstance->GetResponse()->GetSender()->GetRelations()[0].Name, ContactResponse::ContactRelationName);
	EXPECT_EQ(circumstance->GetResponse()->GetSender()->GetRelations()[0].To, receiver);

	EXPECT_TRUE(circumstance->GetResponse()->GetSender()->HasRelationTo(receiver, ContactResponse::ContactRelationName));
	EXPECT_TRUE(circumstance->GetResponse()->GetReceiver()->HasRelationTo(sender, ContactResponse::ContactRelationName));
	
}

TEST(RelationshipTests, BuildRelationships)
{
	const auto observer = std::make_shared<Observer>();

	auto party1 = std::make_shared<Party>("party1");
	auto party2 = std::make_shared<Party>("party2");

	const auto stimulus = std::make_shared<ContactsStimulus>(party1, party2);

	// this modifies the party1 and party2 - is this a good thing?
	stimulus->Trigger();

	const auto circumstance = stimulus->GetCircumstance();

	observer->Observe(circumstance);

}