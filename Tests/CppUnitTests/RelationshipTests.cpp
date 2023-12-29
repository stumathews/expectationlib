#include "pch.h"
#include "pch.h"

#include "ContactCircumstance.h"
#include "ContactCircumstanceBuilder.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "GraphBuilder.h"
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

	std::shared_ptr<IParty> party1 = std::make_shared<Party>("party1");
	std::shared_ptr<IParty> party2 = std::make_shared<Party>("party2");
	std::shared_ptr<IParty> party3 = std::make_shared<Party>("party3");
	std::shared_ptr<IParty> party4 = std::make_shared<Party>("party4");

	// party2 -> party2
	const auto circumstance1 = ContactCircumstanceBuilder::Build(party1, party2);
	party1 = circumstance1->GetResponse()->GetSender();
	party2 = circumstance1->GetResponse()->GetReceiver();

	EXPECT_TRUE(party1->HasRelationTo(party2, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party2->HasRelationTo(party1, ContactResponse::ContactRelationName));

	EXPECT_EQ(party1->GetRelations().size(), 1);
	EXPECT_EQ(party2->GetRelations().size(), 1);

	// party2 -> party3

	const auto circumstance2 = ContactCircumstanceBuilder::Build(party2, party3);
	party2 = circumstance2->GetResponse()->GetSender();
	party1 = party2->GetRelations()[0].To;
	party3 = circumstance2->GetResponse()->GetReceiver();


	EXPECT_TRUE(party2->HasRelationTo(party3, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party3->HasRelationTo(party2, ContactResponse::ContactRelationName));

	EXPECT_EQ(party1->GetRelations().size(), 1);
	EXPECT_EQ(party2->GetRelations().size(), 2); // should have an extra relation to party 3
	EXPECT_EQ(party3->GetRelations().size(), 1);

	const auto circumstance3 =  ContactCircumstanceBuilder::Build(party1, party4);
	party1 = circumstance3->GetResponse()->GetSender();
	party4 = circumstance3->GetResponse()->GetReceiver();

	EXPECT_TRUE(party1->HasRelationTo(party4, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party4->HasRelationTo(party1, ContactResponse::ContactRelationName));

	EXPECT_EQ(party1->GetRelations().size(), 2);

	// changes to state over time:
	// t1: circumstance1  ([party1]-[party2])
	// t2: circumstance2 (party1-[party2]-[party3])
	// t3: circumstance3 ([party4]-[party1]-party2-party3)

}