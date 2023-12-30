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
	EXPECT_EQ(circumstance->GetResponse()->GetReceiver()->GetRelations()[0].To->GetId(), sender->GetId());
	EXPECT_EQ(circumstance->GetResponse()->GetSender()->GetRelations()[0].Name, ContactResponse::ContactRelationName);
	EXPECT_EQ(circumstance->GetResponse()->GetSender()->GetRelations()[0].To->GetId(), receiver->GetId());

	EXPECT_TRUE(circumstance->GetResponse()->GetSender()->HasRelationTo(receiver, ContactResponse::ContactRelationName));
	EXPECT_TRUE(circumstance->GetResponse()->GetReceiver()->HasRelationTo(sender, ContactResponse::ContactRelationName));
	
}

TEST(RelationshipTests, BuildRelationships)
{
	const std::shared_ptr<IParty> party1 = std::make_shared<Party>("party1");
	const std::shared_ptr<IParty> party2 = std::make_shared<Party>("party2");
	const std::shared_ptr<IParty> party3 = std::make_shared<Party>("party3");
	const std::shared_ptr<IParty> party4 = std::make_shared<Party>("party4");

	// party1 -> party2
	const auto circumstance1 = ContactCircumstanceBuilder::Build(party1, party2);
	auto party1c1 = circumstance1->GetResponse()->GetSender();
	auto party2c1 = circumstance1->GetResponse()->GetReceiver();

	EXPECT_TRUE(party1c1->HasRelationTo(party2c1, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party2c1->HasRelationTo(party1c1, ContactResponse::ContactRelationName));

	EXPECT_EQ(party1c1->GetRelations().size(), 1);
	EXPECT_EQ(party2c1->GetRelations().size(), 1);

	// party2 -> party3

	const auto circumstance2 = ContactCircumstanceBuilder::Build(party2c1, party3);
	auto party2c2 = circumstance2->GetResponse()->GetSender();
	auto party3c2 = circumstance2->GetResponse()->GetReceiver();
	
	EXPECT_TRUE(party2c2->HasRelationTo(party3c2, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party3c2->HasRelationTo(party2c2, ContactResponse::ContactRelationName));		
	
	EXPECT_EQ(party2c2->GetRelations().size(), 2); // should have an extra relation to party 3
	EXPECT_EQ(party3c2->GetRelations().size(), 1);

	// party1 -> party4

	const auto circumstance3 =  ContactCircumstanceBuilder::Build(party1c1, party4);
	auto party1c3 = circumstance3->GetResponse()->GetSender();
	auto party4c3 = circumstance3->GetResponse()->GetReceiver();
	
	EXPECT_TRUE(party1c3->HasRelationTo(party4c3, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party4c3->HasRelationTo(party1c3, ContactResponse::ContactRelationName));
	EXPECT_FALSE(party1c3->HasRelationTo(party3c2,  ContactResponse::ContactRelationName)); // note!

	EXPECT_EQ(party1c3->GetRelations().size(), 2);

	// changes to state over time:
	// t1: circumstance1  (party1c1-party2c1)
	// t2: circumstance2  (party1c1-party2c1-party3)
	// t3: circumstance3  (party1c1-party2c1-party4)

}

TEST(RelationshipTests, GraphCircumstances)
{
	std::shared_ptr<IParty> party1 = std::make_shared<Party>("party1");
	std::shared_ptr<IParty> party2 = std::make_shared<Party>("party2");
	std::shared_ptr<IParty> party3 = std::make_shared<Party>("party3");
	std::shared_ptr<IParty> party4 = std::make_shared<Party>("party4");
	
	const auto circumstance1 = ContactCircumstanceBuilder::Build(party1, party2);
	party1 = circumstance1->GetResponse()->GetSender();
	party2 = circumstance1->GetResponse()->GetReceiver();
		
	const auto circumstance2 = ContactCircumstanceBuilder::Build(party2, party3);
	party2 = circumstance2->GetResponse()->GetSender();
	party3 = circumstance2->GetResponse()->GetReceiver();
	
	const auto circumstance3 =  ContactCircumstanceBuilder::Build(party3, party4);
	party3 = circumstance3->GetResponse()->GetSender();
	party4 = circumstance3->GetResponse()->GetReceiver();
	
	EXPECT_TRUE(party1->HasRelationTo(party2, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party2->HasRelationTo(party1, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party2->HasRelationTo(party3, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party3->HasRelationTo(party2, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party3->HasRelationTo(party4, ContactResponse::ContactRelationName));
	EXPECT_TRUE(party4->HasRelationTo(party3, ContactResponse::ContactRelationName));

	Tree<Party> state1 = GraphBuilder::Build(circumstance1);	
	auto state2 = GraphBuilder::Build(circumstance2);
	auto state3 = GraphBuilder::Build(circumstance3);

	EXPECT_EQ(state1.GetDepth(), 1);
	EXPECT_EQ(state2.GetDepth(), 2);
	EXPECT_EQ(state3.GetDepth(), 3);

	// States: State1 -> State2 -> state3

	// State1: party2-party1
	EXPECT_EQ(state1.Root->Item.GetId(), party2->GetId()); // depth 0
	EXPECT_EQ(state1.Root->Children[0]->Item.GetId(), party1->GetId()); // depth 1

	// State2: Party3-party2-party1
	EXPECT_EQ(state2.Root->Item.GetId(), party3->GetId()); // depth 0
	EXPECT_EQ(state2.Root->Children[0]->Item.GetId(), party2->GetId()); // depth 1
	EXPECT_EQ(state2.Root->Children[0]->Children[0]->Item.GetId(), party1->GetId()); // depth 2

	// State3: Party4-party3-party2-party1
	EXPECT_EQ(state3.Root->Item.GetId(), party4->GetId()); //depth 0
	EXPECT_EQ(state3.Root->Children[0]->Item.GetId(), party3->GetId()); // depth 1
	EXPECT_EQ(state3.Root->Children[0]->Children[0]->Item.GetId(), party2->GetId()); //depth 2
	EXPECT_EQ(state3.Root->Children[0]->Children[0]->Children[0]->Item.GetId(), party1->GetId()); //depth 3
	

}